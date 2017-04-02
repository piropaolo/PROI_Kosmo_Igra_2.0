#pragma once
#include "Enemy.h"
class EnemyShooter :
	public Enemy
{
public:
	EnemyShooter(unsigned int id, double x = 0, double y = 0, int hp = 100)
		: Enemy(id, x, y, hp)
	{
		texture = TextureManager::Main().getEnemyShooter();
		sprite.setTexture(texture);
	}
	void display(sf::RenderWindow *game_window);
	virtual ~EnemyShooter();
};

