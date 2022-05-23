#pragma once
#ifndef _BVH_
#define _BVH_
#include<vector>
#include<memory>
#include"Bound.h"

class Object;
class Ray;
class Intersection;


struct BVHNode
{
	Bound bound;
	BVHNode* left;
	BVHNode* right;
	Object* object;
	float area;
public:
	BVHNode()
	{
		bound = Bound();
		left = nullptr;
		right = nullptr;
		object = nullptr;
	}
};

class BVH
{
private:
	//构建BVH资源
	void FreeBVHTree(BVHNode* node);

	//构建BVH
	BVHNode* recursiveBuildBVH(std::vector<std::shared_ptr<Object> > object_list);

	Intersection GetSampleInfoFromBVH(BVHNode* node,float p);

public:
	BVHNode* root;

	BVH();
	BVH(std::vector<std::shared_ptr<Object> > object_list );
	virtual ~BVH();

	//获取到碰撞节点
	Intersection GetIntersection(Ray& ray, BVHNode* node);

	Intersection GetSampleInfo();
};

#endif //_BVH_
