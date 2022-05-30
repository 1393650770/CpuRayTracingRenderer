#include "PostProcessHandle.h"
#include"IPostProcess.h"

void PostProcessHandle::AddPostProcess(std::shared_ptr<IPostProcess> postprocess)
{
	postprocess_list.push_back(postprocess);
}

void PostProcessHandle::Execute(std::vector< std::vector<TinyGlm::vec3 <float>>>& framebuffer_list)
{
	for (auto& postprocess : postprocess_list)
	{
		postprocess->ExecutePostProcess(framebuffer_list);
	}
}
