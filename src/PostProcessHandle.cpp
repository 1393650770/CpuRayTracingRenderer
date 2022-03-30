#include "PostProcessHandle.h"
#include"IPostProcess.h"

void PostProcessHandle::AddPostProcess(IPostProcess* postprocess)
{
	postprocess_list.push_back(postprocess);
}

void PostProcessHandle::Execute(std::vector<TinyGlm::vec3 <float>>& framebuffer)
{
	for (auto& postprocess : postprocess_list)
	{
		postprocess->ExecutePostProcess(framebuffer);
	}
}
