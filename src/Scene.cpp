#include "Scene.h"
#include "Object.h"
#include "BVH.h"
#include "Ray.h"
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

void Scene::Add(std::shared_ptr<Object> object)
{
	objlist.push_back(object);
}

void Scene::BuildBVH()
{
	bvh = new BVH(objlist);
}

TinyGlm::vec3<float> Scene::GetColor(Ray& ray,int current_depth, int recursive_max_depth)
{

	//达到最大递归深度
	if (current_depth > recursive_max_depth)
		return TinyGlm::vec3<float>();

	//达到与场景没有交点
	Intersection interToBvh = bvh->GetIntersection(ray, bvh->root);
	if (interToBvh.hit == false)
	{
		return TinyGlm::vec3<float>();
	}
		
	//如果打到灯光，则直接返回灯光颜色
	if (interToBvh.shader->is_emit_light)
		return  TinyGlm::vec3<float>(interToBvh.shader->emittion_color.x, interToBvh.shader->emittion_color.y, interToBvh.shader->emittion_color.z);
#if  NormalSee == 1
	TinyGlm::vec3<float> normal = interToBvh.normal * 0.5f + 0.5f;
	return normal;
#endif //  NormalSee == 1

	//std::cout << "有交点" << std::endl;
	TinyGlm::vec3<float> light_dir(10.f ,20.0f ,5.f);

	light_dir = light_dir.normalize();
	TinyGlm::vec4<float> hit_color = interToBvh.shader->Shading(ray.direction, light_dir, interToBvh.normal);
	hit_color = hit_color + interToBvh.shader->emittion_color * 0.5f;
	hit_color = TinyGlm::vec4<float>(std::min(hit_color.x, 1.0f), std::min(hit_color.y, 1.0f), std::min(hit_color.z, 1.0f));

	TinyGlm::vec3<float> indir = interToBvh.shader->GetInDirSample(ray.direction, interToBvh.normal);
	Ray indir_ray(interToBvh.coords + 0.001f * interToBvh.normal, indir);
	Intersection interToIndir = bvh->GetIntersection(indir_ray , bvh->root);

	if (interToIndir.hit == true)
	{
		TinyGlm::vec3<float> indir_color = GetColor(indir_ray, current_depth + 1, 3);
		
		TinyGlm::vec4<float> shading = interToIndir.shader->Shading(ray.direction, -indir, interToIndir.normal);

		//std::cout << "shading: " << shading.x << " " << shading.y << " " << shading.z << std::endl;

		TinyGlm::vec4<float> indir_color_vec4 = indir_color * shading  * std::abs( light_dir.dot(interToBvh.normal));

		hit_color = hit_color + indir_color_vec4;

		//std::cout << "hit_color: " << hit_color.x << " " << hit_color.y << " " << hit_color.z << std::endl;
	}
	TinyGlm::vec3<float> result = TinyGlm::vec3<float>(hit_color.x,hit_color.y, hit_color.z);

	Utils::toon_mapping(result);

	return result;
	

}

