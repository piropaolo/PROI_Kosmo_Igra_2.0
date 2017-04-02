#include "..\include\EnemyDodger.h"

EnemyDodger::~EnemyDodger()
{
}

void EnemyDodger::display(sf::RenderWindow *game_window)
{
	moove(-2, 10 * sin(0.02*getX()));	//latanie po sinusie
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}
