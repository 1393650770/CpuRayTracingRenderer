#include "Scene.h"
#include "Object.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;//注意__FILE__是双下划线
#endif 


Scene::Scene(int w , int h ):width(w),height(h),eye_pos(TinyGlm::vec3<float>(0.0f,0.0f,0.0f))
{
}

Scene::~Scene()
{

}

void Scene::Add(std::shared_ptr<Object> object)
{
	objlist.push_back(object);
}

