#pragma once
#ifndef _DIELECTRICMATERIAL_
#define _DIELECTRICMATERIAL_
#include <IShader.h>

class DielectricMaterial :
    public IShader
{
protected:
    int in_num = 1.5046f,out_num=1.000027f;

public:

    DielectricMaterial(const TinyGlm::vec4<float>& emit_color, const TinyGlm::vec3<float>& _f0, float _roughness, float _metallicity, bool _is_emit_light = false);
    
    virtual ~DielectricMaterial();
    //计算着色接口
    TinyGlm::vec4<float> Shading(TinyGlm::vec3<float> wi, TinyGlm::vec3<float> wo, TinyGlm::vec3<float> normal) override;

    //获取间接光的方向
    TinyGlm::vec3<float> GetInDirSample(const TinyGlm::vec3<float> wi, const TinyGlm::vec3<float> normal) override;

    //重要性采样
    float GetPdf(const TinyGlm::vec3<float>& income_view, const TinyGlm::vec3<float>& out_light, const TinyGlm::vec3<float>& normal) override;

};

#endif //_DIELECTRICMATERIAL_

