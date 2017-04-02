#include "..\include\MissileEnemy.h"
#define txtr TextureManager::Main().getMissle()
#define txtrE TextureManager::Main().getMissileEnemy()

MissileEnemy::~MissileEnemy()
{
}

void MissileEnemy::display(sf::RenderWindow *game_window)
{
	moove(-20, 0);
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}

bool MissileEnemy::doesCollide(std::list <Missile*> &missile_list)
{
	for (auto jt = missile_list.begin(); jt != missile_list.end(); )	//kolizja z pociskami gracza
	{
		double x, y;
		x = (*jt)->getX() - getX();
		y = (*jt)->getY() - getY();
		if (x<txtrE.getSize().x && x>-1.0*txtr.getSize().x &&
			y<txtrE.getSize().y && y>-1.0*txtr.getSize().y)
		{
			delete *jt;
			jt = missile_list.erase(jt);
			return true;
		}
		else ++jt;
	}
	if (getX() < -200)	//wylecenie za lew¹ krawêdŸ ekranu
		return true;
	return false;
}