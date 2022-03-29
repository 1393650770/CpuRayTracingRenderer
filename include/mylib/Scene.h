#pragma once
#ifndef _SCENE_
#define _SCENE_
#include <vector>
#include <memory>

class Object;
class Scene
{
private:
	//std::vector<std::shared_ptr<Object *> > objlist;
public:
	int width=1920;
	int height=1080;
	float fov = 60;
	std::vector<std::shared_ptr<Object> > objlist;
	Scene(int w=1920, int h=1080);
	virtual ~Scene();

	void Add(std::shared_ptr<Object> object);
};
#endif //_SCENE_