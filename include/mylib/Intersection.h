#pragma once
#ifndef _INTERSECTION_
#define _INTERSECTION_
#include"TinyGlm.h"
class Object;
class Sphere;
class IShader;

class Intersection
{
private:
public:
	bool hit;
	TinyGlm::vec3<float> coords;
	TinyGlm::vec3<float> texture_coords;
	TinyGlm::vec3<float> normal;
	TinyGlm::vec3<float> emition;
	float distance;

	std::shared_ptr<IShader> shader;
	Object* obj;

	Intersection();
	virtual ~Intersection();
};

#endif //_INTERSECTION_
