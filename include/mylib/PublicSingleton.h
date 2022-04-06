#pragma once
#ifndef _PUBLICSINGLETON_
#define _PUBLICSINGLETON_
#include <mutex>
#include <memory>


template<typename T>
class PublicSingleton;


template<typename T>
class PublicSingleton
{
private:
	PublicSingleton() = default;
	~PublicSingleton() = default;
	PublicSingleton(const PublicSingleton&) = delete;
	PublicSingleton(PublicSingleton&&) = delete;
	PublicSingleton& operator=(const PublicSingleton&) = delete;
	PublicSingleton& operator=(PublicSingleton&&) = delete;

public:
	static T& get_instance()
	{
		static T _instance;
		return _instance;
	}
};


#endif // _PUBLICSINGLETON_

