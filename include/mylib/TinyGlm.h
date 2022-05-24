#pragma once
#ifndef _TINYGlM_
#define _TINYGlM_
#include <assert.h>
#include <math.h>
#include<iostream>

namespace TinyGlm
{
	template<typename T>
	class vec3;
	template<typename T>
	class vec4;
	template<typename T>
	class vec2;


	template<typename T>
	class vec4
	{
	public:
		virtual ~vec4();
		vec4();
		vec4(T _x);
		vec4(T _x, T _y, T _z, T _w);
		vec4(T _x, T _y, T _z);
		vec4(const vec4<T>& _vec4);

		vec4(vec4<T>&& _vec4) noexcept;

		template<typename U>
		vec4(vec4<U>&& _vec4) noexcept;

		friend vec4<T> operator+ (const vec4<T>& a, const vec4<T>& b)
		{
			return vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w+b.w);
		};
		friend vec4<T> operator+ (const vec3<T>& a , const vec4<T>& b)
		{
			return vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, b.w);
		};
		friend vec4<T> operator+ (const vec4<T>& a, const vec3<T>& b)
		{
			return vec4<T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w );
		};
		friend vec4<T> operator- (const vec4<T>& a, const vec4<T>& b)
		{
			return vec4<T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
		};
		friend vec4<T> operator* (const vec4<T>& a, const vec4<T>& b)
		{
			return vec4<T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
		};

		friend vec4<T> operator* (const vec3<T>& a, const vec4<T>& b)
		{
			return vec4<T>(a.x * b.x, a.y * b.y, a.z * b.z, b.w);
		};

		friend vec4<T> operator* (const vec4<T>& a , const T& b)
		{
			return vec4<T>(a.x * b, a.y * b, a.z * b);
		};
		friend vec4<T> operator/ (const vec4<T>& a, const vec4<T>& b)
		{
			return vec4<T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
		};
		friend vec4<T> operator/ (const vec4<T>& a, const T& b)
		{
			return vec4<T>(a.x / b, a.y / b, a.z / b, a.w );
		};

		vec4<T>& operator=(const vec4<T>& _vec4);
		vec4<T>& operator=(vec4<T>&& _vec4) noexcept;
		vec4<T>& operator +() const;
		vec4<T> operator -() const;
		T& operator [](int i);
		T& operator [](short i);
		const T& operator [](int i) const;
		const T& operator [](short i) const;
		vec4<T>& operator +=(const vec4<T>& _vec4);
		vec4<T>& operator -=(const vec4<T>& _vec4);
		vec4<T>& operator *=(const vec4<T>& _vec4);
		vec4<T>& operator /=(const vec4<T>& _vec4);

		template<typename U>
		vec4<T>& operator *=(const U& t);

		template<typename U>
		vec4<T>& operator /=(const U& t);

		//return dot as vec3
		float dot(const vec4<T>& b);
		//return cross result as vec3
		vec4<T> cross(const vec4<T>& b);
		vec4<T> normalize();
		vec4<T> normalize() const;
		//return length as vec3
		float length() const;
		//return squared_length as vec3
		float squared_length()const;

		T r() const;
		T g() const;
		T b() const;
		T a() const;

		T x, y, z, w;
	};


	template<typename T>
	class vec3
	{
	public:
		virtual ~vec3();
		vec3();
		vec3(T _x,T _y ,T _z);
		vec3(T _x);
		vec3(const vec3<T>& _vec3);

		vec3(vec3<T>&& _vec3) noexcept;

		template<typename U>
		vec3(const vec3<U>& _vec3);

		template<typename U>
		vec3(vec3<U>&& _vec3) noexcept;

		T r() const;
		T g() const;
		T b() const;
		vec3<T>& operator=(const vec3<T>& _vec3);
		vec3<T>& operator=(vec3<T>&& _vec3) noexcept;
		vec3<T>& operator+() const;
		vec3<T> operator -() const;
		T& operator [](int i);
		T& operator [](short i);
		const T& operator [](int i) const;
		const T& operator [](short i) const;

		friend vec3<T> operator+ (const vec3<T>& a, const vec3<T>& b)
		{
			return vec3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
		};

		friend vec3<T> operator- (const vec3<T>& a, const vec3<T>& b)
		{
			return vec3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
		};
		vec3<T> operator /(const vec3<T>& b) const;
		vec3<T> operator /(T& b) const;
		vec3<T> operator /(const T& b) const;
		vec3<T> operator /(const T& b);
		vec3<T> operator /(T& b);
		friend vec3<T> operator* (const vec3<T>& a, const vec3<T>& b)
		{
			return vec3<T>(a.x * b.x, a.y * b.y, a.z * b.z);
		};
		vec3<T> operator *(T& b) const;
		vec3<T> operator *(T& b) ;
		vec3<T> operator *(const T& b) const;
		vec3<T>& operator +=(const vec3<T>& _vec3);
		vec3<T>& operator -=(const vec3<T>& _vec3);
		vec3<T>& operator *=(const vec3<T>& _vec3);
		vec3<T>& operator /=(const vec3<T>& _vec3);

		static vec3<T> min(const vec3<T>& a, const vec3<T>& b)
		{
			return vec3<T>(std::min(a.x, b.x), std::min(a.y, b.y),
				std::min(a.z, b.z));
		};

		static vec3<T> max(const vec3<T>& a, const vec3<T>& b)
		{
			return vec3<T>(std::max(a.x, b.x), std::max(a.y, b.y),
				std::max(a.z, b.z));
		};

		template<typename U>
		vec3<T>& operator *=(const U& t);

		template<typename U>
		vec3<T>& operator /=(const U& t);

		float dot(const vec3<T>& b) const;
		vec3<T> cross(const vec3<T>& b) const;
		vec3<T> normalize();
		vec3<T> normalize()const;
		float length() const;
		float squared_length()const;


		T x, y, z;
	};

	template<typename T>
	class vec2
	{
	public:
		virtual ~vec2();
		vec2();
		vec2(T _x, T _y);
		vec2(const vec2<T>& _vec2) = default;
		vec2(vec2<T>&& _vec2) = default;

		template<typename U>
		vec2(const vec2<U>& _vec2);

		template<typename U>
		vec2(vec2<U>&& _vec2) noexcept;

		friend vec2<T> operator+ (const vec2<T>& a, const vec2<T>& b)
		{
			return vec2<T>(a.x + b.x, a.y + b.y);
		};
		friend vec2<T> operator- (const vec2<T>& a, const vec2<T>& b)
		{
			return vec2<T>(a.x - b.x, a.y - b.y);
		};
		friend vec2<T> operator* (const vec2<T>& a, const vec2<T>& b)
		{
			return vec2<T>(a.x * b.x, a.y * b.y);
		};
		friend vec2<T> operator* (const vec2<T>& a, const T& b)
		{
			return vec2<T>(a.x * b, a.y * b);
		};
		friend vec2<T> operator/ (const vec2<T>& a, const vec2<T>& b)
		{
			return vec2<T>(a.x / b.x, a.y / b.y);
		};

		vec2<T>& operator=(const vec2<T>& _vec2);
		vec2<T>& operator=(vec2<T>&& _vec2) noexcept;
		vec2<T>& operator+() const;
		vec2<T> operator -() const;
		T& operator[](int i);
		T& operator[](short i);
		const T& operator [](int i) const;
		const T& operator [](short i) const;
		vec2<T>& operator +=(const vec2<T>& _vec2);
		vec2<T>& operator -=(const vec2<T>& _vec2);
		vec2<T>& operator *=(const vec2<T>& _vec2);
		vec2<T>& operator /=(const vec2<T>& _vec2);

		template<typename U>
		vec2<T>& operator *=(const U& t);

		template<typename U>
		vec2<T>& operator /=(const U& t);

		//return dot as vec3
		float dot(const vec2<T>& b);
		vec3<T> cross(const vec2<T>& b);
		vec2<T> normalize();
		vec2<T> normalize()const;
		float length() const;
		float squared_length()const;

		T r() const;
		T g() const;


		T x, y;
	};



	template<typename T>
	class mat4
	{
	private:
		T cofactor(int i, int j);
	public:
		virtual ~mat4();
		//return identity matrix
		mat4();
		mat4(const mat4<T>& _mat4) = default;
		mat4(mat4<T>&& _mat4) = default;

		template<typename U>
		mat4(const mat4<U>& _mat4);

		template<typename U>
		mat4(mat4<U>&& _mat4) noexcept;

		friend mat4<T> operator+ (const mat4<T>& a, const mat4<T>& b)
		{
			mat4<T> result;
			for (size_t i = 0; i < 16; i++)
			{
				result.val[i] = a[i] + b[i];
			}
			return result;
		};
		friend mat4<T> operator+ (const mat4<T>& a, const T& b)
		{
			mat4<T> result;
			for (short k = 0; k < 16; k++)
			{
				result.val[k] += b;
			}
			return result;
		};
		friend mat4<T> operator- (const mat4<T>& a, const mat4<T>& b)
		{
			mat4<T> result;
			for (size_t i = 0; i < 16; i++)
			{
				result.val[i] = a[i] - b[i];
			}
			return result;
		};
		friend mat4<T> operator- (const mat4<T>& a, const T& b)
		{
			mat4<T> result;
			for (short k = 0; k < 16; k++)
			{
				result.val[k] -= b;
			}
			return result;
		};
		friend mat4<T> operator* (const mat4<T>& a, const mat4<T>& b)
		{
			mat4<T> result;
			for (short k = 0; k < 4; k++)
			{
				for (short i = 0; i < 4; i++)
				{
					result.val[k * 4 + i] = static_cast<T>(0.0f);
					for (short j = 0; j < 4; j++)
					{
						result.val[k*4+i] += a.val[k * 4 + j] * b.val[i + j * 4];
					}
				}
			}
			return result;
			
		};
		friend vec4<T> operator* (const mat4<T>& a, const vec4<T>& b)
		{
			vec4<T> result;
			for (int k = 0; k < 4; k++)
			{
				for (int i = 0; i < 4; i++)
				{
					result[k] += a.val[k*4+i]*b[i];
				}
			}
			return result;

		};
		friend mat4<T> operator* (const mat4<T>& a, const T& b)
		{
			mat4<T> result;
			for (short k = 0; k < 16; k++)
			{
				result.val[k] = a.val[k]*b;
			}
			return result;
		};
		friend mat4<T> operator/ (const mat4<T>& a, const T& b)
		{
			mat4<T> result;
			for (short k = 0; k < 16; k++)
			{
				result.val[k] =a.val[k] / b;
			}
			return result;
		};

		mat4<T>& operator=(const mat4<T>& _mat4);
		mat4<T>& operator=(mat4<T>&& _mat4) noexcept;
		mat4<T>& operator+() const;
		mat4<T> operator-() const;
		mat4<T>& operator +=(const mat4<T>& _mat4);
		mat4<T>& operator -=(const mat4<T>& _mat4);
		mat4<T>& operator /=(const mat4<T>& _mat4);

		template<typename U>
		mat4<T>& operator *=(const U& t);

		template<typename U>
		mat4<T>& operator /=(const U& t);

		template<typename U>
		mat4<T>& operator +=(const U& t);

		template<typename U>
		mat4<T>& operator -=(const U& t);

		mat4<T>& operator *=(const T& t);
		mat4<T>& operator /=(const T& t);
		mat4<T>& operator +=(const T& t);
		mat4<T>& operator -=(const T& t);

		mat4<T>  cofactor_mat();
		float determinant();
		mat4<T> adjoint();
		//return the matrix transpose
		mat4<T> transpose();

		//return the matrix inverse
		mat4<T> inverse();

		T val[16];
	};




	template<typename T>
	TinyGlm::vec3<T>::vec3()
	{
		x = static_cast<T>(0.0f);
		y = static_cast<T>(0.0f);
		z = static_cast<T>(0.0f);
	}


	template<typename T>
	TinyGlm::vec3<T>::vec3(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	template<typename T>
	TinyGlm::vec3<T>::vec3(T _x)
	{
		x = _x;
		y = _x;
		z = _x;
	}

	template<typename T>
	TinyGlm::vec3<T>::~vec3()
	{
	}

	template<typename T>
	template<typename U>
	TinyGlm::vec3<T>::vec3(const vec3<U>& _vec3)
	{
		x = static_cast<T>(_vec3.x);
		y = static_cast<T>(_vec3.y);
		z = static_cast<T>(_vec3.z);
	}

	template<typename T>
	TinyGlm::vec3<T>::vec3(const vec3<T>& _vec3)
	{
		x = _vec3.x;
		y = _vec3.y;
		z = _vec3.z;
	}



	template<typename T>
	TinyGlm::vec3<T>::vec3(vec3<T>&& _vec3) noexcept
	{
		x = _vec3.x;
		y = _vec3.y;
		z = _vec3.z;
	}


	template<typename T>
	template<typename U>
	TinyGlm::vec3<T>::vec3(vec3<U>&& _vec3) noexcept
	{
		x = static_cast<T>(_vec3.x);
		y = static_cast<T>(_vec3.y);
		z = static_cast<T>(_vec3.z);
	}



	template<typename T>
	T TinyGlm::vec3<T>::r() const
	{
		return x;
	}

	template<typename T>
	T TinyGlm::vec3<T>::g() const
	{
		return y;
	}

	template<typename T>
	T TinyGlm::vec3<T>::b() const
	{
		return z;
	}

	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator=(const vec3<T>& _vec3)
	{
		x = _vec3.x;
		y = _vec3.y;
		z = _vec3.z;
		return *this;
	}

	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator=(vec3<T>&& _vec3) noexcept
	{
		x = _vec3.x;
		y = _vec3.y;
		z = _vec3.z;
		return *this;
	}

	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator +() const
	{
		return *this;
	}

	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::operator-() const
	{
		return vec3<T>(-x, -y, -z);
	}

	template<typename T>
	T& TinyGlm::vec3<T>::operator[](int i)
	{
		assert(i <= 2);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		return z;

	}

	template<typename T>
	T& TinyGlm::vec3<T>::operator[](short i)
	{
		assert(i <= 2);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		return z;
	}

	template<typename T>
	const T& TinyGlm::vec3<T>::operator[](int i) const
	{
		assert(i <= 2);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		return z;

	}

	template<typename T>
	const T& TinyGlm::vec3<T>::operator[](short i) const
	{
		assert(i <= 2);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		return z;

	}






	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::operator/(const vec3<T>& b) const
	{
		return vec3<T>(x / b.x, y / b.y, z / b.z);
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator/(const T& b) const
	{
		return vec3<T>(x / b, y / b, z / b);
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator/(T& b) const
	{
		return vec3<T>(x / b, y / b, z / b);
	}

	template<typename T>
	inline vec3<T> vec3<T>::operator/(const T& b)
	{
		return vec3<T>(x / b, y / b, z / b);
	}


	template<typename T>
	inline vec3<T> vec3<T>::operator/(T& b)
	{
		return vec3<T>(x / b, y / b, z / b);
	}



	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::operator*(T& b) const
	{
		return vec3<T>(x * b, y * b, z * b);
	}

	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::operator*(const T& b) const
	{
		return vec3<T>(x * b, y * b, z * b);
	}

	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::operator*(T& b)
	{
		return vec3<T>(x * b, y * b, z * b);
	}




	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator+=(const vec3<T>& _vec3)
	{
		x += _vec3.x;
		y += _vec3.y;
		z += _vec3.z;
		return *this;
	}

	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator-=(const vec3<T>& _vec3)
	{
		x -= _vec3.x;
		y -= _vec3.y;
		z -= _vec3.z;
		return *this;
	}

	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator*=(const vec3<T>& _vec3)
	{
		x *= _vec3.x;
		y *= _vec3.y;
		z *= _vec3.z;
		return *this;
	}

	template<typename T>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator/=(const vec3<T>& _vec3)
	{
		x /= _vec3.x;
		y /= _vec3.y;
		z /= _vec3.z;
		return *this;
	}

	template<typename T>
	template<typename U>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator*=(const U& t)
	{
		x *= static_cast<T>(t);
		y *= static_cast<T>(t);
		z *= static_cast<T>(t);
		return *this;
	}


	template<typename T>
	template<typename U>
	TinyGlm::vec3<T>& TinyGlm::vec3<T>::operator/=(const U& t)
	{
		x /= static_cast<U>(t);
		y /= static_cast<T>(t);
		z /= static_cast<T>(t);
		return *this;
	}

	template<typename T>
	float TinyGlm::vec3<T>::dot(const vec3<T>& b) const
	{
		return x * b.x + y * b.y + z * b.z;
	}

	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::cross(const vec3<T>& b) const
	{
		return TinyGlm::vec3<T>(
			(y * b.z - z * b.y),
			-(x * b.z - z * b.x),
			(x * b.y - y * b.x)
			);
	}

	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::normalize()
	{
		float inv_length =1.0f/ length();
		return vec3<T>( x * inv_length, y* inv_length, z * inv_length);
	}
	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec3<T>::normalize() const
	{
		float inv_length =1.0f/ length();
		return vec3<T>(x * inv_length, y * inv_length, z * inv_length);
	}

	template<typename T>
	float TinyGlm::vec3<T>::length() const
	{
		return std::sqrtf(x * x + y * y + z * z);
	}

	template<typename T>
	float TinyGlm::vec3<T>::squared_length() const
	{
		return x * x + y * y + z * z;
	}



	template<typename T>
	TinyGlm::vec4<T>::vec4()
	{
		x = static_cast<T>(0.0f);
		y = static_cast<T>(0.0f);
		z = static_cast<T>(0.0f);
		w = static_cast<T>(0.0f);
	}


	template<typename T>
	TinyGlm::vec4<T>::vec4(T _x, T _y, T _z, T _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}


	template<typename T>
	TinyGlm::vec4<T>::vec4(T _x, T _y, T _z)
	{
		x = _x;
		y = _y;
		z = _z;
		w = static_cast<T>(1.0f);
	}

	template<typename T>
	TinyGlm::vec4<T>::vec4(T _x)
	{
		x = _x;
		y = _x;
		z = _x;
		w = static_cast<T>(1.0f);
	}





	template<typename T>
	TinyGlm::vec4<T>::~vec4()
	{
	}

	template<typename T>
	TinyGlm::vec4<T>::vec4(const vec4<T>& _vec4)
	{
		x = _vec4.x;
		y = _vec4.y;
		z = _vec4.z;
		w = _vec4.w;
	}



	template<typename T>
	TinyGlm::vec4<T>::vec4(vec4<T>&& _vec4) noexcept
	{
		x = _vec4.x;
		y = _vec4.y;
		z = _vec4.z;
		w = _vec4.w;
	}





	template<typename T>
	template<typename U>
	TinyGlm::vec4<T>::vec4(vec4<U>&& _vec4) noexcept
	{
		x = static_cast<T>(_vec4.x);
		y = static_cast<T>(_vec4.y);
		z = static_cast<T>(_vec4.z);
		w = static_cast<T>(_vec4.w);
	}



	template<typename T>
	T TinyGlm::vec4<T>::r() const
	{
		return x;
	}

	template<typename T>
	T TinyGlm::vec4<T>::g() const
	{
		return y;
	}

	template<typename T>
	T TinyGlm::vec4<T>::b() const
	{
		return z;
	}

	template<typename T>
	T TinyGlm::vec4<T>::a() const
	{
		return w;
	}

	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator=(const vec4<T>& _vec4)
	{
		x = _vec4.x;
		y = _vec4.y;
		z = _vec4.z;
		w = _vec4.w;
		return *this;
	}

	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator=(vec4<T>&& _vec4) noexcept
	{
		x = _vec4.x;
		y = _vec4.y;
		z = _vec4.z;
		w = _vec4.w;
		return *this;
	}

	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator +() const
	{
		return *this;
	}

	template<typename T>
	TinyGlm::vec4<T> TinyGlm::vec4<T>::operator-() const
	{
		return vec4<T>(-x, -y, -z,-w);
	}

	template<typename T>
	T& TinyGlm::vec4<T>::operator[](int i)
	{
		assert(i <= 3);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		else if (i == 2)
		{
			return z;
		}
		return w;
	}

	template<typename T>
	T& TinyGlm::vec4<T>::operator[](short i)
	{
		assert(i <= 3);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		else if (i == 2)
		{
			return z;
		}
		return w;
	}

	template<typename T>
	const T& TinyGlm::vec4<T>::operator[](int i) const
	{
		assert(i <= 3);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		else if (i == 2)
		{
			return z;
		}
		return w;
	}

	template<typename T>
	const T& TinyGlm::vec4<T>::operator[](short i) const
	{
		assert(i <= 3);
		if (i == 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		else if (i == 2)
		{
			return z;
		}
		return w;
	}


	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator+=(const vec4<T>& _vec4)
	{
		x += _vec4.x;
		y += _vec4.y;
		z += _vec4.z;
		w += _vec4.w;
		return *this;
	}

	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator-=(const vec4<T>& _vec4)
	{
		x -= _vec4.x;
		y -= _vec4.y;
		z -= _vec4.z;
		w -= _vec4.w;
		return *this;
	}

	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator*=(const vec4<T>& _vec4)
	{
		x *= _vec4.x;
		y *= _vec4.y;
		z *= _vec4.z;
		w *= _vec4.w;
		return *this;
	}

	template<typename T>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator/=(const vec4<T>& _vec4)
	{
		x /= _vec4.x;
		y /= _vec4.y;
		z /= _vec4.z;
		w /= _vec4.w;
		return *this;
	}

	template<typename T>
	template<typename U>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator*=(const U& t)
	{
		x *= static_cast<T>(t);
		y *= static_cast<T>(t);
		z *= static_cast<T>(t);
		w *= static_cast<T>(t);
		return *this;
	}


	template<typename T>
	template<typename U>
	TinyGlm::vec4<T>& TinyGlm::vec4<T>::operator/=(const U& t)
	{
		x /= static_cast<U>(t);
		y /= static_cast<T>(t);
		z /= static_cast<T>(t);
		w /= static_cast<T>(t);
		return *this;
	}

	template<typename T>
	float TinyGlm::vec4<T>::dot(const vec4<T>& b)
	{
		return x * b.x + y * b.y + z * b.z;
	}

	template<typename T>
	TinyGlm::vec4<T> TinyGlm::vec4<T>::cross(const vec4<T>& b)
	{
		return vec4<T>(
			(y * b.z - z * b.y),
			-(x * b.z - z * b.x),
			(x * b.y - y * b.x)
			);
	}

	template<typename T>
	TinyGlm::vec4<T> TinyGlm::vec4<T>::normalize()
	{
		float this_length_Div = 1.0f/length();
		return this* this_length_Div;
	}

	template<typename T>
	TinyGlm::vec4<T> TinyGlm::vec4<T>::normalize() const
	{
		float this_length_Div = 1.0f / length();
		return this * this_length_Div;
	}

	template<typename T>
	float TinyGlm::vec4<T>::length() const
	{
		return std::sqrtf(x * x + y * y + z * z);
	}

	template<typename T>
	float TinyGlm::vec4<T>::squared_length() const
	{
		return x * x + y * y + z * z ;
	}

	template<typename T>
	TinyGlm::vec2<T>::vec2()
	{
		x = static_cast<T>(0.0f);
		y = static_cast<T>(0.0f);

	}


	template<typename T>
	TinyGlm::vec2<T>::vec2(T _x, T _y)
	{
		x = _x;
		y = _y;

	}

	template<typename T>
	TinyGlm::vec2<T>::~vec2()
	{
	}

	template<typename T>
	template<typename U>
	TinyGlm::vec2<T>::vec2(const vec2<U>& _vec2)
	{
		x = static_cast<T>(_vec2.x);
		y = static_cast<T>(_vec2.y);
	}




	template<typename T>
	template<typename U>
	TinyGlm::vec2<T>::vec2(vec2<U>&& _vec2) noexcept
	{
		x = static_cast<T>(_vec2.x);
		y = static_cast<T>(_vec2.y);
	}



	template<typename T>
	T TinyGlm::vec2<T>::r() const
	{
		return x;
	}

	template<typename T>
	T TinyGlm::vec2<T>::g() const
	{
		return y;
	}



	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator=(const vec2<T>& _vec2)
	{
		x = _vec2.x;
		y = _vec2.y;
		return *this;
	}

	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator=(vec2<T>&& _vec2) noexcept
	{
		x = _vec2.x;
		y = _vec2.y;
		return *this;
	}

	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator +() const
	{
		return *this;
	}

	template<typename T>
	TinyGlm::vec2<T> TinyGlm::vec2<T>::operator-() const
	{
		return vec2<T>(-x, -y);
	}

	template<typename T>
	T& TinyGlm::vec2<T>::operator[](int i)
	{
		assert(i <= 1);
		if (i == 0)
		{
			return x;
		}
		return y;

	}

	template<typename T>
	 T& TinyGlm::vec2<T>::operator[](short i) 
	{
		assert(i <= 1);
		if (i == 0)
		{
			return x;
		}
		return y;

	}

	template<typename T>
	const T& TinyGlm::vec2<T>::operator[](int i) const
	{
		assert(i <= 1);
		if (i == 0)
		{
			return x;
		}
		return y;

	}

	template<typename T>
	const T& TinyGlm::vec2<T>::operator[](short i) const
	{
		assert(i <= 1);
		if (i == 0)
		{
			return x;
		}
		return y;

	}


	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator+=(const vec2<T>& _vec2)
	{
		x += _vec2.x;
		y += _vec2.y;
		return *this;
	}

	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator-=(const vec2<T>& _vec2)
	{
		x -= _vec2.x;
		y -= _vec2.y;
		return *this;
	}

	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator*=(const vec2<T>& _vec2)
	{
		x *= _vec2.x;
		y *= _vec2.y;
		return *this;
	}

	template<typename T>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator/=(const vec2<T>& _vec2)
	{
		x /= _vec2.x;
		y /= _vec2.y;
		return *this;
	}

	template<typename T>
	template<typename U>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator*=(const U& t)
	{
		x *= static_cast<T>(t);
		y *= static_cast<T>(t);
		return *this;
	}


	template<typename T>
	template<typename U>
	TinyGlm::vec2<T>& TinyGlm::vec2<T>::operator/=(const U& t)
	{
		x /= static_cast<U>(t);
		y /= static_cast<T>(t);
		return *this;
	}

	template<typename T>
	float TinyGlm::vec2<T>::dot(const vec2<T>& b)
	{
		return x * b.x + y * b.y;
	}

	template<typename T>
	TinyGlm::vec3<T> TinyGlm::vec2<T>::cross(const vec2<T>& b)
	{
		return vec3<T>(
			static_cast<T>(0.0f),
			static_cast<T>(0.0f),
			(x * b.y - y * b.x)
			);
	}

	template<typename T>
	TinyGlm::vec2<T> TinyGlm::vec2<T>::normalize()
	{
		float this_length_Div = 1.0f/length();
		return this/ this_length_Div;
	}

	template<typename T>
	TinyGlm::vec2<T> TinyGlm::vec2<T>::normalize() const
	{
		float this_length_Div = 1.0f / length();
		return this / this_length_Div;
	}

	template<typename T>
	float TinyGlm::vec2<T>::length() const
	{
		return std::sqrtf(x * x + y * y);
	}

	template<typename T>
	float TinyGlm::vec2<T>::squared_length() const
	{
		return x * x + y * y ;
	}

	template<typename T>
	TinyGlm::mat4<T>::mat4()
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] = static_cast<T>(0.0f);
		}
		val[0] = static_cast<T>(1.0f);
		val[5] = static_cast<T>(1.0f);
		val[10] = static_cast<T>(1.0f);
		val[15] = static_cast<T>(1.0f);
	}



	template<typename T>
	TinyGlm::mat4<T>::~mat4()
	{
	}

	template<typename T>
	template<typename U>
	TinyGlm::mat4<T>::mat4(const mat4<U>& _mat4)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] = static_cast<T>(_mat4.val[i]);
		}
	}




	template<typename T>
	template<typename U>
	TinyGlm::mat4<T>::mat4(mat4<U>&& _mat4) noexcept
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] = static_cast<T>(_mat4.val[i]);
		}
	}



	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator=(const mat4<T>& _mat4)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] = _mat4.val[i];
		}
		return *this;
	}

	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator=(mat4<T>&& _mat4) noexcept
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] =_mat4.val[i];
		}
		return *this;
	}

	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator +() const
	{
		return *this;
	}

	template<typename T>
	TinyGlm::mat4<T> TinyGlm::mat4<T>::operator-() const
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] = -val[i];
		}
		return mat4<T>(this);
	}


	

	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator+=(const mat4<T>& _mat4)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] += val[i];
		}
		return *this;
	}

	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator-=(const mat4<T>& _mat4)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] -= val[i];
		}
		return *this;
	}


	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator/=(const mat4<T>& _mat4)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] /= val[i];
		}
		return *this;
	}

	template<typename T>
	template<typename U>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator*=(const U& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] *= static_cast<T>(t);
		}
		return *this;
	}


	template<typename T>
	template<typename U>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator/=(const U& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] /= static_cast<T>(t);
		}
		return *this;
	}

	template<typename T>
	template<typename U>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator+=(const U& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] += static_cast<T>(t);
		}
		return *this;
	}


	template<typename T>
	template<typename U>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator-=(const U& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] -= static_cast<T>(t);
		}
		return *this;
	}

	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator*=(const T& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] *= t;
		}
		return *this;
	}


	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator/=(const T& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] /= t;
		}
		return *this;
	}

	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator+=(const T& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] += t;
		}
		return *this;
	}


	template<typename T>
	TinyGlm::mat4<T>& TinyGlm::mat4<T>::operator-=(const T& t)
	{
		for (size_t i = 0; i < 16; i++)
		{
			val[i] -= t;
		}
		return *this;
	}

	template<typename T>
	T TinyGlm::mat4<T>::cofactor(int i, int j)
	{
		T mat3x3[9];
		for (short k = 0; k < 9; k++)
		{
			mat3x3[k] = static_cast<T>(0.0f);
		}
		T result;
		bool Is_Should_BeDelete = false;
		int mat3x3_index = 0;
		for (short k = 0; k < 16; k++)
		{
			Is_Should_BeDelete = false;

			//Check This Val Is should Be Delete;
			for (short m = 0; m < 4; m++)
			{
				if (k == i * 4 + m || k == m * 4 + j)
				{
					Is_Should_BeDelete = true;
					break;
				}
			}
			if (Is_Should_BeDelete == false)
			{
				mat3x3[mat3x3_index] = this->val[k];
				mat3x3_index++;
			}
		}
		result = mat3x3[0] * mat3x3[4] * mat3x3[8] +
			mat3x3[1] * mat3x3[5] * mat3x3[6] +
			mat3x3[2] * mat3x3[3] * mat3x3[7] -
			mat3x3[2] * mat3x3[4] * mat3x3[6] -
			mat3x3[1] * mat3x3[3] * mat3x3[8]-
			mat3x3[0] * mat3x3[5] * mat3x3[7];
		return result;
	}


	template<typename T>
	TinyGlm::mat4<T> TinyGlm::mat4<T>::cofactor_mat()
	{
		mat4<T> result;
		for (short i = 0; i < 4; i++)
		{
			for (short j = 0; j < 4; j++)
			{
				result.val[i * 4 + j] = cofactor(i, j);
			}
		}
		return result;
	}

	template<typename T>
	TinyGlm::mat4<T> TinyGlm::mat4<T>::adjoint()
	{
		mat4<T> result = cofactor_mat();
		result = result.transpose();
		return result;
	}

	template<typename T>
	TinyGlm::mat4<T> TinyGlm::mat4<T>::transpose()
	{
		mat4<T> result;
		for (short k = 0; k < 4; k++)
		{
			for (short i = 0; i < 4; i++)
			{
				result.val[k * 4 + i] = this->val[k + i * 4];
			}
		}

		return result;
	}

	template<typename T>
	float TinyGlm::mat4<T>::determinant()
	{
		mat4<T> cof_mat = cofactor_mat();
		float result = 0.0f;
		for (short i = 0; i < 4; i++)
		{
			result += static_cast<float>( this->val[i*4] ) * std::pow(-1.0f, float(i )) * cof_mat.val[i * 4 ];
		}
		return result;
	}

	template<typename T>
	TinyGlm::mat4<T> TinyGlm::mat4<T>::inverse()
	{
		mat4<T> result = adjoint();
		mat4<T> cof_mat = result;
		float det = determinant();
		assert(fabs(det) >= 1e-6);
		result = result / det;
		return result;
	}

}

#endif // _TINYGlM_
