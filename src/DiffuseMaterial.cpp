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
	if (normal.dot(wo) > std::numeric_limits<float>::epsilon())
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
	float x_1 = Utils::get_random_float(), x_2 = Utils::get_random_float();
	float z = std::fabs(1.0f - 2.0f * x_1);
	float r = std::sqrt(1.0f - z * z), phi = 2 * PI * x_2;
	TinyGlm::vec3<float> localRay(r * std::cos(phi), r * std::sin(phi), z);
	return Utils::toWorld(localRay, normal);
}

float DiffuseMaterial::GetPdf(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal)
{
	return 0.0f;
}
