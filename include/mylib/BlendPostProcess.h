#pragma once
#ifndef _BLENDPOSTPROCESS_
#define _BLENDPOSTPROCESS_


#include"IPostProcess.h"

class BlendPostProcess :
    public IPostProcess
{
private:


public:
    BlendPostProcess();
    virtual ~BlendPostProcess();
    void ExecutePostProcess(std::vector< std::vector<TinyGlm::vec3 <float>>>& framebuffer) override;

};

#endif // _BLENDPOSTPROCESS_