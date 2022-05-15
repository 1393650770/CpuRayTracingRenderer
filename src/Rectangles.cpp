#include "Rectangles.h"
#include"Bound.h"
#include"IShader.h"


Rectangles::Rectangles(float _x0, float _x1, float _z0, float _z1, float _k, TinyGlm::vec3<float> _normal, E_Rectangles_Type _type, std::shared_ptr<IShader> mat):x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k),normal(_normal),type(_type),shader(mat)
{

}

Rectangles::~Rectangles()
{
}

bool Rectangles::CheckIsIntersect(const Ray& ray)
{
	return false;
}

Intersection Rectangles::GetIntersection(Ray& ray)
{
	float t = (k - ray.origin.y) / ray.direction.y;
	float x, z;
	if (type == E_Rectangles_Type::XZ)
	{
		x = ray.origin.x + t * ray.direction.x;
	}
	else if (type == E_Rectangles_Type::YZ)
	{
		x = ray.origin.y + t * ray.direction.y;
	}

	z= ray.origin.z + t * ray.direction.z;
	Intersection result;
	if (x<x0 || x>x1 || z<z0 || z>z1)
	{
		return result;
	}
	result.distance = t;
	result.coords = TinyGlm::vec3<float>(ray.origin + ray.direction * result.distance);
	result.obj = this;
	result.normal = this->normal.normalize();
	result.shader = shader;


	return result;
}

void Rectangles::GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const
{
	normal = this->normal;
}

Bound Rectangles::GetBound()
{
	if (type == E_Rectangles_Type::XZ)
	{
		return Bound(TinyGlm::vec3<float>(x0,k-0.0001f,z0), TinyGlm::vec3<float>(x1, k + 0.0001f, z1));
	}
	else if (type == E_Rectangles_Type::YZ)
	{
		return Bound(TinyGlm::vec3<float>(k - 0.0001f,x0, z0), TinyGlm::vec3<float>(k + 0.0001f, x1, z1));
	}
	return Bound();
}
