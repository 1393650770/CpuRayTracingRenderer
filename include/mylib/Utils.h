#pragma once
#ifndef _UTILS_
#define _UTILS_

#define PI 3.1415926f

#include "TinyGlm.h"
#include <random>

class Utils
{
public:
    static float clamp(float val, float min, float max)
    {
        if (val > max)
            return max;
        if (val < min)
            return min;
        return val;
    };

    static void toon_mapping(TinyGlm::vec3<float>& source)
    {
        TinyGlm::vec3<float> up_color = source + TinyGlm::vec3 < float>(0.5f);

        source = source / up_color;
    }

    static float get_random_float()
    {
        std::random_device dev;
        std::mt19937 random_seed(dev());
        std::uniform_real_distribution<float> ran(0.f, 1.0f);
        return ran(random_seed);
    }

    static TinyGlm::vec3<float> toWorld(const TinyGlm::vec3<float>& a, const TinyGlm::vec3<float>& N) 
    {
        //ʩ�����������ؽ�����ϵ
        TinyGlm::vec3<float> B, C;
        auto temp = std::fabs(N.x)>0.01? TinyGlm::vec3<float>(0.f, 1.f, 0.f) : TinyGlm::vec3<float>(1.f, 0.f, 0.f);
        B = (temp - temp.dot(N) * N).normalize();
        C = B.cross(N);
        
        return a.x * B + a.y * C + a.z * N;



        //TinyGlm::vec3<float> T, B;
        //T = N.cross(TinyGlm::vec3<float>(N.z, 0.0, -N.x));
        //B = N.cross(B);
        //T = T.normalize();
        //B = T.normalize();
        //return (a.x * B + a.y * T + a.z * N).normalize();
    }

};
#endif //_UTILS_

