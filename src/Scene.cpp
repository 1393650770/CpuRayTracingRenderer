#include "Scene.h"
#include "Object.h"
#include "BVH.h"
#include "Ray.h"
#include "IShader.h"
#include <iostream>

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

	if (true)
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
		
		//std::cout << "有交点" << std::endl;
		TinyGlm::vec3<float> light_dir(10.f ,20.0f ,5.f);
		TinyGlm::vec4<float> hit_color = interToBvh.shader->Shading(ray.direction, light_dir, interToBvh.normal);
		hit_color = hit_color + interToBvh.shader->emittion_color * 0.5f;
		hit_color = TinyGlm::vec4<float>(std::min(hit_color.x, 1.0f), std::min(hit_color.y, 1.0f), std::min(hit_color.z, 1.0f));

		TinyGlm::vec3<float> indir_color = GetColor(Ray(interToBvh.coords + 0.01f * interToBvh.normal, GetReflectDir(ray.direction, interToBvh.normal)), current_depth+1, 4);
		//if(indir_color.x > std::numeric_limits<float>::epsilon() || indir_color.y > std::numeric_limits<float>::epsilon() || indir_color.z>std::numeric_limits<float>::epsilon())
			//std::cout << "indir_color : " << indir_color.x<<" "<< indir_color.y<<" " << indir_color .z<< std::endl;
		hit_color = hit_color *(1.0f- interToBvh.shader->metallicity) +  TinyGlm::vec4<float>(indir_color.x, indir_color.y, indir_color.z) * interToBvh.shader->metallicity;
		
		return TinyGlm::vec3<float>(std::min(hit_color.x,1.0f), std::min(hit_color.y, 1.0f), std::min(hit_color.z, 1.0f));
	
	}
	else
	{
		Intersection inter;
		for (auto& v : objlist)
		{
			Intersection k = v->GetIntersection(ray);
			if (k.hit)
			{
				TinyGlm::vec3<float> light_dir(10.f, 20.0f, 5.f);
				TinyGlm::vec4<float> hit_color = (k.shader->emittion_color * 0.8f) + k.shader->Shading(ray.direction, light_dir, k.normal);
				return  TinyGlm::vec3<float>(hit_color.x, hit_color.y, hit_color.z);
			}
		}
	}
	return TinyGlm::vec3<float>();
}

