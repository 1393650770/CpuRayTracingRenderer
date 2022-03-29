#pragma once
#ifndef _RAH_
#define _RAH_
#include"TinyGlm.h"

class Ray
{
private:
	

public:
	TinyGlm::vec3<float> origin;
	TinyGlm::vec3<float> direction;
	float t;
	float t_min;
	float t_max;
	Ray(const TinyGlm::vec3<float>& ori, const TinyGlm::vec3<float>& dir,const float _t=0.0f);
	virtual ~Ray();
};

#endif //_RAH_
