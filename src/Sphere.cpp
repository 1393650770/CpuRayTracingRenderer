#include "Sphere.h"
#include"Bound.h"

Sphere::Sphere(const TinyGlm::vec3<float>& _center, float _radius) :center(_center), radius(_radius)
{
}

Sphere::~Sphere()
{
}

bool Sphere::CheckIsIntersect(const Ray& ray)
{
	TinyGlm::vec3<float> center_to_rayorigin = ray.origin - center;
	//射线原点到球中心的距离平方
	float distance_center_to_rayorigin = center_to_rayorigin.dot(center_to_rayorigin);
	if (distance_center_to_rayorigin < radius * radius)
		return true;

	//射线原点到球中心在射线上的投影距离
	float dis_proj_centortorayorigin_to_raydirection = ray.direction.normalize().dot(center_to_rayorigin);
	if (dis_proj_centortorayorigin_to_raydirection <= std::numeric_limits<float>::epsilon())
		return false;

	//球中心到射线的垂直距离平方
	float dis_center_to_raylight = distance_center_to_rayorigin - dis_proj_centortorayorigin_to_raydirection * dis_proj_centortorayorigin_to_raydirection;
	if (dis_center_to_raylight > radius * radius)
		return false;
	return true;

}

Intersection Sphere::GetIntersection(Ray& ray)
{
	Intersection result;
	result.hit = CheckIsIntersect(ray);
	if (result.hit == false)
		return result;
	float t0= std::numeric_limits<float>::max(), t1= std::numeric_limits<float>::max();
	TinyGlm::vec3<float> ray_dir_normal = ray.direction.normalize();

	TinyGlm::vec3<float> center_to_rayorigin = ray.origin - center;
	//射线原点到球中心在射线上的投影距离
	float dis_proj_centortorayorigin_to_raydirection = ray_dir_normal.dot(center_to_rayorigin);
	//射线原点到球中心的距离平方
	float dis_center_to_rayorigin = center_to_rayorigin.dot(center_to_rayorigin);
	//球中心到射线的垂直距离平方
	float dis_center_to_raylight = dis_center_to_rayorigin - dis_proj_centortorayorigin_to_raydirection* dis_proj_centortorayorigin_to_raydirection;
	//两个交点之间的距离
	float dis_intersection_to_intersection = std::sqrtf(radius * radius - dis_center_to_raylight);

	t0 =std::min( dis_proj_centortorayorigin_to_raydirection - dis_intersection_to_intersection, dis_proj_centortorayorigin_to_raydirection + dis_intersection_to_intersection);
	t1= std::max( dis_proj_centortorayorigin_to_raydirection - dis_intersection_to_intersection, dis_proj_centortorayorigin_to_raydirection + dis_intersection_to_intersection);

	if (t0 <= -std::numeric_limits<float>::epsilon())
	{
		result.distance = t1;
	}
	else
	{
		result.distance = t0;
	}
	result.coords = TinyGlm::vec3<float>(ray.origin + ray_dir_normal * result.distance);
	result.obj =this;
	result.normal = TinyGlm::vec3<float>(result.coords - center).normalize();

	return result;
}

void Sphere::getSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const
{
	normal = (pos - center).normalize();
}

Bound Sphere::getBound()
{
	return Bound(TinyGlm::vec3<float>(center.x - radius, center.y - radius, center.z - radius), TinyGlm::vec3<float>(center.x + radius, center.y + radius, center.z + radius));
}
