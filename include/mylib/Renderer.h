#pragma once
#ifndef _RENDER_
#define _RENDER_
#include <vector>
#include <array>

namespace TinyGlm
{
	template<typename T>
	class vec3;
};

class SDLWindows;
class Scene;
class PostProcessHandle;

class ThreadPool;

class Renderer
{
private:
	int scene_width = 0;
	int scene_height = 0;
	int cpu_core_num;
	std::vector<std::pair<std::pair<int ,int >, std::pair<int,int>> > scene_tile;

	SDLWindows* sdl_windows;
	std::array<std::vector<TinyGlm::vec3<float>>, 3> framebuff_list;

	//Draw buffer in one frame 
	void DrawBuffer(Scene& scene, std::vector<TinyGlm::vec3<float>>& framebuffer);

	//Output framebuff to Screen 
	void DrawScreenPixel(std::vector<TinyGlm::vec3<float>>& framebuffer);

	void WriteToPPM(std::vector<TinyGlm::vec3<float>>& framebuffer);

public:
	bool is_use_postprocess = false;

	Renderer(int scene_width,int scene_height);
	virtual ~Renderer();
	void tick( Scene& scene,bool use_postprocess=false, PostProcessHandle* postpocess_handle=nullptr);


};
#endif
