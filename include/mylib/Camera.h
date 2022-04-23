#pragma once
#ifndef _CANERA_
#define _CANERA_

#include"TinyGlm.h"
extern template class TinyGlm::vec4<float>;
extern template class TinyGlm::vec3<float>;
extern template class TinyGlm::vec2<float>;

class Camera
{
private:
	TinyGlm::vec3<float> camera_pos;
	TinyGlm::vec3<float> camera_front;
	TinyGlm::vec3<float> camera_right;
	TinyGlm::vec3<float> camera_up;
public:
	Camera(TinyGlm::vec3<float> camerapos);
	TinyGlm::mat4<float> GetViewMatrix();

};
#endif //_CANERA_
