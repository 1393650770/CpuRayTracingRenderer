#pragma once
#ifndef _SCENE_
#define _SCENE_
#include <vector>
#include <memory>
#include "TinyGlm.h"

class BVH;
class Object;
class Ray;

class Scene
{

private:
	//std::vector<std::shared_ptr<Object *> > objlist;

	//计算反射光线
	TinyGlm::vec3<float> GetReflectDir(TinyGlm::vec3<float>& income_light, TinyGlm::vec3<float>& normal);

public:
	int width=1920;
	int height=1080;
	float fov = 60;
	std::vector<std::shared_ptr<Object> > objlist;
	TinyGlm::vec3<float> eye_pos;
	BVH* bvh;
	Scene(int w=1920, int h=1080);
	
	virtual ~Scene();

	//往场景中添加物体
	void Add(std::shared_ptr<Object> object);
	//构建BVH
	void BuildBVH();

	//获取颜色
	TinyGlm::vec3<float> GetColor(Ray& ray,int current_depth=0,int recursive_max_depth=2);
};
#endif //_SCENE_
