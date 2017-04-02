#pragma once
#include "Enemy.h"
#include "Obstacle.h"
class Missile
{
    public:
		Missile(double x, double y)
			: x(x), y(y)
		{
			sprite.setTexture(TextureManager::Main().getMissle());
		}
        void moove(double a, double b);
        virtual ~Missile();
        double getX();
        double getY();
        virtual bool doesCollide(std::list <Enemy*> &enemy_list, std::list <Obstacle*> &obstacle_list, int &score);
		virtual void display(sf::RenderWindow *game_window);
		sf::Sprite sprite;
    protected:
        double x,y;
};
