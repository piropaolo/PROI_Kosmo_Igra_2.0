#include "Obstacle.h"

Obstacle::Obstacle(unsigned int id, unsigned int size, double x, double y)
{
    this->x=x;
    this->y=y;
    this->id=id;
	this->size = size;
    std::cout<<"Obstacle #"<<id<<" added."<<std::endl;
}

void Obstacle::randomize()
{
	x = ((rand() % 200) + 1920);
	y = (rand() % 1080);
	size = (rand() % 10) + 1;
}

void Obstacle::loadTexture()
{
	texture = TextureManager::Main().getObstacle(size);
	sprite.setTexture(texture);
}

void Obstacle::display(sf::RenderWindow *game_window){
	moove(-2, 0);
    sprite.setPosition((float)getX(), (float)getY());
    game_window->draw(sprite);
}

bool Obstacle::doesOverlap(std::list <Obstacle*> &obstacle_list)
{
    for (auto it=obstacle_list.begin(); it!=obstacle_list.end(); ++it) 
        {	//sprawdzenie czy tworzona przeszkoda nie pokrywa siê z ju¿ istniej¹cymi
            double x, y;
            x=(*it)->getX()-getX();
            y=(*it)->getY()-getY();
            if (x<120 && x>-120 && y<98 && y>-98)
            {
                std::cout<<"Obstacle overlapping."<<std::endl;
                return true;
            }
        }
    return false;
}

bool Obstacle::doesCollide(std::list <Obstacle*> &obstacle_list)
{
	if (getX() < -100)	//wylecenie za lew¹ krawêdŸ ekranu
		return true;
	return false;
}

Obstacle::~Obstacle()
{
    std::cout<<"Obstacle #"<<id<<" destroyed."<<std::endl;
}

