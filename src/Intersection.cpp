#include "Intersection.h"
Intersection::Intersection()
{
	hit = false;
	coords = TinyGlm::vec3<float>();
	texture_coords = TinyGlm::vec3<float>();
	normal = TinyGlm::vec3<float>();
	distance = std::numeric_limits<float>::max();
	obj = nullptr;
}

Intersection::~Intersection()
{
}
