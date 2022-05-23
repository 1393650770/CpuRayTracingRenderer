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
	//�ҳ����İ�Χ��
	for (size_t i = 0; i < object_list.size(); i++)
	{
		bound = Union(bound, object_list[i]->GetBound());
	}

	//���ֻʣ��һ�����壬��ôֱ�ӷ���
	if (object_list.size() == 1)
	{
		node->bound = object_list[0]->GetBound();
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

	//�������û�н�����,������Ҷ�ӽڵ㣬����˵û�н���
	if (!root)
	{
		//std::cout << "������û�н�����" << std::endl;
		return Intersection();
	}
	if (!node )
	{
		//std::cout << "���󣺿սڵ�" << std::endl;
		return Intersection();
	}
	if ( !(node->bound.GetIsIntersect(ray)))
	{
		//std::cout << "����û�н���" << std::endl;
		return Intersection();
	}

	//Ҷ�ӽڵ�,���ж���������
	if (!node->right && !node->left)
	{
		//std::cout << "Ҷ�ӽڵ�" << std::endl;
		return node->object->GetIntersection(ray);
	}

	//�������Ҷ�ӽڵ�Ľ��㣬ȡ������Ǹ�
	Intersection inter1 = GetIntersection(ray, node->left);
	Intersection inter2 = GetIntersection(ray, node->right);

	return inter1.distance< inter2.distance ? inter1:inter2;
}

Intersection BVH::GetSampleInfo()
{
	float p = std::sqrt(Utils::get_random_float()) * root->area;
	return GetSampleInfoFromBVH(root, p);
}

