#pragma once
#ifndef _BOUND_
#define _BOUND_
#include"TinyGlm.h"

class Ray;

class Bound
{
private:
	
public:
	TinyGlm::vec3<float> min_point;
	TinyGlm::vec3<float> max_point;
	TinyGlm::vec3<float> centroid_point;
	Bound();
	Bound(const TinyGlm::vec3<float>& min,const TinyGlm::vec3<float>& max);
	virtual ~Bound();

	//求是否相交；
	bool GetIsIntersect(const Ray& ray);
	int GetMaxAxis();


};


inline Bound Union(const Bound& b1, const Bound& b2)
{
	Bound result;
	result.min_point = TinyGlm::vec3<float>::min(b1.min_point, b2.min_point);
	result.max_point = TinyGlm::vec3<float>::max(b1.max_point, b2.max_point);
	return result;
}

inline Bound Union(const Bound& b1, const TinyGlm::vec3<float>& b2)
{
	Bound result;
	result.min_point = TinyGlm::vec3<float>::min(b1.min_point, b2);
	result.max_point = TinyGlm::vec3<float>::max(b1.max_point, b2);
	return result;
}

#endif // _BOUND_