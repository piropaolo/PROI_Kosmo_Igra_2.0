#pragma once
#include "TextureManager.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <list>
class Object
{
public:
	Object();
	unsigned int id;
	void moove(double a, double b);
	void create();
	double getX();
	double getY();
	sf::Texture texture;
	sf::Sprite sprite;
	virtual ~Object();
protected:
	double x, y;
};

