#include "DiffuseMaterial.h"
#include"Utils.h"
DiffuseMaterial::DiffuseMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float _roughness, float _metallicity, bool _is_emit_light)
{
	emittion_color = emit_color;
	f0 = _f0;
	roughness = _roughness;
	metallicity = _metallicity;
	is_emit_light = _is_emit_light;
}

DiffuseMaterial::~DiffuseMaterial()
{
}

TinyGlm::vec4<float> DiffuseMaterial::Shading(TinyGlm::vec3<float> wi, TinyGlm::vec3<float> wo, TinyGlm::vec3<float> normal)
{
	if (normal.dot(wo) > -std::numeric_limits<float>::epsilon())
	{
		return emittion_color / PI;
	}
	else
	{

		return TinyGlm::vec4<float>(0.f);
	}
}	

TinyGlm::vec3<float> DiffuseMaterial::GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal)
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

float DiffuseMaterial::GetPdf(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal)
{
	float ndotl=wi.dot(normal);
	if (ndotl >= -0.0001f)
	{
		return ndotl / PI;
	}
	return 0.0f;
}


