#pragma once
#include "Object.h"
#define PI 3.14159265
class Enemy:
	public Object
{
    public:
        Enemy(unsigned int id, double x=0, double y=0, int hp=100);
        void randomize();
        virtual void display(sf::RenderWindow *game_window);
		virtual void loadTexture();
        bool doesOverlap(std::list <Enemy*> &enemy_list);
        bool doesCollide(std::list <Enemy*> &enemy_list);
        virtual ~Enemy();
		int hp;
};

