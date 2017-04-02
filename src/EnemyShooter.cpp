#include "..\include\EnemyShooter.h"

EnemyShooter::~EnemyShooter()
{
}

void EnemyShooter::display(sf::RenderWindow *game_window)
{
	moove(-5, 0);	//latanie w lewo
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}
