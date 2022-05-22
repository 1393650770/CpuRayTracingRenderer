#pragma once
#ifndef _ISHADER_
#define _ISHADER_
#include "TinyGlm.h"

class IShader
{
public:
	TinyGlm::vec4<float> emittion_color;
	TinyGlm::vec3<float> f0;
	float roughness;
	float metallicity;
	bool is_emit_light;
	IShader();
	virtual ~IShader();
	//���������ɫ
	virtual TinyGlm::vec4<float> Shading(TinyGlm::vec3<float> wi , TinyGlm::vec3<float> wo , TinyGlm::vec3<float> normal)=0;
	//��ȡ��ӹ�ķ���
	virtual TinyGlm::vec3<float> GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal)=0;
	//��Ҫ�Բ���
	virtual float GetPdf(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal)=0;

};

#endif //_ISHADER_

