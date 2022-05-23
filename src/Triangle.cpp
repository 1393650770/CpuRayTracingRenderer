#include "Triangle.h"
#include "IShader.h"
#include "TinyGlm.h"
#include "BVH.h"
#include "OBJLoader.h"
#include <Utils.h>


Triangle::Triangle(TinyGlm::vec3<float> v0, TinyGlm::vec3<float> v1, TinyGlm::vec3<float> v2, std::shared_ptr<IShader> mat):vertices0(v0),vertices1(v1),vertices2(v2)
{
	edge0 = vertices1 - vertices0;
	edge1 = vertices2 - vertices0;

	TinyGlm::vec3<float> e0_cross_e1 = edge0.cross(edge1);

	normal = e0_cross_e1.normalize();
	area = e0_cross_e1.length() * 0.5f;

	shader = mat;
}

Triangle::~Triangle()
{

}

bool Triangle::CheckIsIntersect(const Ray& ray)
{
	bool result=false;
	float u, v, t = 0.0f;
	TinyGlm::vec3<float> pvec = ray.direction.cross(edge1);
	float det = edge0.dot(pvec);
	if (std::fabs(det) < std::numeric_limits<float>::epsilon())
	{
		return result;
	}
	float det_inv = 1.0f / det;
	TinyGlm::vec3<float> tvec = ray.origin - vertices0;
	u = tvec.dot(pvec) * det_inv;
	if (u < 0.0f || u > 1.0f)
		return result;
	TinyGlm::vec3<float> qvec = tvec.cross(edge0);
	TinyGlm::vec3<float> dir = ray.direction;
	v = dir.dot(qvec) * det_inv;
	if (v < 0.0f || v + u>1.0f)
		return result;
	t = edge1.dot(qvec) * det_inv;
	if (t < 0.0f)
		return result;

	result = true;
	return result;
}

Intersection Triangle::GetIntersection(Ray& ray)
{
	Intersection result;

	float u = 0.0f, v = 0.0f, t=0.0f;

	TinyGlm::vec3<float> pvec = ray.direction.cross(edge1);
	float det = edge0.dot(pvec);
	if (std::fabs(det) < -std::numeric_limits<float>::epsilon())
	{
		return result;
	}
	float det_inv = 1.0f / det;
	TinyGlm::vec3<float> tvec = ray.origin - vertices0;
	u = tvec.dot(pvec) * det_inv;
	if (u < -std::numeric_limits<float>::epsilon() || u > 0.99999999f)
		return result;
	TinyGlm::vec3<float> qvec = tvec.cross(edge0);
	v = ray.direction.dot(qvec) * det_inv;
	if (v < -std::numeric_limits<float>::epsilon() || v + u > 0.99999999f)
		return result;
	t = edge1.dot(qvec) * det_inv;
	if (t < -std::numeric_limits<float>::epsilon())
		return result;

	result.distance = t;
	result.hit = true;
	result.normal = this->normal;
	result.texture_coords = ray.origin + ray.direction * t;
	result.obj = this;
	result.shader = this->shader;
	return result;
}

void Triangle::GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const
{
	normal = this->normal;
}

Bound Triangle::GetBound()
{
	return Union(Bound(vertices0, vertices1), vertices2);
}

float Triangle::GetPdf()
{
	return 0.0f;
}

Intersection Triangle::GetSampleInfo()
{
	Intersection result;
	float x = std::sqrt(Utils::get_random_float()), y = Utils::get_random_float();
	result.coords = vertices0 * (1.0f - x) + vertices1 * (x * (1.0f - y)) + vertices2 * (x * y);
	result.normal = this->normal;
	result.emition = TinyGlm::vec3<float>(shader->emittion_color.x, shader->emittion_color.y, shader->emittion_color.z);
	result.shader = shader;
	return result;
}

MeshTriangle::MeshTriangle(const std::string& filename, std::shared_ptr<IShader> mt)
{
	objl::Loader loader;
	loader.LoadFile(filename);
	area = 0;
	shader = mt;
	assert(loader.LoadedMeshes.size() == 1);
	auto mesh = loader.LoadedMeshes[0];

	TinyGlm::vec3<float> min_vert = TinyGlm::vec3<float>{ std::numeric_limits<float>::infinity(),
								 std::numeric_limits<float>::infinity(),
								 std::numeric_limits<float>::infinity() };
	TinyGlm::vec3<float> max_vert = TinyGlm::vec3<float>{ -std::numeric_limits<float>::infinity(),
								 -std::numeric_limits<float>::infinity(),
								 -std::numeric_limits<float>::infinity() };
	for (int i = 0; i < mesh.Vertices.size(); i += 3) 
	{
		std::vector<TinyGlm::vec3<float>> face_vertices(3);

		for (int j = 0; j < 3; j++) {
			auto vert = TinyGlm::vec3<float>(mesh.Vertices[i + j].Position.X,
				mesh.Vertices[i + j].Position.Y,
				mesh.Vertices[i + j].Position.Z);
			face_vertices[j] = vert;

			min_vert = TinyGlm::vec3<float>(std::min(min_vert.x, vert.x),
				std::min(min_vert.y, vert.y),
				std::min(min_vert.z, vert.z));
			max_vert = TinyGlm::vec3<float>(std::max(max_vert.x, vert.x),
				std::max(max_vert.y, vert.y),
				std::max(max_vert.z, vert.z));
		}

		triangles.emplace_back(face_vertices[0], face_vertices[1],
			face_vertices[2], mt);
	}

	bounding_box = Bound(min_vert, max_vert);

	for (auto& tri : triangles) 
	{
		std::shared_ptr<Triangle> t = std::make_shared<Triangle>(tri);

		ptrs.push_back(t);
		area += tri.area;
	}
	bvh = new BVH(ptrs);
}

MeshTriangle::~MeshTriangle()
{
	delete bvh;
}

bool MeshTriangle::CheckIsIntersect(const Ray& ray)
{
	Intersection result;

	if (bvh)
	{
		Ray ray_temp = ray;
		result = bvh->GetIntersection(ray_temp, bvh->root);
	}

	return result.hit;
}

Intersection MeshTriangle::GetIntersection(Ray& ray)
{
	Intersection result;

	if (bvh) 
	{
		result = bvh->GetIntersection(ray,bvh->root);
	}

	return result;
}

void MeshTriangle::GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const
{
	const TinyGlm::vec3<float>& v0 = vertices[vertexIndex[index * 3]];
	const TinyGlm::vec3<float>& v1 = vertices[vertexIndex[index * 3 + 1]];
	const TinyGlm::vec3<float>& v2 = vertices[vertexIndex[index * 3 + 2]];
	TinyGlm::vec3<float> e0 =(v1 - v0).normalize();
	TinyGlm::vec3<float> e1 =(v2 - v1).normalize();
	normal = e0.cross(e1).normalize();
	const TinyGlm::vec2<float>& st0 = stCoordinates[vertexIndex[index * 3]];
	const TinyGlm::vec2<float>& st1 = stCoordinates[vertexIndex[index * 3 + 1]];
	const TinyGlm::vec2<float>& st2 = stCoordinates[vertexIndex[index * 3 + 2]];
	st = st0 * (1 - uv.x - uv.y) + st1 * uv.x + st2 * uv.y;
}

Bound MeshTriangle::GetBound()
{
	return bounding_box;
}

float MeshTriangle::GetPdf()
{
	return 0.0f;
}

Intersection MeshTriangle::GetSampleInfo()
{
	return  bvh->GetSampleInfo();
}

