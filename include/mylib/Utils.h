#pragma once
#ifndef _UTILS_
#define _UTILS_

#include "TinyGlm.h"

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
};
#endif //_UTILS_

