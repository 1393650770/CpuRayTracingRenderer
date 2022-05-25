#include "PBRMaterial.h"
#include <math.h>
#include <algorithm>
#include "Utils.h"




float PBRMaterial::GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0f);
    float k = (r * r) / 8.0f;

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k+0.000001f;

    return nom / denom;
}

float PBRMaterial::GeometrySmith(TinyGlm::vec3<float>& nomal_dir, TinyGlm::vec3<float>& view_dir, TinyGlm::vec3<float>& light_dir, float roughness)
{
    float NdotV = std::max(nomal_dir.dot(view_dir), 0.00001f);
    float NdotL = std::max(nomal_dir.dot(light_dir), 0.00001f);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float PBRMaterial::DistributionGGX(TinyGlm::vec3<float>& normal_dir, TinyGlm::vec3<float>& half_dir, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH =  std::max(normal_dir.dot(half_dir), 0.0001f);
    float NdotH2 = NdotH * NdotH;

    //std::cout << NdotH2 << std::endl;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
    denom = denom * denom * PI+0.0001f;

    return nom / denom;
}

TinyGlm::vec3<float> PBRMaterial::FresnelSchlick(float cosTheta, TinyGlm::vec3<float>& F0)
{

    return F0 + (TinyGlm::vec3<float>(1.0f) - F0) * std::powf(Utils::clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
}




PBRMaterial::PBRMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, const TinyGlm::vec3<float>& _light_color, float _roughness, float _metallicity, bool _is_emit_light)
{
    light_color = _light_color;
    emittion_color = emit_color;
    f0 = _f0;
    roughness = std::clamp( _roughness,0.001f,0.999f);
    metallicity = std::clamp(_metallicity, 0.001f, 0.999f);
    is_emit_light=_is_emit_light;
}

PBRMaterial::~PBRMaterial()
{
}

TinyGlm::vec4<float> PBRMaterial::Shading(TinyGlm::vec3<float> wi, TinyGlm::vec3<float> wo, TinyGlm::vec3<float> normal)
{
    TinyGlm::vec3<float> normal_dir = normal.normalize();
    TinyGlm::vec3<float> light_dir = wo.normalize();
    float cos_theta = normal_dir.dot(light_dir);

    if (cos_theta > -std::numeric_limits<float>::epsilon())
    {
        TinyGlm::vec3<float> view_dir = (-wi).normalize();
        TinyGlm::vec3<float> half_dir = (view_dir + light_dir).normalize();

        float D = DistributionGGX(normal_dir, half_dir, roughness);

        float G = GeometrySmith(normal_dir, view_dir, light_dir, roughness);
        
        TinyGlm::vec3<float> non_matal(0.04f);
        f0 = Utils::lerp(non_matal, f0, metallicity);

        TinyGlm::vec3<float> F = FresnelSchlick(std::max(cos_theta,0.0f), f0);

        float divide = 1.0f / (4.0f * std::max(normal_dir.dot(light_dir), 0.0001f) * std::max(normal_dir.dot(view_dir), 0.0001f));

        TinyGlm::vec3<float> specular = D * F * G * divide;

        TinyGlm::vec3<float> KD = TinyGlm::vec3<float>(1.0f) - F;
        
        KD *= 1.0f- metallicity;
         
        TinyGlm::vec3<float> emittion_color_vec3 = TinyGlm::vec3<float>(emittion_color.x, emittion_color.y, emittion_color.z);
        TinyGlm::vec3<float> color = (emittion_color_vec3 * KD / PI + specular)* light_color;
        
        //Utils::toon_mapping(color);
        return  TinyGlm::vec4<float>(color.x, color.y, color.z);

    }

    return TinyGlm::vec4<float>(0.0f);
}

//获取间接光的方向
TinyGlm::vec3<float> PBRMaterial::GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) 
{
    //----cos-weighted 重要性采样---
    {
        //----cos-weighted 重要性采样:从pdf反推---
        {
            float r1 = Utils::get_random_float(), r2 = Utils::get_random_float();
            float theta = std::acosf(std::sqrt(1.0f - r1)), phi = 2 * PI * r2;
            TinyGlm::vec3<float> localRay(std::cos(phi) * std::sin(theta), std::sin(phi) * std::sin(theta), std::cos(theta));
            return Utils::toWorld(localRay, normal);
        }

        //----cos-weighted 重要性采样:从pdf反推（化简，并改版）---
        //{
        //	float z = std::fabs(1.0f - 2.0f * Utils::get_random_float());
        //	float r = std::sqrt(1.0f - z * z), phi = 2 * PI * Utils::get_random_float();
        //	TinyGlm::vec3<float> localRay(r * std::cos(phi), r * std::sin(phi), z);
        //	return Utils::toWorld(localRay, normal);
        //}

        //----cos-weighted 重要性采样:法线中心球形采样（太极图形）---
        //{
        //	TinyGlm::vec3<float> localRay;
        //	do
        //	{
        //		localRay = 2.0f * TinyGlm::vec3<float>(Utils::get_random_float(), Utils::get_random_float(), Utils::get_random_float()) - TinyGlm::vec3<float>(1.0f);
        //	} while (localRay.dot(localRay) >= 1.0f);
        //	return localRay + normal.normalize();
        //}
    }
}

//重要性采样
float PBRMaterial::GetPdf(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) 
{
    float ndotl = wi.dot(normal);
    if (ndotl >= 0.0001f)
    {
        return ndotl / PI;
    }
    return 0.0f;
}
