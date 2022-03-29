#include "Scene.h"
#include "Object.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;//ע��__FILE__��˫�»���
#endif 


Scene::Scene(int w , int h ):width(w),height(h)
{
}

Scene::~Scene()
{

}

void Scene::Add(std::shared_ptr<Object> object)
{
	objlist.push_back(object);
}

