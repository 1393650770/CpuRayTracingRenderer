#pragma once
#ifndef _OBJECT_
#define _OBJECT_
#include "Ray.h"
#include "Intersection.h"

namespace TinyGlm
{
	template<typename T>
	class vec3;
	template<typename T>
	class vec2;
};

class Bound;

class Object
{
private:

public:
	Object();
	virtual ~Object();
	//≈–∂œ «∑Òœ‡Ωª
	virtual bool CheckIsIntersect(const Ray& ray) = 0; 
	virtual Intersection GetIntersection(Ray& ray) = 0;
	virtual void GetSurfaceProperties(const TinyGlm::vec3<float>&, const TinyGlm::vec3<float>&, const uint32_t&, const TinyGlm::vec2<float>&, TinyGlm::vec3<float>&, TinyGlm::vec2<float>&) const = 0;
	virtual Bound GetBound()=0;
};



#endif //_OBJECT_
