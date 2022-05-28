#include "Scene.h"
#include "Object.h"
#include "BVH.h"
#include "Ray.h"
#include "Sphere.h"
#include"Rectangles.h"
#include "IShader.h"
#include <iostream>
#include"Utils.h"
#define NormalSee 0
#define LightHitJudge 0

TinyGlm::vec3<float> Scene::GetReflectDir(TinyGlm::vec3<float>& income_light, TinyGlm::vec3<float>& normal)
{
	TinyGlm::vec3<float> result;
	result = income_light - (2.0f * income_light.dot(normal) * normal);
	return result;

}


Scene::Scene(int w , int h ):width(w),height(h),eye_pos(TinyGlm::vec3<float>(0.0f,0.0f,0.0f))
{
	bvh = nullptr;
}

Scene::~Scene()
{
	if(bvh!=nullptr)
		delete bvh;
}

void Scene::AddObj(std::shared_ptr<Object> object)
{
	obj_list.push_back(object);
}

void Scene::AddLight(std::shared_ptr<Object> light)
{
	obj_list.push_back(light);
	light_list.push_back(light);
}

void Scene::BuildBVH()
{
	bvh = new BVH(obj_list);
}


Intersection Scene::GetIntersect(const Ray& ray) const
{
	Intersection result;
	Ray temp_ray(ray.origin, ray.direction);
	for (auto& object : obj_list)
	{
		result = object->GetIntersection(temp_ray);
		if (result.hit)
		{
			return result;
		}
	}
	return result;

}


TinyGlm::vec3<float> Scene::GetColor(Ray& ray, int mis_weight,int current_depth, int recursive_max_depth)
{

	//�ﵽ���ݹ����
	if (current_depth > recursive_max_depth)
	{
		return TinyGlm::vec3<float>();
	}
	//�ﵽ�볡��û�н���
	Intersection interToBvh = bvh->GetIntersection(ray, bvh->root);
	if (interToBvh.hit == false)
	{
		return TinyGlm::vec3<float>();
	}
		
	TinyGlm::vec3<float> result(0.0f);

	//����򵽵ƹ⣬��ֱ�ӷ��صƹ���ɫ
	if (interToBvh.shader->is_emit_light && current_depth == 0)
	{
		result = TinyGlm::vec3<float>(interToBvh.shader->emittion_color.x, interToBvh.shader->emittion_color.y, interToBvh.shader->emittion_color.z);
		Utils::toon_mapping(result);
		return  result * mis_weight;
	}

#if  NormalSee == 1
	TinyGlm::vec3<float> normal = interToBvh.normal * 0.5f + 0.5f;
	return normal;
#endif //  NormalSee == 1


	
	TinyGlm::vec4<float> hit_color;
	TinyGlm::vec3<float> light_dir;
	Intersection interToLight;
	std::vector<float> pdf_list;
	float pdf=0.0f;
	float light_and_hitpoint_dis_noneclamp = 0;
	float light_and_hitpoint_dis = 0;

	//Ϊ�˼��������Ҫ�Բ�������Ҫ�����pdf(Ŀǰ����ֻ��һ����Դ����ôд��Todo: ���Դ)
	TinyGlm::vec3<float> indir = (interToBvh.shader->GetInDirSample(ray.direction, (interToBvh.normal)));
	Ray indir_ray(interToBvh.coords + 0.001f * interToBvh.normal.normalize(), indir.normalize());
	Intersection interToIndir = bvh->GetIntersection(indir_ray, bvh->root);
	float indir_pdf = interToBvh.shader->GetPdf(-(ray.direction), indir, interToBvh.normal);

	pdf_list.push_back(indir_pdf);

	//ֱ�ӹ�
	if (light_list.size() >= 1)
	{
		//��ȡ�ƹ��������Ϣ
		Intersection light_sample= light_list[0]->GetSampleInfo();

		light_dir = light_sample.coords - interToBvh.coords;
		light_and_hitpoint_dis_noneclamp = light_dir.length();
		light_and_hitpoint_dis = std::max(light_and_hitpoint_dis_noneclamp, 1.0f);

		light_dir = light_dir.normalize();

		pdf = light_list[0]->GetPdf(-light_dir, light_and_hitpoint_dis);
		

		Ray tolight_ray(interToBvh.coords + 0.001f * interToBvh.normal.normalize(), light_dir);

		interToLight = bvh->GetIntersection(tolight_ray, bvh->root);

		bool hit_bool = false;

#if LightHitJudge==0
		hit_bool = interToLight.hit && interToLight.shader->is_emit_light;
#elif LightHitJudge==1
		hit_bool = interToLight.distance - light_and_hitpoint_dis > -std::numeric_limits<float>::epsilon();
#endif 

		//����򵽵ƹ�
		if (hit_bool)
		{
			TinyGlm::vec4<float> shading = interToBvh.shader->Shading(ray.direction, light_dir, interToBvh.normal);
			float light_n_dot_l = std::clamp(light_dir.dot(-interToLight.normal), -std::numeric_limits<float>::epsilon(), 1.0f);

			pdf_list.push_back(pdf / light_n_dot_l);

			float w_ems= Utils::get_mis_weight(pdf, pdf_list);
				
			hit_color = light_sample.emition *
				shading *
				std::clamp(light_dir.dot(interToBvh.normal), -std::numeric_limits<float>::epsilon(), 1.0f) *
				std::clamp(light_dir.dot(-interToLight.normal), -std::numeric_limits<float>::epsilon(), 1.0f)/
				//w_ems /  //(���Utils::get_mis_weight(pdf, pdf_list)���ܻ��СȻ���ó����кڵ�qwq)
				(pdf)/  
				(light_and_hitpoint_dis* light_and_hitpoint_dis);


			result = TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);
			Utils::toon_mapping(result);
			hit_color = TinyGlm::vec4<float>(result.x, result.y, result.z, hit_color.w);

			
		}
	}

	//���δ�����������򷵻�
	if (interToIndir.hit == false)
	{
		result = TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);

		return result;
	}

	float in_light_and_hitpoint_dis = std::max((interToIndir.coords - interToBvh.coords).length(), 1.0f);

	TinyGlm::vec3<float> indir_color = GetColor(indir_ray, Utils::get_mis_weight(indir_pdf, pdf_list),(current_depth + 1), recursive_max_depth) ;

	TinyGlm::vec4<float> shading = interToBvh.shader->Shading(ray.direction , indir , interToBvh.normal);

	TinyGlm::vec4<float> indir_color_vec4 = indir_color *
		shading *
		std::clamp(indir.dot(interToBvh.normal), -std::numeric_limits<float>::epsilon(), 1.0f) / 
		 indir_pdf /
		(in_light_and_hitpoint_dis* in_light_and_hitpoint_dis);

	indir_color_vec4 = TinyGlm::vec4<float>(std::max(indir_color_vec4.x,std::numeric_limits<float>::epsilon()), std::max(indir_color_vec4.y, std::numeric_limits<float>::epsilon()), std::max(indir_color_vec4.z, std::numeric_limits<float>::epsilon()));

	
	hit_color += indir_color_vec4 * 0.8f;

	result = TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);
	Utils::toon_mapping(result);

	return result;
	
	

}

