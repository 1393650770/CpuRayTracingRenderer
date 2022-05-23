#include "Scene.h"
#include "Object.h"
#include "BVH.h"
#include "Ray.h"
#include "Sphere.h"
#include "IShader.h"
#include <iostream>
#include"Utils.h"
#define NormalSee 0

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


TinyGlm::vec3<float> Scene::GetColor(Ray& ray,int current_depth, int recursive_max_depth)
{

	//达到最大递归深度
	if (current_depth > recursive_max_depth)
	{
		return TinyGlm::vec3<float>();
	}
	//达到与场景没有交点
	Intersection interToBvh = bvh->GetIntersection(ray, bvh->root);
	if (interToBvh.hit == false)
	{
		return TinyGlm::vec3<float>();
	}
		
	TinyGlm::vec3<float> result;
	//如果打到灯光，则直接返回灯光颜色
	if (interToBvh.shader->is_emit_light)
	{
		result = TinyGlm::vec3<float>(interToBvh.shader->emittion_color.x, interToBvh.shader->emittion_color.y, interToBvh.shader->emittion_color.z);
		Utils::toon_mapping(result);
		return  result;
	}

#if  NormalSee == 1
	TinyGlm::vec3<float> normal = interToBvh.normal * 0.5f + 0.5f;
	return normal;
#endif //  NormalSee == 1

	//std::cout << "有交点" << std::endl;

	TinyGlm::vec4<float> hit_color;

	TinyGlm::vec3<float> light_dir;
	Intersection interToLight;
	float light_and_hitpoint_dis = 0;

	if (light_list.size() >= 1)
	{
		Intersection light_sample= light_list[0]->GetSampleInfo();
		float light_pdf = light_list[0]->GetPdf();

		light_dir = light_sample.coords - interToBvh.coords;
		light_and_hitpoint_dis = light_dir.length();

		light_dir = light_dir.normalize();

		Ray tolight_ray(interToBvh.coords + 0.001f * interToBvh.normal, light_dir);

		interToLight =bvh->GetIntersection(tolight_ray, bvh->root);


		if (interToLight.distance - light_and_hitpoint_dis > -0.005f)
		{
			TinyGlm::vec4<float> shading = interToBvh.shader->Shading(ray.direction, light_dir, interToBvh.normal);

			hit_color = light_sample.emition  * shading *
				light_dir.dot(interToBvh.normal)*
				light_dir.dot(-interToLight.normal)/ light_and_hitpoint_dis/light_pdf;

			result = TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);
			Utils::toon_mapping(result);
			hit_color = TinyGlm::vec4<float>(result.x, result.y, result.z, hit_color.w);

			//std::cout << "hit_color: " << hit_color.x << " " << hit_color.y << " " << hit_color.z << std::endl;
			//std::cout << "interToLight.normal: " << interToLight.normal.x << " " << interToLight.normal.y << " " << interToLight.normal.z << std::endl;
			//std::cout << "light_sample.emition: " << light_sample.emition.x << " " << light_sample.emition.y << " " << light_sample.emition.z << std::endl;
			//std::cout << "light_dir.dot(interToBvh.normal): " << light_dir.dot(interToBvh.normal) << std::endl;
			//std::cout << "light_dir.dot(interToLight.normal): " << light_dir.dot(-interToLight.normal) << std::endl;
			//std::cout << "shading: " << shading.x << " " << shading.y << " " << shading.z << std::endl << std::endl;

			
		}


	}

	TinyGlm::vec3<float> indir = (interToBvh.shader->GetInDirSample(ray.direction, (interToBvh.normal)));

	Ray indir_ray(interToBvh.coords + 0.001f * interToBvh.normal.normalize(), indir.normalize());

	Intersection interToIndir = bvh->GetIntersection(indir_ray , bvh->root);
	
	//如果未打到其他物体或者打到光源则返回
	if (interToIndir.hit == false || interToIndir.shader->is_emit_light)
	{
		result = TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);
		Utils::toon_mapping(result);
		return result;
	}

	float in_light_and_hitpoint_dis = (interToIndir.coords- interToBvh.coords).length();

	TinyGlm::vec3<float> indir_color = GetColor(indir_ray, (current_depth + 1), recursive_max_depth);

	TinyGlm::vec4<float> shading = interToBvh.shader->Shading(ray.direction , indir , interToBvh.normal);


	TinyGlm::vec4<float> indir_color_vec4 = indir_color* shading * std::clamp(indir.dot(interToBvh.normal), 0.0f, 1.0f)/ (in_light_and_hitpoint_dis* in_light_and_hitpoint_dis)/ interToBvh.shader->GetPdf(indir, interToBvh.normal);

	hit_color += indir_color_vec4;

	result = TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);
	Utils::toon_mapping(result);

	return result;
	
	

}

