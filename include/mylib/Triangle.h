#pragma once
#ifndef _TRIANGLE_
#define _TRIANGLE_
#include"Object.h"
#include"TinyGlm.h"
#include"OBJLoader.h"
class IShader;
class BVH;


class Triangle :
	public Object
{
private:
public:
	Triangle(TinyGlm::vec3<float> v0, TinyGlm::vec3<float> v1, TinyGlm::vec3<float> v2, std::shared_ptr<IShader> mat );
	virtual ~Triangle();
	TinyGlm::vec3<float> vertices0, vertices1, vertices2;
	TinyGlm::vec3<float> edge0, edge1;
	TinyGlm::vec3<float> texture_vertices0, texture_vertices1, texture_vertices2;
	TinyGlm::vec3<float> normal;
	float area;
	std::shared_ptr<IShader> shader;

	bool CheckIsIntersect(const Ray& ray) override;
	Intersection GetIntersection( Ray& ray) override;
	Bound GetBound() override;
	void GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const override;
};


class MeshTriangle : public Object
{
public:
	Bound bounding_box;
	std::unique_ptr<TinyGlm::vec3<float>[]> vertices;
	uint32_t numTriangles;
	std::unique_ptr<uint32_t[]> vertexIndex;
	std::unique_ptr<TinyGlm::vec2<float>[]> stCoordinates;

	std::vector<Triangle> triangles;
	BVH* bvh;
	float area;
	std::shared_ptr<IShader>* m;

    MeshTriangle(const std::string& filename, std::shared_ptr<IShader>* mt);
    virtual ~MeshTriangle();

	bool CheckIsIntersect(const Ray& ray) override;
	Intersection GetIntersection(Ray& ray) override;
	Bound GetBound() override;
	void GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const override;


};

#endif //

