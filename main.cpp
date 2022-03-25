//#include<SDL2/SDL.h>
#include"TinyGlm.h"
#include<iostream>


int main()
{
	TinyGlm::vec3 a(1, 1, 1);
	TinyGlm::vec3 b(2, 2, 2);
	TinyGlm::vec3 c(3, 3, 3);

	TinyGlm::vec3 d;
	d = a + b;
	std::cout << " a+b :" << d.x << " " << d.y << " " << d.z << std::endl;
	d += a ;
	std::cout << " d += a :" << d.x << " " << d.y << " " << d.z << std::endl;

	TinyGlm::vec3 f(std::move(d));
	std::cout << "move d to f " << f.x << " " << f.y << " " << f.z << std::endl;

	f = a - b;
	std::cout << " a-b :" << f.x << " " << f.y << " " << f.z << std::endl;
	f -= a;
	std::cout << " d -= a :" << f.x << " " << f.y << " " << f.z << std::endl;

	TinyGlm::vec3 g(0, 1, 0);
	TinyGlm::vec3 h(1, 0, 0);
	TinyGlm::vec3 cro= g.cross(h);

	std::cout << " cross :" << cro.x << " " << cro.y << " " << cro.z << std::endl;

	float k = cro.y;

	float fl = a.dot(b);

	std::cout << " dot :" << fl<< std::endl;

	fl = a.length();
	std::cout << " length :" << fl << std::endl;

	a = a.normalize();
	std::cout << "a.normalize :" << a.x << " " << a.y << " " << a.z << std::endl;

	std::cout << " k :" << k << std::endl;
	k = -0.0f;
	std::cout << " k :" << k << std::endl;

	

	k += 1.0f;
	std::cout << " k :" << k << std::endl;
	return 0;
}