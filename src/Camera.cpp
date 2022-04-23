#include "Camera.h"

Camera::Camera(TinyGlm::vec3<float> camerapos)
{
	camera_pos = camerapos;
}

TinyGlm::mat4<float> Camera::GetViewMatrix()
{
	TinyGlm::mat4<float> result;
	return result;
}
