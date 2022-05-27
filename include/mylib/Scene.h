#pragma once
#ifndef _SCENE_
#define _SCENE_
#include <vector>
#include <memory>
#include "TinyGlm.h"

class BVH;
class Object;
class Ray;
class Intersection;

class Scene
{

private:

	//计算反射光线
	TinyGlm::vec3<float> GetReflectDir(TinyGlm::vec3<float>& income_light, TinyGlm::vec3<float>& normal);

public:
	int width= 1280;
	int height= 960;
	float fov = 45;
	std::vector<std::shared_ptr<Object> > obj_list;
	std::vector<std::shared_ptr<Object> > light_list;

	TinyGlm::vec3<float> eye_pos;
	BVH* bvh;
	Scene(int w=1920, int h=1080);
	
	virtual ~Scene();

	//往场景中添加物体
	void AddObj(std::shared_ptr<Object> object);
	//往场景中添加光源
	void AddLight(std::shared_ptr<Object> light);
	//构建BVH
	void BuildBVH();

	Intersection GetIntersect(const Ray& ray) const;

	//获取颜色
	TinyGlm::vec3<float> GetColor(Ray& ray,int current_depth=0,int recursive_max_depth=2);
};
#endif //_SCENE_
