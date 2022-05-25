#include<SDL.h>
#include"TinyGlm.h"
#include"ThreadPool.h"
#include"Ray.h"
#include"Sphere.h"
#include"Scene.h"
#include"Triangle.h"
#include"Rectangles.h"
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

	//-----------------Scene-----------------
	Scene scene(SceneWidth, SceneHeight);

	//-----------------Renderer-----------------
	Renderer render(scene.width, scene.height);

	//-----------------Controller£¨·ÏÆú£©-----------------
	InputHandle input;

	// Cornell Box Point
	//       D__________C
	//      /|         /|
	//     / |   ¡ý   / |
	//   A/__|_______/B |
	//    | H|_______|__|G
	//    |  /       |  /
	//    | /    ¡ü  | /
	//   E|/_________|/F

	TinyGlm::vec3<float> A = TinyGlm::vec3<float>(-50.f, 1.5f, -50.f);
	TinyGlm::vec3<float> B = TinyGlm::vec3<float>(50.f, 1.5f, -50.f);
	TinyGlm::vec3<float> C = TinyGlm::vec3<float>(50.f, 1.5f, 50.f);
	TinyGlm::vec3<float> D = TinyGlm::vec3<float>(-50.f, 1.5f, 50.f);
	TinyGlm::vec3<float> E = TinyGlm::vec3<float>(-50.f, -1.5f, -50.f);
	TinyGlm::vec3<float> F = TinyGlm::vec3<float>(50.f, -1.5f, -50.f);
	TinyGlm::vec3<float> G = TinyGlm::vec3<float>(50.f, -1.5f, 50.f);
	TinyGlm::vec3<float> H = TinyGlm::vec3<float>(-50.f, -1.5f, 50.f);

	//Material
	std::shared_ptr<PBRMaterial>  shader1 = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.63f, 0.065f, 0.05f), TinyGlm::vec3<float>(0.3f, 0.1f, 0.7f),0.15f,0.2f);
	std::shared_ptr<PBRMaterial>  red = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.65f, 0.05f, 0.05f), TinyGlm::vec3<float>(0.9f, 0.5f, 0.3f), 0.02f, 0.2f);
	std::shared_ptr<PBRMaterial>  white = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.75f, 0.75f, 0.75f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.2f);
	std::shared_ptr<PBRMaterial>  Test = std::make_shared<PBRMaterial>(TinyGlm::vec4<float>(0.12f, 0.45f, 0.15f), TinyGlm::vec3<float>(1.0f,1.0f, 1.0f), 0.01f, 0.7f);

	std::shared_ptr<DiffuseMaterial>  white_diffuse = std::make_shared<DiffuseMaterial>(TinyGlm::vec4<float>(0.75f, 0.75f, 0.75f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.2f);
	std::shared_ptr<DiffuseMaterial>  green_diffuse = std::make_shared<DiffuseMaterial>(TinyGlm::vec4<float>(0.12f, 0.45f, 0.15f), TinyGlm::vec3<float>(0.1f, 0.7f, 0.01f), 0.02f, 0.8f);
	std::shared_ptr<DiffuseMaterial>  red_diffuse = std::make_shared<DiffuseMaterial>(TinyGlm::vec4<float>(0.65f, 0.05f, 0.05f), TinyGlm::vec3<float>(0.9f, 0.5f, 0.3f), 0.02f, 0.2f);

	TinyGlm::vec4<float> lightcolor = ( TinyGlm::vec4<float>(0.747f + 0.058f, 0.747f + 0.258f, 0.747f) * 8.0f  +  TinyGlm::vec4<float>(0.740f + 0.287f, 0.740f + 0.160f, 0.740f) * 15.6f +  TinyGlm::vec4<float>(0.737f + 0.642f, 0.737f + 0.159f, 0.737f) * 18.4f);
	std::shared_ptr<DiffuseMaterial> light = std::make_shared<DiffuseMaterial>(TinyGlm::vec4<float>(35.f, 35.f,35.f), TinyGlm::vec3<float>(0.9f, 0.5f, 0.3f), 0.02f, 0.2f, true);

	//-----------------Object-----------------
	
	// Sphere simulates the Cornell box
	std::shared_ptr<Sphere>  right = std::make_shared<Sphere>(TinyGlm::vec3<float>(1051.5f, 0.f, 0.f), 1050.f, red_diffuse);
	std::shared_ptr<Sphere>  left = std::make_shared<Sphere>(TinyGlm::vec3<float>(-1051.5f, 0.f, 0.f), 1050.f, green_diffuse);
	std::shared_ptr<Sphere>  forward = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 0.f, 1056.f), 1050.f, white_diffuse);
	std::shared_ptr<Sphere>  up = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 1051.5f,0.f), 150.f, white_diffuse);
	std::shared_ptr<Sphere>  down = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -1051.5f, 0.f), 1050.f, white_diffuse);
	
	// Rectangles simulates the Cornell box (Todo)
	//std::shared_ptr<Rectangles>  up = std::make_shared<Rectangles>(A, B,C, D, white_diffuse);
	//std::shared_ptr<Rectangles>  down = std::make_shared<Rectangles>(H,G,F,E, white_diffuse);
	//std::shared_ptr<Rectangles>  left = std::make_shared<Rectangles>(D,H,E,A, green_diffuse);
	//std::shared_ptr<Rectangles>  right = std::make_shared<Rectangles>(C,B,F,G, red_diffuse);
	//std::shared_ptr<Rectangles>  forward = std::make_shared<Rectangles>(H,D,C,G, white_diffuse);

	//Sphere
	//std::shared_ptr<Sphere>  sphere1 = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -401.5f, 2.f), 400.0f, white_diffuse);
	std::shared_ptr<Sphere>  sphere2 = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -1.f, 4.5f), 0.5f, Test);


	//Light
	std::shared_ptr<Sphere>  point_light = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 0.5f, 5.f),0.2f, light);
	std::shared_ptr<Rectangles>  rectangle_light = std::make_shared<Rectangles>(TinyGlm::vec3<float>(-0.5f, 1.5f, 4.25f), TinyGlm::vec3<float>(0.5f, 1.5f, 4.25f), TinyGlm::vec3<float>(0.5f, 1.5f, 4.75f), TinyGlm::vec3<float>(-0.5f, 1.5f, 4.75f), light);

	/*new Test
	// Sphere simulates the Cornell box
	std::shared_ptr<Sphere>  right = std::make_shared<Sphere>(TinyGlm::vec3<float>(5035.5f, 0.f, 100.f), 5000.f, red_diffuse);
	std::shared_ptr<Sphere>  left = std::make_shared<Sphere>(TinyGlm::vec3<float>(-5035.5f, 0.f, 100.f), 5000.f, green_diffuse);
	std::shared_ptr<Sphere>  forward = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 0.f, 5116.f), 5000.f, white_diffuse);
	std::shared_ptr<Sphere>  up = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 5031.5f, 100.f), 5000.f, white_diffuse);
	std::shared_ptr<Sphere>  down = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, -5031.5f, 100.f), 5000.f, white_diffuse);

	//Light
	std::shared_ptr<Sphere>  point_light = std::make_shared<Sphere>(TinyGlm::vec3<float>(0.f, 28.f, 100.f), 10.f, light);
	std::shared_ptr<Rectangles>  rectangle_light = std::make_shared<Rectangles>(TinyGlm::vec3<float>(-10.5f, 30.5f, 85.25f), TinyGlm::vec3<float>(10.5f, 30.5f, 85.25f), TinyGlm::vec3<float>(10.5f, 30.5f, 95.75f), TinyGlm::vec3<float>(-10.5f, 30.5f, 95.75f), light);
	*/

	//Init the Thread Pool
	InitThreadPool();

	//Add Object
	scene.AddObj(right);
	scene.AddObj(left);
	scene.AddObj(forward);
	scene.AddObj(up);
	scene.AddObj(down);

	//scene.AddObj(sphere1);
	scene.AddObj(sphere2);


	//Add Light
	//scene.AddLight(point_light);
	scene.AddLight(rectangle_light);


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
