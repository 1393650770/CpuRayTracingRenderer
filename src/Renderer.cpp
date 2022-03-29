#include "Renderer.h"
#include "Sphere.h"
#include "Ray.h"
#include "Scene.h"
#include "TinyGlm.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "windows.h"
#include <cmath>
#include <iostream>
#include<fstream>

float deg2rad(const float& deg) { return deg * 3.1415926f / 180.0; }


TinyGlm::vec3<float> Color(const Ray& ray, Sphere& sphere)
{
	if (sphere.CheckIsIntersect(ray))
	{
		return TinyGlm::vec3<float>(1.0f, 0.0f, 0.0f);
	}
	return TinyGlm::vec3<float>(0.1f, 0.1f, 0.1f);
}


void RenderFrame( std::pair<int,int> x, std::pair<int, int> y, TinyGlm::vec3 <float>& eye_pos, Scene& scene, std::vector < TinyGlm::vec3 < float> >& framebuffer)
{
	int m = 0;
	int spp = 126;
	float imageAspectRatio = scene.width / (float)scene.height;
	float scale = tan(deg2rad(scene.fov * 0.5));
	for (int j = y.first; j < y.second; ++j) 
	{
		m = j * scene.width + x.first;
		for (int i = x.first; i < x.second; ++i) 
		{
			float x = (2 * (i + 0.5) / (float)scene.width - 1) *
				imageAspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)scene.height) * scale;

			TinyGlm::vec3 < float> dir = TinyGlm::vec3 < float>(-x, y, 1).normalize();
			for (int k = 0; k < spp; k++) {

				framebuffer[m] = Color(Ray(eye_pos, dir), *dynamic_cast<Sphere*>(scene.objlist[0].get()));
			}
			m++;
		}
	}
}


Renderer::Renderer(int scene_width, int scene_height)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	cpu_core_num = sysInfo.dwNumberOfProcessors;
	
	int clip_num = std::sqrt(cpu_core_num*2);
	int clip_disX = std::floor(scene_width / clip_num),clip_disY = std::floor(scene_height / clip_num);
	int minAxisX = 0, maxAxisX = 0, minAxisY = 0, maxAxisY = 0;
	for (size_t i = 0; i < clip_num; i++)
	{
		if (i + 1 == clip_num)
		{
			maxAxisX = scene_width;
			maxAxisY = scene_height;
		}
		else
		{
			maxAxisX=minAxisX + clip_disX;
			maxAxisY = maxAxisY + clip_disY;
		}

		scene_tile.push_back(std::make_pair(std::make_pair(minAxisX, maxAxisX), std::make_pair(minAxisY, maxAxisY)));
		minAxisX = maxAxisX;
		minAxisY = maxAxisY;
	}
}

Renderer::~Renderer()
{
}

void Renderer::Render(Scene& scene)
{
	auto start = std::chrono::system_clock::now();
	std::vector < TinyGlm::vec3 < float> > framebuffer(scene.width * scene.height);
	TinyGlm::vec3 < float> eye_pos(0, 0, 0);
	std::vector<std::thread> thread_list;
	for (size_t i = 0; i < scene_tile.size(); i++)
	{
		for (size_t j = 0; j < scene_tile.size(); j++)
		{
			thread_list.push_back(std::thread(RenderFrame,scene_tile[i].first , scene_tile[j].second, std::ref(eye_pos), std::ref(scene) , std::ref(framebuffer)));
		}
	}
	for (int i = 0; i < thread_list.size(); i++) 
		thread_list[i].join();
	//RenderFrame(std::make_pair(0, scene.width), std::make_pair(0, scene.height), eye_pos, scene, framebuffer);

	std::fstream fp;
	fp.open(std::string("RayTracing.ppm"), std::fstream::binary | std::fstream::out);
	if (fp.is_open())
	{
		fp << "P3\n" << scene.width << " " << scene.height << "\n255\n";
		for (auto i = 0; i < scene.height * scene.width; ++i) {
			int colorChar[3];
			colorChar[0] = (int)(255 * framebuffer[i].x);
			colorChar[1] = (int)(255 * framebuffer[i].y);
			colorChar[2] = (int)(255 * framebuffer[i].z);

			fp << colorChar[0] << " " << colorChar[1] << " " << colorChar[2] << "\n";
		}

		std::cout << "complished" << std::endl;
	}
	else
	{
		std::cout << " ERROR: Open Wrong !" << std::endl;
	}
	fp.flush();
	fp.close();
	auto stop = std::chrono::system_clock::now();
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";

}


