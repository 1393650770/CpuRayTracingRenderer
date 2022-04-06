#include "Scene.h"
#include "Object.h"
#include "BVH.h"



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

