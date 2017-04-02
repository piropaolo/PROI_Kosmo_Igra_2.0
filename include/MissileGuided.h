#pragma once
#include "Missile.h"
class MissileGuided :
	public Missile
{
public:
	MissileGuided(double x, double y)
		: Missile(x, y)
	{
		sprite.setTexture(TextureManager::Main().getMissileGuided());
	}
	virtual ~MissileGuided();
	Enemy* enemyNearest(std::list <Enemy*> &enemy_list);
	bool doesCollide(std::list <Enemy*> &enemy_list, std::list <Obstacle*> &obstacle_list, int &score);
	void display(sf::RenderWindow *game_window, double y);
	Enemy* nearest;
};

