#pragma once
#ifndef _DIFFUSEMATRIAL_
#define _DIFFUSEMATRIAL_
#include"IShader.h"

class DiffuseMaterial :public IShader
{
public:
    DiffuseMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float _roughness, float _metallicity, bool _is_emit_light = false);
    virtual ~DiffuseMaterial();
    //计算着色接口
    TinyGlm::vec4<float> Shading(TinyGlm::vec3<float> wi, TinyGlm::vec3<float> wo, TinyGlm::vec3<float> normal) override;

    //获取间接光的方向
    TinyGlm::vec3<float> GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) override;

    //重要性采样
    float GetPdf(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) override;

};

#endif // _DIFFUSEMATRIAL_

