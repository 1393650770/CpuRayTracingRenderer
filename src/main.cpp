#include<SDL.h>
#include"TinyGlm.h"
#include"ThreadPool.h"
#include"Ray.h"
#include"Sphere.h"
#include"Scene.h"
#include"InputHandle.h"
#include"Renderer.h"
#include"PublicSingleton.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#include<Windows.h>

#ifdef	_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define M_PI 3.1415926
void TestTinyGlm();
void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

 int SceneWidth=1440, SceneHeight = 720;

 void InitThreadPool();

int main(int argc, char* argv[])
{
	EnableMemLeakCheck();

	Scene scene(SceneWidth, SceneHeight);
	Renderer render(scene.width, scene.height);
	InputHandle input;

	//Init the Thread Pool
	InitThreadPool();

	std::shared_ptr<Sphere>  sphere = std::make_shared<Sphere>(TinyGlm::vec3<float>(0, 0, -1), 0.5f);

	scene.Add(sphere);

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





void TestTinyGlm()
{
	TinyGlm::vec3<float> a(1, 1, 1);
	TinyGlm::vec3<float> b(2, 2, 2);
	TinyGlm::vec3<float> c(3, 3, 3);

	TinyGlm::vec3<float> d;
	d = a + b;
	std::cout << " a+b :" << d.x << " " << d.y << " " << d.z << std::endl;

	a /= 2;
	std::cout << " a/= :" << a.x << " " << a.y << " " << a.z << std::endl;

	a *= 5;
	std::cout << " a*= :" << a.x << " " << a.y << " " << a.z << std::endl;

	d = d.normalize();
	std::cout << " d.normalize :" << d.x << " " << d.y << " " << d.z << std::endl;

	d = a.cross(b);
	std::cout << " a.cross(b) :" << d.x << " " << d.y << " " << d.z << std::endl;

	float k = a.dot(b);
	std::cout << " a.dot(b) :" << k << std::endl;

	TinyGlm::vec4<float> e(1, 1, 1);
	TinyGlm::vec4<float> f(2, 2, 2);
	TinyGlm::vec4<float> g(3, 3, 3);

	TinyGlm::vec3<float> h;
	h = e + f;
	std::cout << " a+b :" << h.x << " " << h.y << " " << h.z << std::endl;

	e /= 2;
	std::cout << " a/= :" << e.x << " " << e.y << " " << e.z << std::endl;

	e *= 5;
	std::cout << " a*= :" << e.x << " " << e.y << " " << e.z << std::endl;

	h = h.normalize();
	std::cout << " d.normalize :" << h.x << " " << h.y << " " << h.z << std::endl;

	h = e.cross(f);
	std::cout << " a.cross(b) :" << h.x << " " << h.y << " " << h.z << std::endl;

	float l = e.dot(f);
	std::cout << " a.dot(b) :" << l << std::endl;

	TinyGlm::vec2<float> x(1.0f, 0.0f);
	TinyGlm::vec2<float> y(0.0f, 1.0f);

	TinyGlm::vec3<float> crossXY = x.cross(y);
	std::cout << "x.cross(y) :" << crossXY.x << " " << crossXY.y << " " << crossXY.z << std::endl;

	TinyGlm::mat4<float> mat4;
	mat4 *= 0.4f;
	std::cout << "mat4 :" << mat4.val[0] << " " << mat4.val[5] << " " << mat4.val[10] << " " << mat4.val[15] << std::endl;

	TinyGlm::vec4<float> m(1.0f, 1.0f, 1.0f);
	mat4.val[10] = 100.0f;
	m = mat4 * m;
	std::cout << " m = mat4 * m:" << m.x << " " << m.y << " " << m.z << std::endl;

	TinyGlm::mat4<float> matTest;
	matTest *= 0.4f;
	float det = matTest.determinant();
	std::cout << " mat.det :" << det << std::endl;
	mat4 = matTest.inverse();
	std::cout << "mat4 inverse :" << mat4.val[0] << " " << mat4.val[5] << " " << mat4.val[10] << " " << mat4.val[15] << std::endl;

	TinyGlm::mat4<float> matTest2;
	matTest2 *= 0.4f;
	matTest2.val[3] = 0.5f;
	mat4 = matTest2.transpose();
	std::cout << "mat4 transpose :" << mat4.val[0] << " " << mat4.val[5] << " " << mat4.val[10] << " " << mat4.val[15] << " " << mat4.val[12] << std::endl;

}

void InitThreadPool()
{

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int cpu_core_num = sysInfo.dwNumberOfProcessors;
	PublicSingleton<ThreadPool>::get_instance().Init(cpu_core_num*2);
}
