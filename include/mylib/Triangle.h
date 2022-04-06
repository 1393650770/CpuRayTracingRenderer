#pragma once
#ifndef _TRIANGLE_
#define _TRIANGLE_
#include"Object.h"
#include"TinyGlm.h"


class Triangle :
	public Object
{
private:
public:
	Triangle(TinyGlm::vec3<float> v0, TinyGlm::vec3<float> v1, TinyGlm::vec3<float> v2);
	virtual ~Triangle();
	TinyGlm::vec3<float> vertices0, vertices1, vertices2;
	TinyGlm::vec3<float> edge0, edge1;
	TinyGlm::vec3<float> texture_vertices0, texture_vertices1, texture_vertices2;
	TinyGlm::vec3<float> normal;
	float area;

	bool CheckIsIntersect(const Ray& ray) override;
	Intersection GetIntersection(Ray& ray) override;
};

#endif //

