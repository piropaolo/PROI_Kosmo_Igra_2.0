#include "..\include\missileGuided.h"
#define txtr TextureManager::Main().getMissileGuided()

MissileGuided::~MissileGuided()
{
}

Enemy* MissileGuided::enemyNearest(std::list <Enemy*> &enemy_list)
{	//metoda umo¿liwiaj¹ca znalezienie najbli¿szego przeciwnika
	Enemy* nearest;
	double minX = 1920;
	double minY = 1080;
	for (auto it=enemy_list.begin(); it!=enemy_list.end(); ++it)
	{
		double x, y;
		x = (*it)->getX() - getX();
		y = (*it)->getY() - getY();
		if ((x*x + y*y)<(minX*minX + minY*minY))
		{
			minX = x;
			minY = y;
			nearest = *it;
		}
	}
	return nearest;
}

bool MissileGuided::doesCollide(std::list <Enemy*> &enemy_list, std::list <Obstacle*> &obstacle_list, int &score)
{
	for (auto jt=enemy_list.begin(); jt!=enemy_list.end(); )	//kolizja z przeciwnikami
	{
		double x, y;
		x = (*jt)->getX() - getX();
		y = (*jt)->getY() - getY();
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
	if (getX() > 1920)	//wylecenie za praw¹ krawêdzi¹ ekranu
		return true;
	return false;
}

void MissileGuided::display(sf::RenderWindow *game_window, double y) {
	moove(20, 0.1*y);
	sprite.setRotation(float(atan2(0.1*y, 20)*180/PI));	//obrót sprite'a o pewny k¹t, zale¿ny od przemieszczenia
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}
