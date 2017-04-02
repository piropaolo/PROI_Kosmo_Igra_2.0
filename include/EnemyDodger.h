#pragma once
#include "Enemy.h"
class EnemyDodger :
	public Enemy
{
public:
	EnemyDodger(unsigned int id, double x = 0, double y = 0, int hp = 100)
		: Enemy(id, x, y, hp)
	{
		texture = TextureManager::Main().getEnemyDodger();
		sprite.setTexture(texture);
	}
	void display(sf::RenderWindow *game_window);
	virtual ~EnemyDodger();
};

