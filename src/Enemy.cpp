#include "Enemy.h"

Enemy::Enemy(unsigned int id, double x, double y, int hp)
{
    this->x=x;
    this->y=y;
    this->id=id;
	this->hp = hp;
    std::cout<<"Enemy #"<<id<<" added."<<std::endl;
}

void Enemy::randomize()
{
    x=(rand()%200)+1920;
    y=(rand()%(1080-texture.getSize().y));
}

void Enemy::display(sf::RenderWindow *game_window){
	moove(-10, 0);
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}

void Enemy::loadTexture()
{
	texture = TextureManager::Main().getEnemy1();
	sprite.setTexture(texture);
}

bool Enemy::doesOverlap(std::list <Enemy*> &enemy_list)
{	//sprawdzenie czy tworzony przeciwnik nie pokrywa siê z ju¿ istniej¹cymi
    for (auto it=enemy_list.begin(); it!=enemy_list.end(); ++it)
        {
            double x, y;
            x=(*it)->getX()-getX();
            y=(*it)->getY()-getY();
			if (x<84 && x>-84 && y<93 && y>-93)
            {
                std::cout<<"Enemies overlapping."<<std::endl;
                return true;
            }
        }
    return false;
}

bool Enemy::doesCollide(std::list <Enemy*> &enemy_list)
{
	if (getX() < -200)	//wylecenie za lew¹ krawêdŸ ekranu
		return true;
	return false;
}

Enemy::~Enemy()
{
    std::cout<<"Enemy #"<<id<<" destroyed."<<std::endl;
}
