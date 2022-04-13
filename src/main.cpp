#include<SDL.h>
#include"TinyGlm.h"
#include"ThreadPool.h"
#include"Ray.h"
#include"Sphere.h"
#include"Scene.h"
#include"IShader.h"
#include"PBRMaterial.h"
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

 int SceneWidth=1200, SceneHeight = 800;

 void InitThreadPool();

int main(int argc, char* argv[])
{

	Scene scene(SceneWidth, SceneHeight);
	Renderer render(scene.width, scene.height);
	InputHandle input;
	//Init the Thread Pool
	InitThreadPool();

	std::shared_ptr<PBRMaterial>  shader1 = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.63f, 0.065f, 0.05f), TinyGlm::vec3<float>(0.3f, 0.1f, 0.7f),0.15f,0.2f);
	std::shared_ptr<PBRMaterial>  shader2 = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.14f, 0.45f, 0.091f), TinyGlm::vec3<float>(0.9f, 0.5f, 0.3f), 0.02f, 0.2f);
	std::shared_ptr<PBRMaterial>  shader3 = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.725f, 0.71f, 0.68f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.2f);
	std::shared_ptr<PBRMaterial>  shader4 = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.925f, 0.91f, 0.1f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.8f);

	std::shared_ptr<Sphere>  sphere0 = std::make_shared<Sphere>(TinyGlm::vec3<float>(300.f, 120.f, 500.f), 100.f, dynamic_cast<IShader*>(shader3.get()));
	std::shared_ptr<Sphere>  sphere1 = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 2.f, 10.f) , 1.f, dynamic_cast<IShader*>(shader3.get()));
	std::shared_ptr<Sphere>  sphere2 = std::make_shared<Sphere>(TinyGlm::vec3<float>(-2.f, 1.f, 10.f) , 1.f, dynamic_cast<IShader*>(shader2.get()));
	std::shared_ptr<Sphere>  sphere3 = std::make_shared<Sphere>(TinyGlm::vec3<float>(2.f, 5.f, 10.f), 1.f, dynamic_cast<IShader*>(shader1.get()));
	std::shared_ptr<Sphere>  sphere4 = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -200.5f,10.f), 200.f, dynamic_cast<IShader*>(shader4.get()));

	//scene.Add(sphere0);
	scene.Add(sphere1);
	scene.Add(sphere2);
	scene.Add(sphere3);
	scene.Add(sphere4);

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
