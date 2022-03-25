#include "TinyGlm.h"
#include<iostream>

TinyGlm::vec3::vec3()
{
	x = 0.0f; 
	y = 0.0f; 
	z = 0.0f;
}

TinyGlm::vec3::vec3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

TinyGlm::vec3::~vec3()
{
	std::cout << " vec3 Îö¹¹" << std::endl;
}




TinyGlm::vec3::vec3(const vec3& _vec3)
{
	x = _vec3.x;
	y = _vec3.y;
	z = _vec3.z;
}

TinyGlm::vec3::vec3(vec3&& _vec3) noexcept
{
	x = _vec3.x;
	y = _vec3.y;
	z = _vec3.z;
}


float TinyGlm::vec3::r() const
{
	return x;
}

float TinyGlm::vec3::g() const
{
	return y;
}

float TinyGlm::vec3::b() const
{
	return z;
}

const TinyGlm::vec3& TinyGlm::vec3::operator=(const vec3& _vec3) 
{
 	x = _vec3.x;
	y = _vec3.y;
	z = _vec3.z;
	return *this;
}

const TinyGlm::vec3& TinyGlm::vec3::operator+() const
{
	return *this;
}

TinyGlm::vec3 TinyGlm::vec3::operator-() const
{
	return vec3(-x,-y,-z);
}

float TinyGlm::vec3::operator[](int& i) const
{
	assert(i <= 2);
	return i==0? x: (i==1? y: z);
}

TinyGlm::vec3 TinyGlm::vec3::operator+(const vec3& b) const
{
	return vec3(x+b.x,y+b.y,z+ b.z);
}

TinyGlm::vec3 TinyGlm::vec3::operator-(const vec3& b) const
{
	return vec3(x- b.x, y - b.y, z- b.z);
}

TinyGlm::vec3 TinyGlm::vec3::operator/(const vec3& b) const
{
	return vec3(x / b.x, y / b.y, z / b.z);
}

TinyGlm::vec3 TinyGlm::vec3::operator*(const vec3& b) const
{
	return vec3(x * b.x, y * b.y, z * b.z);
}



TinyGlm::vec3& TinyGlm::vec3::operator+=(const vec3& _vec3)
{
	x += _vec3.x;
	y += _vec3.y;
	z += _vec3.z;
	return *this;
}

TinyGlm::vec3& TinyGlm::vec3::operator-=(const vec3& _vec3)
{
	x -= _vec3.x;
	y -= _vec3.y;
	z -= _vec3.z;
	return *this;
}

TinyGlm::vec3& TinyGlm::vec3::operator*=(const vec3& _vec3)
{
	x *= _vec3.x;
	y *= _vec3.y;
	z *= _vec3.z;
	return *this;
}

TinyGlm::vec3& TinyGlm::vec3::operator/=(const vec3& _vec3)
{
	x /= _vec3.x;
	y /= _vec3.y;
	z /= _vec3.z;
	return *this;
}

TinyGlm::vec3& TinyGlm::vec3::operator*=(const float& t)
{
	x *= t;
	y *= t;
	z *= t;
	return *this;
}

TinyGlm::vec3& TinyGlm::vec3::operator/=(const float& t)
{
	x /= t;
	y /= t;
	z /= t;
	return *this;
}

float TinyGlm::vec3::dot(const vec3& b)
{
	return x*b.x+ y * b.y+ z * b.z;
}

TinyGlm::vec3 TinyGlm::vec3::cross(const vec3& b)
{
	return vec3(
		(y*b.z-z*b.y),
		-(x*b.z-z*b.x),
		(x*b.y-y*b.x)
		);
}

TinyGlm::vec3 TinyGlm::vec3::normalize()
{
	float this_length = length();
	return vec3(x/this_length,y/this_length,z/this_length);
}

float TinyGlm::vec3::length() const
{
	return std::sqrtf(x*x+y*y+z*z);
}

float TinyGlm::vec3::squared_length() const
{
	return x * x + y * y + z * z;
}

