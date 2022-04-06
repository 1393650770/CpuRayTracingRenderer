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

    bool CheckIsIntersect(const Ray& ray) override;
    Intersection GetIntersection(Ray& ray) override;
    void getSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const override;
    Bound getBound() override;
};


#endif //_SPHERE_

