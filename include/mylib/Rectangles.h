#pragma once
#ifndef _RECTANGLES_
#define _RECTANGLES_
#include"Object.h"

class IShader;

enum E_Rectangles_Type
{
	None=0,
	XZ,
	YZ
};

class Rectangles_XZ:public Object
{
private:
public:
	float x0, x1, z0, z1, k;
	TinyGlm::vec3<float> normal;
	std::shared_ptr<IShader> shader;
	E_Rectangles_Type type;

	Rectangles_XZ()=default;
	Rectangles_XZ(float _x0, float _x1, float _z0, float _z1, float _k, TinyGlm::vec3<float> _normal, E_Rectangles_Type _type,std::shared_ptr<IShader> mat);
	virtual ~Rectangles_XZ();

	bool CheckIsIntersect(const Ray& ray) override;
	Intersection GetIntersection(Ray& ray) override;
	void GetSurfaceProperties(const TinyGlm::vec3<float>&, const TinyGlm::vec3<float>&, const uint32_t&, const TinyGlm::vec2<float>&, TinyGlm::vec3<float>&, TinyGlm::vec2<float>&) const override;
	Bound GetBound() override;

};



#endif //_RECTANGLES_

