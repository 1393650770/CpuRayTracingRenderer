#include "Intersection.h"
extern template class TinyGlm::vec4<float>;
extern template class TinyGlm::vec3<float>;
extern template class TinyGlm::vec2<float>;
Intersection::Intersection()
{
	hit = false;
	coords = TinyGlm::vec3<float>();
	texture_coords = TinyGlm::vec3<float>();
	normal = TinyGlm::vec3<float>();
	distance = std::numeric_limits<float>::max();
	obj = nullptr;
	shader = nullptr;
}

Intersection::~Intersection()
{
}
