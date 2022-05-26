#pragma once
#ifndef _RECTANGLES_
#define _RECTANGLES_
#include"Object.h"

class IShader;

class Rectangles:public Object
{
private:
public:
	TinyGlm::vec3<float> A,B,C,D;
	TinyGlm::vec3<float>  S, T;
	TinyGlm::vec3<float> normal;
	std::shared_ptr<IShader> shader;
	float area;

	Rectangles()=default;
	Rectangles(TinyGlm::vec3<float> _x0, TinyGlm::vec3<float> _x1, TinyGlm::vec3<float> _z0, TinyGlm::vec3<float> _z1, std::shared_ptr<IShader> mat);
	virtual ~Rectangles();

	bool CheckIsIntersect(const Ray& ray) override;
	Intersection GetIntersection(Ray& ray) override;
	void GetSurfaceProperties(const TinyGlm::vec3<float>& pos, const TinyGlm::vec3<float>& I, const uint32_t& index, const TinyGlm::vec2<float>& uv, TinyGlm::vec3<float>& normal, TinyGlm::vec2<float>& st) const override;
	Bound GetBound() override;

	//均匀采样 ， TODO：重要性采样
	float GetPdf(const TinyGlm::vec3<float>& income_light, const float dis) override;

	Intersection GetSampleInfo() override;

};



#endif //_RECTANGLES_

