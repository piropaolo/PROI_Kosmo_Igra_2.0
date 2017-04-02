#include "..\include\Object.h"

Object::Object()
{
}

void Object::moove(double a, double b)
{
	x = x + a;
	y = y + b;
}

void Object::create()
{
	std::cout << "Input x: ";
	std::cin >> x;
	std::cout << "Input y: ";
	std::cin >> y;
}

double Object::getX()
{
	return x;
}

double Object::getY()
{
	return y;
}

Object::~Object()
{
}
