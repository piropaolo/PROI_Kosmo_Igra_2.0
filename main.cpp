//Autor: Pawe� Kami�ski, grupa I3, 277307
//Prowadz�cy: mgr in�. Bart�omiej Gajewski
#include "Window.h"


int main()
{

	bool next = 0;
	do
	{
		Window window;
		if (!next)
			window.createWindow();	//utworzenie okna
		window.displayWindow();		//wy�wietlenie okna
		next = window.scoreboard();	//mo�liwo�� dalszej gry, zale�na od woli gracza
	} while (next);
	return 0;
}
