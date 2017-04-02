//Autor: Pawe³ Kamiñski, grupa I3, 277307
//Prowadz¹cy: mgr in¿. Bart³omiej Gajewski
#include "Window.h"


int main()
{

	bool next = 0;
	do
	{
		Window window;
		if (!next)
			window.createWindow();	//utworzenie okna
		window.displayWindow();		//wyœwietlenie okna
		next = window.scoreboard();	//mo¿liwoœæ dalszej gry, zale¿na od woli gracza
	} while (next);
	return 0;
}
