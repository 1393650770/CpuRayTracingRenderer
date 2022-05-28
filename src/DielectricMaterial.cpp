#include "DielectricMaterial.h"

DielectricMaterial::DielectricMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float _roughness, float _metallicity, bool _is_emit_light)
{
	emittion_color = emit_color;
	f0 = _f0;
	roughness = _roughness;
	metallicity = _metallicity;
	is_emit_light = _is_emit_light;
}

DielectricMaterial::~DielectricMaterial()
{
}

TinyGlm::vec4<float> DielectricMaterial::Shading(TinyGlm::vec3<float> wi, TinyGlm::vec3<float> wo, TinyGlm::vec3<float> normal)
{
	return TinyGlm::vec4<float>(0.0f);
}

TinyGlm::vec3<float> DielectricMaterial::GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal)
{
	return TinyGlm::vec3<float>();
}

float DielectricMaterial::GetPdf(const TinyGlm::vec3<float>& income_view, const TinyGlm::vec3<float>& out_light, const TinyGlm::vec3<float>& normal)
{
	return 0.0f;
}
