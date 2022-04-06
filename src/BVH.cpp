#include "BVH.h"
#include"Object.h"
#include<math.h>
#include <algorithm>

bool sortFunctionByX(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
	return a->getBound().centroid_point.x < b->getBound().centroid_point.x;
}
bool sortFunctionByY(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
	return a->getBound().centroid_point.y < b->getBound().centroid_point.y;
}
bool sortFunctionByZ(const std::shared_ptr<Object>& a, const std::shared_ptr<Object>& b)
{
	return a->getBound().centroid_point.z < b->getBound().centroid_point.z;
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
	//�ҳ����İ�Χ��
	for (size_t i = 0; i < object_list.size(); i++)
	{
		bound = Union(bound, object_list[i]->getBound());
	}

	//���ֻʣ��һ�����壬��ôֱ�ӷ���
	if (object_list.size() == 1)
	{
		node->bound = object_list[0]->getBound();
		node->object = std::move(object_list[0].get());
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}
	//���ֻʣ�������壬��ֱ����Ϊ�����ڵ�
	else if (object_list.size() == 2)
	{
		node->left = recursiveBuildBVH(std::vector<std::shared_ptr<Object>>{object_list[0]});
		node->right = recursiveBuildBVH(std::vector<std::shared_ptr<Object>>{object_list[1]});
		node->bound = Union(node->left->bound, node->right->bound);
		return node;
	}

	//��ȡ�������ᣬ�����Ǹ�����������з�
	Bound max_centroid_bound;
	for (size_t i = 0; i < object_list.size(); i++)
	{
		max_centroid_bound = Union(max_centroid_bound, object_list[i]->getBound().centroid_point);
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
