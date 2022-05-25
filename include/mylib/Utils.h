#pragma once
#ifndef _UTILS_
#define _UTILS_

#define PI 3.1415926f

#include "TinyGlm.h"
#include <random>

static std::random_device dev;
static std::mt19937 random_seed(dev());
static std::uniform_real_distribution<float> ran(0.f, 1.0f);

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



    static TinyGlm::vec3<float> toWorld(const TinyGlm::vec3<float>& a, const TinyGlm::vec3<float>& N) 
    {
        //施密特正交化重建坐标系
        //TinyGlm::vec3<float> B, C;
        //auto temp = std::fabs(N.x) > 0.01 ? TinyGlm::vec3<float>(0.f, 1.f, 0.f) : TinyGlm::vec3<float>(1.f, 0.f, 0.f);
        //B = (temp - temp.dot(N) * N).normalize();
        //C = B.cross(N);

        //return a.x * B + a.y * C + a.z * N;

        TinyGlm::vec3<float> B, C;
        if (std::fabs(N.x) > std::fabs(N.y)) {
            float invLen = 1.0f / std::sqrt(N.x * N.x + N.z * N.z);
            C = TinyGlm::vec3<float>(N.z * invLen, 0.0f, -N.x * invLen);
        }
        else {
            float invLen = 1.0f / std::sqrt(N.y * N.y + N.z * N.z);
            C = TinyGlm::vec3<float>(0.0f, N.z * invLen, -N.y * invLen);
        }
        B = C.cross(N);
        return a.x * B + a.y * C + a.z * N;

        //TinyGlm::vec3<float> T, B;
        //T = N.cross(TinyGlm::vec3<float>(N.z, 0.0, -N.x));
        //B = N.cross(B);
        //T = T.normalize();
        //B = T.normalize();
        //return (a.x * B + a.y * T + a.z * N).normalize();
    }



    static float get_random_float()
    {
        return ran(random_seed);
    }

    static TinyGlm::vec3<float> lerp(TinyGlm::vec3<float>& a, TinyGlm::vec3<float>& b, float m)
    {
        m = std::clamp(m, 0.0f, 1.0f);
        float x1 = a.x * (1.0f - m) + b.x * (m);
        float x2 = a.y * (1.0f - m) + b.y * (m);
        float x3 = a.z * (1.0f - m) + b.z * (m);

        return TinyGlm::vec3<float>(x1, x2, x3);

    }

};
#endif //_UTILS_

