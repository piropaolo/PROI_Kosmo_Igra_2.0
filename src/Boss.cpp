#include "..\include\Boss.h"

void Boss::display(sf::RenderWindow *game_window)
{
	if (counter < 30)	//wprowadzenie bossa na ekran
	{
		moove(-10, 0);
		++counter;
	}
	else	//latanie bossa góra/dó³
	{
		if (ud < 50)
			moove(0, -10);
		else
			moove(0, 10);
		++ud; ud = ud % 100;
	}
	sprite.setPosition((float)getX(), (float)getY());
	game_window->draw(sprite);
}


Boss::~Boss()
{
}
