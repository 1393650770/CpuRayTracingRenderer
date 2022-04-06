#include "Bound.h"
#include<limits>

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

int Bound::GetMaxAxis()
{
	TinyGlm::vec3<float> sub = max_point - min_point;
	if (sub.x > sub.y && sub.x > sub.z)
		return 0;
	else if (sub.y > sub.z)
		return 1;
	return 2;
}
