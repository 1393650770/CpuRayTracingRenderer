#include "IShader.h"
#include <random>

IShader::IShader()
{
}

IShader::~IShader()
{
}
TinyGlm::vec3<float> IShader::toWorld(const TinyGlm::vec3<float>& a, const TinyGlm::vec3<float>& N)
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

float IShader::get_random_float()
{
    std::random_device dev;
    std::mt19937 random_seed(dev());
    std::uniform_real_distribution<float> ran(0.f, 1.0f);
    return ran(random_seed);
}

