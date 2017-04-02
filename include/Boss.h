#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss(unsigned int id, double x = 0, double y = 0, int hp = 2000)
		: Enemy(id, x, y, hp)
	{
		texture = TextureManager::Main().getBoss();
		sprite.setTexture(texture);
	}
	void display(sf::RenderWindow *game_window);
	virtual ~Boss();
	int counter = 0, ud = 0;
};

