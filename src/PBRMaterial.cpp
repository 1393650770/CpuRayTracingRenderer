#include "PBRMaterial.h"
#include <math.h>
#include <algorithm>
#include "Utils.h"




float PBRMaterial::GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0f);
    float k = (r * r) / 8.0f;

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k;

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
    denom = denom * denom * PI;

    return nom / denom;
}

TinyGlm::vec3<float> PBRMaterial::FresnelSchlick(float cosTheta, TinyGlm::vec3<float>& F0)
{

    return F0 + (TinyGlm::vec3<float>(1.0f) - F0) * std::powf(Utils::clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
}




PBRMaterial::PBRMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float _roughness, float _metallicity, bool _is_emit_light)
{
    emittion_color = emit_color;
    f0 = _f0;
    roughness = _roughness;
    metallicity = _metallicity;
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
        TinyGlm::vec3<float> F = FresnelSchlick(cos_theta, f0);
        float divide = 1.0f / (4 * std::max(normal_dir.dot(light_dir), 0.0001f) * std::max(normal_dir.dot(view_dir), 0.0001f));

        TinyGlm::vec3<float> specular = D * F * G * divide;

        TinyGlm::vec3<float> KD = TinyGlm::vec3<float>(1.0f) - F;
        
        KD *= 1.0f- metallicity;
         
        TinyGlm::vec3<float> emittion_color_vec3 = TinyGlm::vec3<float>(emittion_color.x, emittion_color.y, emittion_color.z);
        TinyGlm::vec3<float> color = emittion_color_vec3 * KD / PI + specular;
        
        
        return  TinyGlm::vec4<float>(std::min(color.x, 1.0f), std::min(color.y, 1.0f), std::min(color.z, 1.0f));

    }

    return TinyGlm::vec4<float>(0.0f);
}

//获取间接光的方向
TinyGlm::vec3<float> PBRMaterial::GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) 
{
    float x_1 = Utils::get_random_float(), x_2 = Utils::get_random_float();
    float z = std::fabs(1.0f - 2.0f * x_1);
    float r = std::sqrt(1.0f - z * z), phi = 2 * PI * x_2;
    TinyGlm::vec3<float> localRay(r * std::cos(phi), r * std::sin(phi), z);
    return Utils::toWorld(localRay, normal);
}

//重要性采样
float PBRMaterial::GetPdf(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) 
{
    return 0;
}
