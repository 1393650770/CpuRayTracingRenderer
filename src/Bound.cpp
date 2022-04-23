#include "Bound.h"
#include "Ray.h"
#include<limits>
#include<algorithm>
#include<math.h>

extern template class TinyGlm::vec4<float>;
extern template class TinyGlm::vec3<float>;
extern template class TinyGlm::vec2<float>;

Bound::Bound()
{
	float max = std::numeric_limits<float>::max();
	float min = std::numeric_limits<float>::min();
	max_point = TinyGlm::vec3<float>(min, min, min);
	min_point = TinyGlm::vec3<float>(max, max, max);

}

Bound::Bound(const TinyGlm::vec3<float>& min, const TinyGlm::vec3<float>& max)
{
	min_point = min;
	max_point = max;
	centroid_point = (max + min) * 0.5f;

}

Bound::~Bound()
{
}

bool Bound::GetIsIntersect(const Ray& ray)
{
	TinyGlm::vec3<float> direction_inv(1.0f / ray.direction.x, 1.0f / ray.direction.y, 1.0f / ray.direction.z);

	//求出入t，和出t
	TinyGlm::vec3<float> t_minTemp = direction_inv * (min_point - ray.origin) ;
	TinyGlm::vec3<float> t_maxTemp = direction_inv * (max_point - ray.origin) ;
	TinyGlm::vec3<float> t_min = TinyGlm::vec3<float>::min(t_minTemp, t_maxTemp);
	TinyGlm::vec3<float> t_max = TinyGlm::vec3<float>::max(t_minTemp, t_maxTemp);

	float t_min_time = std::max(t_min.x, std::max(t_min.y, t_min.z));
	float t_max_time = std::min(t_max.x, std::max(t_max.y, t_max.z));

	return t_max_time>=-std::numeric_limits<float>::epsilon()&&t_min_time<=t_max_time;
}

int Bound::GetMaxAxis()
{
	TinyGlm::vec3<float> sub = max_point - min_point;
	if (sub.x > sub.y && sub.x > sub.z)
		return 0;
	else if (sub.y > sub.z)
		return 1;
	return 2;
}
