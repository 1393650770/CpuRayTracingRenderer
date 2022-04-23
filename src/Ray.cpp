#include "Ray.h"



Ray::Ray(const TinyGlm::vec3<float>& ori, const TinyGlm::vec3<float>& dir, const float _t) :origin(ori), direction(dir.normalize()), t(_t)
{
	t_min = 0.0f;
	t_max = std::numeric_limits<float>::max();
}

Ray::~Ray()
{
}
