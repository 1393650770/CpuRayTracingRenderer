#include "Rectangles.h"
#include"Bound.h"
#include"IShader.h"
#include"Utils.h"

Rectangles::Rectangles(TinyGlm::vec3<float> _x0, TinyGlm::vec3<float> _x1, TinyGlm::vec3<float> _z0, TinyGlm::vec3<float> _z1, std::shared_ptr<IShader> mat) :A(_x0), B(_x1), C(_z0), D(_z1), shader(mat)
{
	//�ٶ�CCW
	S =  B - A  ;
	T =  B - C  ;
	TinyGlm::vec3<float> AB_cross_CB = (S.cross(T));
	area = AB_cross_CB.length();
	normal = AB_cross_CB.normalize();

}

Rectangles::~Rectangles()
{
}

bool Rectangles::CheckIsIntersect(const Ray& ray)
{
	float t = (A - ray.origin).dot(normal) * (1 / normal.dot(ray.direction));
	if (t < 0.00001f)
	{
		return false;
	}

	TinyGlm::vec3<float> point = ray.origin + ray.direction * t;

	TinyGlm::vec3<float> max_vec = TinyGlm::vec3<float>::max(TinyGlm::vec3<float>::max(A, B), TinyGlm::vec3<float>::max(C, D));
	TinyGlm::vec3<float> min_vec = TinyGlm::vec3<float>::min(TinyGlm::vec3<float>::min(A, B), TinyGlm::vec3<float>::min(C, D));

	//������ھ�����
	if (min_vec.x - point.x > std::numeric_limits<float>::epsilon() || point.x - max_vec.x > std::numeric_limits<float>::epsilon() ||
		min_vec.y - point.y > std::numeric_limits<float>::epsilon() || point.y - max_vec.y > std::numeric_limits<float>::epsilon() ||
		min_vec.z - point.z > std::numeric_limits<float>::epsilon() || point.z - max_vec.z > std::numeric_limits<float>::epsilon())
	{
		return false;
	}

	return true;
}

Intersection Rectangles::GetIntersection(Ray& ray)
{
	Intersection result;

	//ƽ�����
	float t = (A - ray.origin).dot(normal) * (1.0f / normal.dot(ray.direction));
	if (t < 0.00001f)
	{
		return result;
	}

	TinyGlm::vec3<float> point = ray.origin + ray.direction * t;

	TinyGlm::vec3<float> max_vec = TinyGlm::vec3<float>::max(TinyGlm::vec3<float>::max(A, B), TinyGlm::vec3<float>::max(C, D));
	TinyGlm::vec3<float> min_vec = TinyGlm::vec3<float>::min(TinyGlm::vec3<float>::min(A, B), TinyGlm::vec3<float>::min(C, D));

	//������ھ�����
	if (min_vec.x - point.x > std::numeric_limits<float>::epsilon() || point.x - max_vec.x > std::numeric_limits<float>::epsilon() ||
		min_vec.y - point.y > std::numeric_limits<float>::epsilon() || point.y - max_vec.y > std::numeric_limits<float>::epsilon() ||
		min_vec.z - point.z > std::numeric_limits<float>::epsilon() || point.z - max_vec.z > std::numeric_limits<float>::epsilon())
	{
		return result;
	}


	result.coords = point;
	result.distance = t;
	result.obj = this;
	result.normal = this->normal;
	result.shader = shader;
	result.hit = true;
	result.emition = TinyGlm::vec3<float>(shader->emittion_color.x, shader->emittion_color.y, shader->emittion_color.z);
	
	return result;
}

void Rectangles::GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const
{
	normal = this->normal;
}

Bound Rectangles::GetBound()
{
	return Union( Union(Bound(A,B) ,C ), D );
}

float Rectangles::GetPdf()
{
	return 1.0f/area;
}

Intersection Rectangles::GetSampleInfo()
{
	Intersection result;
	result.coords = A + S * Utils::get_random_float() + T * Utils::get_random_float();
	result.shader = this->shader;
	result.normal = this->normal;
	result.emition = TinyGlm::vec3<float>(shader->emittion_color.x, shader->emittion_color.y, shader->emittion_color.z);
	return result;
}
