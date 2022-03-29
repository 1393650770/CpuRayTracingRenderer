#pragma once
#ifndef _OBJECT_
#define _OBJECT_
#include "Ray.h"
#include "Intersection.h"

class Object
{
private:

public:
	Object();
	virtual ~Object();
	//≈–∂œ «∑Òœ‡Ωª
	virtual bool CheckIsIntersect(const Ray& ray) = 0; 
	virtual Intersection GetIntersection(Ray ray) = 0;
};



#endif //_OBJECT_
