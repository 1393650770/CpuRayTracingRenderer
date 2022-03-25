#pragma once
#include <assert.h>
#include <math.h>

namespace TinyGlm
{
	class vec3
	{
	public:
		virtual ~vec3();
		vec3();
		vec3(float _x,float _y ,float _z);
		vec3(const vec3& _vec3);
		vec3(vec3&& _vec3) noexcept;
		float r() const;
		float g() const;
		float b() const;
		const vec3& operator =(const vec3& _vec3);
		const vec3& operator +() const;
		vec3 operator -() const;
		float operator [](int& i) const;
		vec3 operator +(const vec3& b) const;
		vec3 operator -(const vec3& b) const;
		vec3 operator /(const vec3& b) const;
		vec3 operator *(const vec3& b) const;
		vec3& operator +=(const vec3& _vec3);
		vec3& operator -=(const vec3& _vec3);
		vec3& operator *=(const vec3& _vec3);
		vec3& operator /=(const vec3& _vec3);
		vec3& operator *=(const float& t);
		vec3& operator /=(const float& t);

		float dot(const vec3& b);
		vec3 cross(const vec3& b);
		vec3 normalize();
		float length() const;
		float squared_length()const;


		float x, y, z;
	};
}
