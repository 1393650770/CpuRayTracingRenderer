#pragma once
#ifndef _RENDER_
#define _RENDER_
#include <vector>

class Scene;

class Renderer
{
private:
	int cpu_core_num;
	std::vector<std::pair<std::pair<int ,int >, std::pair<int,int>> > scene_tile;
public:
	Renderer(int scene_width,int scene_height);
	virtual ~Renderer();
	void Render( Scene& scene);

};
#endif
