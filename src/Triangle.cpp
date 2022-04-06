#include "Triangle.h"
#include "TinyGlm.h"

Triangle::Triangle(TinyGlm::vec3<float> v0, TinyGlm::vec3<float> v1, TinyGlm::vec3<float> v2):vertices0(v0),vertices1(v1),vertices2(v2)
{
	edge0 = vertices1 - vertices0;
	edge1 = vertices2 - vertices0;
	TinyGlm::vec3<float> e0_cross_e1=edge0.cross(edge1);
	normal = e0_cross_e1.normalize();
	area = e0_cross_e1.length() * 0.5f;
}

Triangle::~Triangle()
{

}

bool Triangle::CheckIsIntersect(const Ray& ray)
{

	return true;
}

Intersection Triangle::GetIntersection(Ray& ray)
{
	Intersection result;
	float u, v, t=0.0f;
	TinyGlm::vec3<float> pvec = ray.direction.cross(edge1);
	float det = edge0.dot(pvec);
	if (std::fabs(det) < std::numeric_limits<float>::epsilon())
	{
		return result;
	}
	float det_inv = 1.0f / det;
	TinyGlm::vec3<float> tvec = ray.origin - vertices0;
	u = tvec.dot(pvec) * det_inv;
	if (u < 0.0f || u>1.0f)
		return result;
	TinyGlm::vec3<float> qvec = tvec.cross(edge0);
	v = ray.direction.dot(qvec) * det_inv;
	if (v < 0.0f || v + u>1.0f)
		return result;
	t = edge1.dot(qvec) * det_inv;
	if (t < 0.0f)
		return result;
	result.distance = t;
	result.hit = true;
	result.normal = this->normal;
	result.texture_coords = ray.origin + ray.direction * t;
	result.obj = this;
	return result;
}
