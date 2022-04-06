#pragma once
#ifndef _BVH_
#define _BVH_
#include<vector>
#include<memory>
#include"Bound.h"

class Object;

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
	void FreeBVHTree(BVHNode* node);

	BVHNode* recursiveBuildBVH(std::vector<std::shared_ptr<Object> > object_list);

public:
	BVHNode* root;

	BVH();
	BVH(std::vector<std::shared_ptr<Object> > object_list );
	virtual ~BVH();
};

#endif //_BVH_
