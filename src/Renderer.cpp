#include "Renderer.h"
#include "PublicSingleton.h"
#include "ThreadPool.h"
#include "Sphere.h"
#include "Ray.h"
#include "Scene.h"
#include "SDLWindows.h"
#include "TinyGlm.h"
#include "Utils.h"
#include "PostProcessHandle.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "windows.h"
#include <cmath>
#include <iostream>
#include <fstream>

#define MAXSPP 8

float deg2rad(const float& deg) { return deg * 3.1415926f / 180.0f; }


TinyGlm::vec3<float> Color(Ray& ray, Sphere& sphere)
{
	Intersection inter = sphere.GetIntersection(ray);
	if (inter.hit)
	{
		TinyGlm::vec3<float> N; 
		TinyGlm::vec3<float> I;
		int index=0;
		TinyGlm::vec2<float> uv;
		TinyGlm::vec2<float> st;
		sphere.GetSurfaceProperties(inter.coords, I, index, uv, N, st);
		return TinyGlm::vec3<float>((1.0f+N.x)*0.5f, (1.0f + N.y) * 0.5f, (1.0f + N.z) * 0.5f);
	}
	return TinyGlm::vec3<float>(0.1f, 0.1f, 0.1f);
}


void RenderFrame(std::pair<int, int> x, std::pair<int, int> y, Scene& scene, std::vector < TinyGlm::vec3 < float> >& framebuffer)
{
	
	int m = 0;

	float imageAspectRatio = scene.width / (float)scene.height;
	float scale = tan(deg2rad(scene.fov * 0.5f));
	int int_X = 0, int_Y = 0;
	for (int j = y.first; j < y.second; ++j) 
	{
		m = j * scene.width + x.first;
		for (int i = x.first; i < x.second; ++i) 
		{			
			for (int k = 0; k < MAXSPP; k++)
			{
				float r1 = Utils::get_random_float() - 0.5f,r2= Utils::get_random_float() - 0.5f;
				float dir_x = (2.f * (i + 0.5f+ r1) / (float)scene.width - 1.0f) * imageAspectRatio * scale;
				float dir_y = (1.0f - 2.f * (j + 0.5f+r2) / (float)scene.height) * scale;
			
				TinyGlm::vec3 < float> dir = TinyGlm::vec3 < float>( dir_x, dir_y, 1).normalize();
				Ray ray(scene.eye_pos, dir);
				framebuffer[m] =scene.GetColor(ray,1.0f,0,5);
			}			
			m++;
		}
	}
}


void Renderer::DrawBuffer(Scene& scene, std::vector<TinyGlm::vec3<float>>& framebuffer)
{
	
	for (size_t i = 0; i < scene_tile.size(); i++)
	{
		for (size_t j = 0; j < scene_tile.size(); j++)
		{
			PublicSingleton<ThreadPool>::get_instance().SubmitMessage(RenderFrame, scene_tile[i].first, scene_tile[j].second, std::ref(scene), std::ref(framebuffer));
			//thread_pool->SubmitMessage(RenderFrame, scene_tile[i].first, scene_tile[j].second, std::ref(scene), std::ref(framebuffer));
		}
	}

	PublicSingleton<ThreadPool>::get_instance().Join();


}

void Renderer::DrawScreenPixel(std::vector<TinyGlm::vec3<float>>& framebuffer)
{
	int m = 0;
	for (int j = 0; j < scene_height; ++j)
	{
		for (int i = 0; i < scene_width; ++i)
		{

			sdl_windows->DrawPixel(i, j, TinyGlm::vec4<float>(framebuffer[m].x, framebuffer[m].y, framebuffer[m].z));
			m++;
		}
	}
}

void Renderer::WriteToPPM(std::vector<TinyGlm::vec3<float>>& framebuffer)
{
	std::fstream fp;
	fp.open(std::string("RayTracing.ppm"), std::fstream::binary | std::fstream::out);
	if (fp.is_open())
	{
		fp << "P3\n" << scene_width << " " << scene_height << "\n255\n";
		for (auto i = 0; i < scene_height * scene_width; ++i) {
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
}

Renderer::Renderer(int _scene_width, int _scene_height):scene_width(_scene_width), scene_height(_scene_height)
{
	for (size_t i = 0; i < MAXSPP; i++)
	{
		framebuff_list.emplace_back(std::vector<TinyGlm::vec3<float>>(scene_height * scene_width, TinyGlm::vec3<float>(0.0f, 0.0f, 0.0f)));
	}

	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	cpu_core_num = sysInfo.dwNumberOfProcessors;
	bool is_init_success = true;
	sdl_windows = new SDLWindows(is_init_success, _scene_width, _scene_height);
	assert(is_init_success);
	
	//thread_pool->Init(cpu_core_num);

	int clip_num = std::sqrt(cpu_core_num*2);
	int clip_disX = std::floor(_scene_width / clip_num),clip_disY = std::floor(_scene_height / clip_num);
	int minAxisX = 0, maxAxisX = 0, minAxisY = 0, maxAxisY = 0;
	for (size_t i = 0; i < clip_num; i++)
	{
		if (i + 1 == clip_num)
		{
			maxAxisX = _scene_width;
			maxAxisY = _scene_height;
		}
		else
		{
			maxAxisX=  minAxisX + clip_disX;
			maxAxisY = maxAxisY + clip_disY;
		}

		scene_tile.push_back(std::make_pair(std::make_pair(minAxisX, maxAxisX), std::make_pair(minAxisY, maxAxisY)));
		minAxisX = maxAxisX;
		minAxisY = maxAxisY;
	}
}

Renderer::~Renderer()
{
	delete sdl_windows;
}


void Renderer::tick(Scene& scene,bool use_postprocess, std::shared_ptr<PostProcessHandle> postpocess_handle)
{
	auto start = std::chrono::system_clock::now();
	//Draw buffer in one frame 
	DrawBuffer(scene, framebuff_list[current_frame_num]);

	//Use PostProcess
	if (use_postprocess)
	{
		postpocess_handle->Execute(framebuff_list);
		DrawScreenPixel(framebuff_list[framebuff_list.size()-1]);
	}
	else
	{
		DrawScreenPixel(framebuff_list[current_frame_num]);
	}
	sdl_windows->Refresh();

	current_frame_num++;
	if (current_frame_num >= MAXSPP)
	{
		current_frame_num = 0;
	}

	auto stop = std::chrono::system_clock::now();
	std::cout << "FPS: " << int(1.0f / (float(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()) / 1000.0f)) << "\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " milliseconds\n";
}


