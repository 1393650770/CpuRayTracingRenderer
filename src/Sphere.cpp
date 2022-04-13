#include "Sphere.h"
#include"Bound.h"
#include"IShader.h"



Sphere::Sphere(const TinyGlm::vec3<float>& _center, float _radius, IShader* _shader, bool _is_use_mathequation_solve) :center(_center), radius(_radius),shader(_shader), is_use_mathequation_solve(_is_use_mathequation_solve)
{
}

Sphere::~Sphere()
{
}

bool Sphere::CheckIsIntersect(const Ray& ray)
{
	if (is_use_mathequation_solve ==true)
	{

		TinyGlm::vec3<float> oc = ray.origin - center;
		TinyGlm::vec3<float> ray_dir_normal = ray.direction.normalize();
		float a = ray_dir_normal.dot(ray_dir_normal);
		float b = ray_dir_normal.dot(oc);
		float c = oc.dot(oc) - radius * radius;
		float discriminant = b * b - a * c;
		if (discriminant > -std::numeric_limits<float>::epsilon())
		{
			float temp = (-b - sqrtf(discriminant)) / a;
			if (temp < std::numeric_limits<float>::max() && temp > std::numeric_limits<float>::epsilon())
			{
				return true;
			}
			temp = (-b + sqrtf(discriminant)) / a;
			if (temp < std::numeric_limits<float>::max() && temp > std::numeric_limits<float>::epsilon())
			{
				return true;
			}
		}
		return false;
	}
	else
	{
		TinyGlm::vec3<float> rayorigin_to_origin = center - ray.origin;
		//射线原点到球中心的距离平方
		float distance_center_to_rayorigin = rayorigin_to_origin.dot(rayorigin_to_origin);
		if (distance_center_to_rayorigin < radius * radius)
			return true;
		//std::cout << "1" << std::endl;
		//射线原点到球中心在射线上的投影距离
		float dis_proj_centortorayorigin_to_raydirection = ray.direction.normalize().dot(rayorigin_to_origin);
		if (dis_proj_centortorayorigin_to_raydirection <= std::numeric_limits<float>::epsilon())
			return false;
		//std::cout << "2" << std::endl;
		//球中心到射线的垂直距离平方
		float dis_center_to_raylight = distance_center_to_rayorigin - dis_proj_centortorayorigin_to_raydirection * dis_proj_centortorayorigin_to_raydirection;
		if (dis_center_to_raylight > radius * radius)
			return false;
		//std::cout << "3" << std::endl;
		return true;
	}
}

Intersection Sphere::GetIntersection(Ray& ray)
{
	Intersection result;
	result.hit = CheckIsIntersect(ray);
	if (result.hit == false)
		return result;
	TinyGlm::vec3<float> ray_dir_normal = ray.direction.normalize();

	if (is_use_mathequation_solve == true)
	{
		TinyGlm::vec3<float> oc = ray.origin - center;

		float a = ray_dir_normal.dot(ray_dir_normal);
		float b = ray_dir_normal.dot(oc);
		float c = oc.dot(oc) - radius * radius;
		float discriminant = b * b - a * c;
		if (discriminant > -std::numeric_limits<float>::epsilon())
		{
			float temp = (-b - sqrtf(discriminant)) / a;
			if (temp < std::numeric_limits<float>::max() && temp > std::numeric_limits<float>::epsilon())
			{
				result.distance = temp;
				result.coords = TinyGlm::vec3<float>(ray.origin + ray_dir_normal * result.distance);
				result.obj = this;
				result.normal = TinyGlm::vec3<float>(result.coords - center).normalize();
				result.shader = shader;
				return result;
			}
			temp = (-b + sqrtf(discriminant)) / a;
			if (temp < std::numeric_limits<float>::max() && temp > std::numeric_limits<float>::epsilon())
			{
				result.distance = temp;
				result.coords = TinyGlm::vec3<float>(ray.origin + ray_dir_normal * result.distance);
				result.obj = this;
				result.normal = TinyGlm::vec3<float>(result.coords - center).normalize();
				result.shader = shader;
				return result;
			}
		}

	}
	else
	{
		float t0 = std::numeric_limits<float>::max(), t1 = std::numeric_limits<float>::max();

		TinyGlm::vec3<float> rayorigin_to_center = center - ray.origin;
		//射线原点到球中心在射线上的投影距离
		float dis_proj_centortorayorigin_to_raydirection = ray_dir_normal.dot(rayorigin_to_center);
		//射线原点到球中心的距离平方
		float dis_center_to_rayorigin = rayorigin_to_center.dot(rayorigin_to_center);
		//球中心到射线的垂直距离平方
		float dis_center_to_raylight = dis_center_to_rayorigin - dis_proj_centortorayorigin_to_raydirection * dis_proj_centortorayorigin_to_raydirection;
		//两个交点之间的距离
		float dis_intersection_to_intersection = std::sqrtf(radius * radius - dis_center_to_raylight);

		t0 = std::min(dis_proj_centortorayorigin_to_raydirection - dis_intersection_to_intersection, dis_proj_centortorayorigin_to_raydirection + dis_intersection_to_intersection);
		t1 = std::max(dis_proj_centortorayorigin_to_raydirection - dis_intersection_to_intersection, dis_proj_centortorayorigin_to_raydirection + dis_intersection_to_intersection);

		if (t0 <= std::numeric_limits<float>::epsilon())
		{
			result.distance = t1;
		}
		else
		{
			result.distance = t0;
		}
		result.coords = TinyGlm::vec3<float>(ray.origin + ray_dir_normal * result.distance);
		result.obj = this;
		result.normal = TinyGlm::vec3<float>(result.coords - center).normalize();
		result.shader = shader;
	}


	return result;
}

void Sphere::GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const
{
	normal = (pos - center).normalize();
}

Bound Sphere::GetBound()
{
	return Bound(TinyGlm::vec3<float>(center.x - radius, center.y - radius, center.z - radius), TinyGlm::vec3<float>(center.x + radius, center.y + radius, center.z + radius));
}
