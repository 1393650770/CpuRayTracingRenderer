#include "BlendPostProcess.h"
#include"TinyGlm.h"
BlendPostProcess::BlendPostProcess()
{

}

BlendPostProcess::~BlendPostProcess()
{

}

void BlendPostProcess::ExecutePostProcess(std::vector<std::vector<TinyGlm::vec3<float>>>& framebuffer)
{
	float t1 = 0.8f, t2 = 0.2f;
	for (size_t i = 1; i < framebuffer.size(); i++)
	{
		for (size_t j = 0; j < framebuffer[i].size(); j++)
		{
			framebuffer[i][j] = (framebuffer[i][j] *t1)+framebuffer[i - 1][j] *t2;
		}
	}
}


