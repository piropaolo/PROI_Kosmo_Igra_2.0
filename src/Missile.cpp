#include "Missile.h"
#define txtr TextureManager::Main().getMissle()

void Missile::moove(double a, double b)
{
    x=x+a;
    y=y+b;
}

Missile::~Missile()
{
    std::cout<<"Missile destroyed."<<std::endl;
}

double Missile::getX(){
    return x;
}

double Missile::getY(){
    return y;
}

bool Missile::doesCollide(std::list <Enemy*> &enemy_list, std::list <Obstacle*> &obstacle_list, int &score)
{
    for (auto jt=enemy_list.begin(); jt!=enemy_list.end(); )	//kolizja z przeciwnikami
    {
        double x, y;
        x=(*jt)->getX()-getX();
        y=(*jt)->getY()-getY();
        if (x<txtr.getSize().x && x>-1.0*(*jt)->texture.getSize().x &&
			y<txtr.getSize().y && y>-1.0*(*jt)->texture.getSize().y)
        {
			(*jt)->hp -= 50;
			if ((*jt)->hp <= 0) {
				if ((*jt)->id == 9999)
					score += 90;
				else
					++score;
				delete *jt;
				jt = enemy_list.erase(jt);
			}
			return true;
        }
		else ++jt;
    }
    for (auto jt=obstacle_list.begin(); jt!=obstacle_list.end(); )	//kolizja z przeszkodami
        {
            double x, y;
            x=(*jt)->getX()-getX();
            y=(*jt)->getY()-getY();
			if (x<txtr.getSize().x && x>-1.0*(*jt)->texture.getSize().x &&
				y<txtr.getSize().y && y>-1.0*(*jt)->texture.getSize().y)
				return true;
			else ++jt;
        }
	if (getX() > 2100)	//wylecenie za praw¹ krawêdŸ ekranu
		return true;
	return false;
}

void Missile::display(sf::RenderWindow *game_window) {
	moove(50, 0);
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}

