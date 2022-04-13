#pragma once
#ifndef _SPHERE_
#define _SPHERE_
#include "Object.h"

class IShader;

class Sphere :
    public Object
{
private:
    bool is_use_mathequation_solve = true;
public:
    TinyGlm::vec3<float> center;
    float radius;
    IShader* shader;

    Sphere(const TinyGlm::vec3<float>& _center,float _radius,IShader* _shader=nullptr, bool _is_use_mathequation_solve=false);
    virtual ~Sphere();

    bool CheckIsIntersect(const Ray& ray) override;
    Intersection GetIntersection( Ray& ray) override;
    void GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const override;
    Bound GetBound() override;
};


#endif //_SPHERE_

