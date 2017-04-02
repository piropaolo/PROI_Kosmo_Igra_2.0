#pragma once
#include "Object.h"
class Obstacle:
	public Object
{
    public:
        Obstacle(unsigned int id, unsigned int size = 0, double x = 0, double y = 0);
        void randomize();
		void loadTexture();
        void display(sf::RenderWindow *game_window);
        bool doesOverlap(std::list <Obstacle*> &obstacle_list);
        bool doesCollide(std::list <Obstacle*> &obstacle_list);
        virtual ~Obstacle();
		unsigned int size;
};

