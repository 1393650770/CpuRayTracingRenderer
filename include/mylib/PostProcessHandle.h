#pragma once
#ifndef _IPOSTPROCESSHANDLE_
#define _IPOSTPROCESSHANDLE_
#include <vector>
#include<TinyGlm.h>

class IPostProcess;

class PostProcessHandle
{
private:
	std::vector<IPostProcess*> postprocess_list;
public:
	void AddPostProcess(IPostProcess* postprocess);
	void Execute(std::vector<TinyGlm::vec3 <float>>& framebuffer);
};

#endif //_IPOSTPROCESSHANDLE_

