#pragma once
#ifndef _UTILS_
#define _UTILS_
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
};
#endif //_UTILS_

