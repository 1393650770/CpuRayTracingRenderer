#pragma once
#ifndef _MATERIAL_
#define _MATERIAL_
#include"IShader.h"


class PBRMaterial :
    public IShader
{
private:
    //计算几何函数SchickGGX
    float GeometrySchlickGGX(float NdotV, float roughness);
    //计算几何函数
    float GeometrySmith(TinyGlm::vec3<float>& nomal_dir, TinyGlm::vec3<float>& view_dir, TinyGlm::vec3<float>& light_dir, float roughness);
    //计算正态分布函数
    float DistributionGGX(TinyGlm::vec3<float>& normal_dir, TinyGlm::vec3<float>& half_dir, float roughness);
    //计算菲涅尔函数
    TinyGlm::vec3<float> FresnelSchlick(float cosTheta, TinyGlm::vec3<float>& F0);

    float intensiy;

public:

    PBRMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float specular_intensity, float _roughness,float _metallicity,bool _is_emit_light=false);
    virtual ~PBRMaterial();
    //计算着色接口
    TinyGlm::vec4<float> Shading(TinyGlm::vec3<float> wi, TinyGlm::vec3<float> wo, TinyGlm::vec3<float> normal) override;
    
    //获取间接光的方向
    TinyGlm::vec3<float> GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) override;
    
    //重要性采样
    float GetPdf(const TinyGlm::vec3<float>& income_view, const TinyGlm::vec3<float>& out_light, const TinyGlm::vec3<float>& normal) override;

};
#endif //_MATERIAL_

