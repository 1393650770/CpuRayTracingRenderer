#pragma once
#ifndef _IPOSTPROCESSHANDLE_
#define _IPOSTPROCESSHANDLE_
#include <vector>
#include<TinyGlm.h>

class IPostProcess;

class PostProcessHandle
{
private:
	std::vector<std::shared_ptr<IPostProcess>> postprocess_list;
public:
	PostProcessHandle() {};
	virtual ~PostProcessHandle() {};

	void AddPostProcess(std::shared_ptr<IPostProcess> postprocess);
	void Execute(std::vector< std::vector<TinyGlm::vec3 <float>>>& framebuffer_list);
};

#endif //_IPOSTPROCESSHANDLE_

