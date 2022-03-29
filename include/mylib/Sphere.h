#pragma once
#ifndef _SPHERE_
#define _SPHERE_
#include "Object.h"


class Sphere :
    public Object
{
private:
public:
    TinyGlm::vec3<float> center;
    float radius;
    Sphere(const TinyGlm::vec3<float>& _center,float _radius);
    virtual ~Sphere();

    bool CheckIsIntersect(const Ray& ray) ;
    Intersection GetIntersection(Ray ray) ;
};


#endif //_SPHERE_

