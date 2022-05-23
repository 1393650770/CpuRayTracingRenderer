#include "BVH.h"
#include "Intersection.h"
#include "Ray.h"
#include"Object.h"
#include"Rectangles.h"
#include<math.h>
#include <algorithm>
#include <Utils.h>
extern template class TinyGlm::vec4<float>;
extern template class TinyGlm::vec3<float>;
extern template class TinyGlm::vec2<float>;

bool sortFunctionByX(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
	return a->GetBound().centroid_point.x < b->GetBound().centroid_point.x;
}
bool sortFunctionByY(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
	return a->GetBound().centroid_point.y < b->GetBound().centroid_point.y;
}
bool sortFunctionByZ(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
	return a->GetBound().centroid_point.z < b->GetBound().centroid_point.z;
}


void BVH::FreeBVHTree(BVHNode* node)
{
	if (node == nullptr)
		return;

	BVHNode* left_node = node->left;
	BVHNode* right_node = node->right;
	delete node;
	node = nullptr;
	if (left_node)
		FreeBVHTree(left_node);
	if (right_node)
		FreeBVHTree(right_node);
}
BVHNode* BVH::recursiveBuildBVH(std::vector<std::shared_ptr<Object>> object_list)
{
	BVHNode* node = new BVHNode();

	Bound bound;
	//找出最大的包围盒
	for (size_t i = 0; i < object_list.size(); i++)
	{
		bound = Union(bound, object_list[i]->GetBound());
	}

	//如果只剩下一个物体，那么直接返回
	if (object_list.size() == 1)
	{
		node->bound = object_list[0]->GetBound();
		node->object = std::move(object_list[0].get());
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}
	//如果只剩两个物体，就直接作为两个节点
	else if (object_list.size() == 2)
	{
		node->left = recursiveBuildBVH(std::vector<std::shared_ptr<Object>>{object_list[0]});
		node->right = recursiveBuildBVH(std::vector<std::shared_ptr<Object>>{object_list[1]});
		node->bound = Union(node->left->bound, node->right->bound);
		return node;
	}

	//获取到最大的轴，根据那个轴进行排序切分
	Bound max_centroid_bound;
	for (size_t i = 0; i < object_list.size(); i++)
	{
		max_centroid_bound = Union(max_centroid_bound, object_list[i]->GetBound().centroid_point);
	}
	int max_axis= max_centroid_bound.GetMaxAxis();

	switch (max_axis)
	{
	case 0:
		std::sort(object_list.begin(),object_list.end(),sortFunctionByX);
		break;
	case 1:
		std::sort(object_list.begin(), object_list.end(), sortFunctionByY);
		break;
	case 2:
		std::sort(object_list.begin(), object_list.end(), sortFunctionByZ);
		break;
	default:
		break;
	}

	auto begin = object_list.begin();
	auto middle = object_list.begin() + (object_list.size() / 2.0f);
	auto end = object_list.end();

	node->left = recursiveBuildBVH(std::vector<std::shared_ptr<Object>>(begin, middle));
	node->right = recursiveBuildBVH(std::vector<std::shared_ptr<Object>>(middle, end));
	node->bound = Union(node->left->bound, node->right->bound);
	

	return node;
}

Intersection BVH::GetSampleInfoFromBVH(BVHNode* node, float p)
{
	Intersection result;
	if (node->left == nullptr || node->right == nullptr) 
	{
		return node->object->GetSampleInfo();
	}
	if (p < node->left->area)
		return GetSampleInfoFromBVH(node->left, p);
	else
	{
		return GetSampleInfoFromBVH(node->right, p - node->left->area);
	}
}

BVH::BVH()
{

}

BVH::BVH(std::vector<std::shared_ptr<Object>> object_list)
{
	root = recursiveBuildBVH(object_list);
}

BVH::~BVH()
{
	FreeBVHTree(root);
}

Intersection BVH::GetIntersection(Ray& ray, BVHNode* node)
{

	//如果树都没有建起来,或者是叶子节点，或者说没有交点
	if (!root)
	{
		//std::cout << "错误：树没有建起来" << std::endl;
		return Intersection();
	}
	if (!node )
	{
		//std::cout << "错误：空节点" << std::endl;
		return Intersection();
	}
	if ( !(node->bound.GetIsIntersect(ray)))
	{
		//std::cout << "错误：没有交点" << std::endl;
		return Intersection();
	}

	//叶子节点,进行对物体的求教
	if (!node->right && !node->left)
	{
		//std::cout << "叶子节点" << std::endl;
		return node->object->GetIntersection(ray);
	}

	//求出左右叶子节点的交点，取最近的那个
	Intersection inter1 = GetIntersection(ray, node->left);
	Intersection inter2 = GetIntersection(ray, node->right);

	return inter1.distance< inter2.distance ? inter1:inter2;
}

Intersection BVH::GetSampleInfo()
{
	float p = std::sqrt(Utils::get_random_float()) * root->area;
	return GetSampleInfoFromBVH(root, p);
}

