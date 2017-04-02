#pragma once
#include "Missile.h"
class MissileEnemy :
	public Missile
{
public:
	MissileEnemy(double x, double y)
		: Missile(x, y)
	{
		sprite.setTexture(TextureManager::Main().getMissileEnemy());
	}
	virtual ~MissileEnemy();
	void display(sf::RenderWindow *game_window);
	bool doesCollide(std::list <Missile*> &missile_list);
};

