#include "PBRMaterial.h"
#include <math.h>
#include <algorithm>
#include "Utils.h"




float PBRMaterial::GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0f);
    float k = (r * r) / 8.0f;

    float nom = NdotV;
    float denom = NdotV * (1.0f - k) + k +0.01f;

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
    denom = denom * denom * PI+ 0.0001f;

    return nom / denom;
}

TinyGlm::vec3<float> PBRMaterial::FresnelSchlick(float cosTheta, TinyGlm::vec3<float>& F0)
{

    return F0 + (TinyGlm::vec3<float>(1.0f) - F0) * std::powf(std::clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
}




PBRMaterial::PBRMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float specular_intensity, float _roughness, float _metallicity, bool _is_emit_light)
{
    emittion_color = emit_color;
    f0 = _f0;
    roughness = std::clamp( _roughness, std::numeric_limits<float>::epsilon(), 1.0f);
    intensiy = specular_intensity;
    metallicity = std::clamp(_metallicity, std::numeric_limits<float>::epsilon(), 1.0f);
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

        TinyGlm::vec3<float> F = FresnelSchlick(std::max(cos_theta,0.0001f), f0);

        float divide = 1.0f / (4.0f * std::max(normal_dir.dot(light_dir), 0.0001f) * std::max(normal_dir.dot(view_dir), 0.0001f));

        TinyGlm::vec3<float> specular = D * F * G * divide;

        TinyGlm::vec3<float> KD = TinyGlm::vec3<float>(1.0f) - F;
        
        KD *= (1.0f- metallicity);
         
        TinyGlm::vec3<float> emittion_color_vec3 = TinyGlm::vec3<float>(emittion_color.x, emittion_color.y, emittion_color.z);
        
        //return  TinyGlm::vec4<float>(specular.x* intensiy, specular.y * intensiy, specular.z * intensiy);
        TinyGlm::vec3<float> color = emittion_color_vec3 * KD / PI + specular*intensiy;
        

        Utils::toon_mapping(color);
        return  TinyGlm::vec4<float>(color.x, color.y, color.z);

    }

    return TinyGlm::vec4<float>(0.0f);
}

//????????????????
TinyGlm::vec3<float> PBRMaterial::GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) 
{
    //----cos-weighted ??????????---
    {
        //----cos-weighted ??????????:??pdf????---
        {
            //float r1 = Utils::get_random_float(), r2 = Utils::get_random_float();
            //float theta = std::acosf(std::sqrt(1.0f - r1)), phi = 2 * PI * r2;
            //TinyGlm::vec3<float> localRay(std::cos(phi) * std::sin(theta), std::sin(phi) * std::sin(theta), std::cos(theta));
            //return Utils::toWorld(localRay, normal);
        }

        //----cos-weighted ??????????:??pdf????????????????????---
        //{
        //	float z = std::fabs(1.0f - 2.0f * Utils::get_random_float());
        //	float r = std::sqrt(1.0f - z * z), phi = 2 * PI * Utils::get_random_float();
        //	TinyGlm::vec3<float> localRay(r * std::cos(phi), r * std::sin(phi), z);
        //	return Utils::toWorld(localRay, normal);
        //}

        //----cos-weighted ??????????:????????????????????????????---
        //{
        //	TinyGlm::vec3<float> localRay;
        //	do
        //	{
        //		localRay = 2.0f * TinyGlm::vec3<float>(Utils::get_random_float(), Utils::get_random_float(), Utils::get_random_float()) - TinyGlm::vec3<float>(1.0f);
        //	} while (localRay.dot(localRay) >= 1.0f);
        //	return localRay + normal.normalize();
        //}
    }

    //----BRDF ??????????---
    {
        float a_2 = roughness * roughness;
        float r1 = Utils::get_random_float(), r2 = Utils::get_random_float();
        float theta = std::atanf(std::sqrtf( -( a_2 * a_2 * std::logf(1.0f-r1) ))), phi = 2.0f * PI * r2;

        TinyGlm::vec3<float> localRay(std::cos(phi) * std::sin(theta), std::sin(phi) * std::sin(theta) , std::cos(theta));

        TinyGlm::vec3<float> worldHalf = Utils::toWorld(localRay, normal).normalize();
        TinyGlm::vec3<float> income_view = wi;

        return Utils::reflect(income_view,worldHalf).normalize();
    }
}

//??????????
float PBRMaterial::GetPdf(const TinyGlm::vec3<float>& income_view, const TinyGlm::vec3<float>& out_light,const TinyGlm::vec3<float>& normal)
{

    //----cos-weighted ??????????---
    //{
    //    float result = 0.0f;
    //    float ndotl = out_light.dot(normal);
    //    if (ndotl >= 0.0001f)
    //    {
    //        result= ndotl / PI;
    //    }
    //    //std::cout << result << std::endl;
    //    return result;
    //}

    //----BRDF ??????????---
    {
        TinyGlm::vec3<float> world_half = (income_view+out_light).normalize();
        TinyGlm::vec3<float> normal_not_const = normal.normalize();
        float D = DistributionGGX(normal_not_const, world_half, roughness);
        float n_dot_h = std::max(normal_not_const.dot(world_half), 0.0001f);
        float l_dot_h = std::max(world_half.dot(out_light), 0.0001f);
        float l_dot_n = std::max(normal.dot(out_light), 0.0001f);

        TinyGlm::vec3<float> Ks_vec3 = FresnelSchlick(std::max(l_dot_n, 0.0001f), f0);

        float ks = (Ks_vec3.x + Ks_vec3.y + Ks_vec3.z) / 3.0f;

        //??????????pdf
        float glossy = ks * D * n_dot_h / (4.0f * l_dot_h);

        //????????pdf
        float diffuse = (1.0f - ks) * l_dot_n / PI;

        float result = glossy + diffuse;

        return (result);
    }
}
