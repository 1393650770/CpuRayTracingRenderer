#pragma once
#ifndef _IPOSTPROCESS_
#define _IPOSTPROCESS_
#include<vector>
#include<TinyGlm.h>

//post process interface
class IPostProcess
{
private:
public:
	virtual void ExecutePostProcess(std::vector< std::vector<TinyGlm::vec3 <float>>>& framebuffer)=0;
};

#endif //_IPOSTPROCESS_

