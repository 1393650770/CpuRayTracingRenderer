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

    Sphere(const TinyGlm::vec3<float>& _center,float _radius, std::shared_ptr<IShader> _shader=nullptr);
    virtual ~Sphere();

    bool CheckIsIntersect(const Ray& ray) override;
    Intersection GetIntersection( Ray& ray) override;
    void GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const override;
    Bound GetBound() override;

    //均匀采样 ， TODO：重要性采样
    float GetPdf(const TinyGlm::vec3<float>& income_light, const float dis) override;

    Intersection GetSampleInfo() override;

};


#endif //_SPHERE_

