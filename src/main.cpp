#include<SDL.h>
#include"TinyGlm.h"
#include"ThreadPool.h"
#include"Ray.h"
#include"Sphere.h"
#include"Scene.h"
#include"Triangle.h"
#include"IShader.h"
#include"PBRMaterial.h"
#include"DiffuseMaterial.h"
#include"InputHandle.h"
#include"Renderer.h"
#include"PublicSingleton.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<Windows.h>
	


#define M_PI 3.1415926

 int SceneWidth= 1280, SceneHeight = 800;

 void InitThreadPool();

int main(int argc, char* argv[])
{

	Scene scene(SceneWidth, SceneHeight);
	Renderer render(scene.width, scene.height);
	InputHandle input;

	std::shared_ptr<PBRMaterial>  shader1 = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.63f, 0.065f, 0.05f), TinyGlm::vec3<float>(0.3f, 0.1f, 0.7f),0.15f,0.2f);
	std::shared_ptr<PBRMaterial>  red = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.65f, 0.05f, 0.05f), TinyGlm::vec3<float>(0.9f, 0.5f, 0.3f), 0.02f, 0.2f);
	std::shared_ptr<PBRMaterial>  white = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.75f, 0.75f, 0.75f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.2f);
	std::shared_ptr<PBRMaterial>  green = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.12f, 0.45f, 0.15f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.8f);

	std::shared_ptr<DiffuseMaterial>  white_diffuse = std::make_shared<DiffuseMaterial>(TinyGlm::vec4<float>(0.75f, 0.75f, 0.75f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.2f);
	std::shared_ptr<DiffuseMaterial>  green_diffuse = std::make_shared<DiffuseMaterial>(TinyGlm::vec4<float>(0.12f, 0.45f, 0.15f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.8f);


	std::shared_ptr<Sphere>  right = std::make_shared<Sphere>(TinyGlm::vec3<float>(10500.f, 0.f, 500.f), 10000.f, red);

	std::shared_ptr<Sphere>  left = std::make_shared<Sphere>(TinyGlm::vec3<float>(-10500.f, 0.f, 500.f), 10000.f, green);

	std::shared_ptr<Sphere>  forward = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 0.f, 11200.f), 10000.f, white);

	std::shared_ptr<Sphere>  up = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 10300.f, 500.f), 10000.f, white);


	std::shared_ptr<Sphere>  sphere1 = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -100.5f, 1.f), 100.0f, white);
	std::shared_ptr<Sphere>  sphere2 = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -0.1f, 1.f), 0.1f, green);

	//Init the Thread Pool
	InitThreadPool();

	//scene.Add(right);
	//scene.Add(left);
	//scene.Add(forward);
	//scene.Add(up);

	scene.Add(sphere1);
	scene.Add(sphere2);


	scene.BuildBVH();



	while (input.is_runing)
	{
		input.ListenInput();

		render.tick(scene);
	}
	
	//Wait and close the Thread Pool
	PublicSingleton<ThreadPool>::get_instance().CloseTheadPool();

	return 0;
}





void InitThreadPool()
{

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int cpu_core_num = sysInfo.dwNumberOfProcessors;
	PublicSingleton<ThreadPool>::get_instance().Init(4, cpu_core_num);
}
