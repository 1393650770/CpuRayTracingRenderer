#include "Rectangles.h"
#include"Bound.h"
#include"IShader.h"


Rectangles_XZ::Rectangles_XZ(float _x0, float _x1, float _z0, float _z1, float _k, TinyGlm::vec3<float> _normal, E_Rectangles_Type _type, std::shared_ptr<IShader> mat):x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k),normal(_normal),type(_type),shader(mat)
{

}

Rectangles_XZ::~Rectangles_XZ()
{
}

bool Rectangles_XZ::CheckIsIntersect(const Ray& ray)
{
	return false;
}

Intersection Rectangles_XZ::GetIntersection(Ray& ray)
{
	float t = (k - ray.origin.y) / ray.direction.y;

	return Intersection();
}

void Rectangles_XZ::GetSurfaceProperties(const TinyGlm::vec3<float>&, const TinyGlm::vec3<float>&, const uint32_t&, const TinyGlm::vec2<float>&, TinyGlm::vec3<float>&, TinyGlm::vec2<float>&) const
{
}

Bound Rectangles_XZ::GetBound()
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
