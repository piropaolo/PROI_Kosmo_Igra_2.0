#include "..\include\File.h"

File::File()
{
}


File::~File()
{
}

class file_open_error : public std::exception { //wyj¹tek, gdy nie mo¿na utworzyæ pliku do zapisu
	virtual const char* what() const throw ()
	{
		return "Nie mo¿na utworzyæ pliku zapisu.";
	}
}open_err;

class file_not_found : public std::exception {	//wyj¹tek, gdy nie mo¿na znaleŸæ/otworzyæ pliku do wczytania
	virtual const char * what() const throw ()
	{
		return "Nie znaleziono pliku.";
	}
}not_found;

void File::save(Level &level)
{
	file.open("save/saveFile.txt", std::fstream::out | std::fstream::trunc);	//otwarcie pliku do nadpisania
	if (file.good())
		std::cout << "SaveFile is good." << std::endl;
	else {	//rzut wyj¹tkiem, gdy nie mo¿na utworzyæ pliku zapisu gry
		throw open_err;
	}
	file << level.score << std::endl;
	file << level.jet.getX() << " " << level.jet.getY() << std::endl;
	file << level.enemy_list.size() << std::endl;
	for (auto it = level.enemy_list.begin(); it != level.enemy_list.end(); ++it)
	{
		file << (*it)->id << " " << (*it)->hp << " " << (*it)->getX() << " " << (*it)->getY() << std::endl;
	}
	file << level.obstacle_list.size()<<std::endl;
	for (auto it = level.obstacle_list.begin(); it != level.obstacle_list.end(); ++it)
	{
		file << (*it)->id << " " << (*it)->size << " " << (*it)->getX() << " " << (*it)->getY() << std::endl;
	}
	file.close();
}

void File::load(Level &level)
{
	file.open("save/saveFile.txt", std::fstream::in);	//otwarcie pliku do odczytu
	if (file.good())
		std::cout << "SaveFile is good." << std::endl;
	else {	//rzut wyj¹tkiem, gdy nie ma pliku zapisu gry
		throw not_found;
	}
	//aby wczytaæ elementy, najpierw czyœcimy wszystkie listy
	for (auto &it : level.enemy_list) delete it; level.enemy_list.clear();
	for (auto &it : level.obstacle_list) delete it; level.obstacle_list.clear();
	for (auto &it : level.missile_list) delete it; level.missile_list.clear();
	for (auto &it : level.missileEnemy_list) delete it; level.missileEnemy_list.clear();
	for (auto &it : level.missileGuided_list) delete it; level.missileGuided_list.clear();
	file >> level.score;
	double x, y;
	file >> x >> y;
	level.jet.setX(x); level.jet.setY(y);
	int n;
	file >> n;
	for (int i = 0; i < n; ++i){
		unsigned int id; int hp; double x; double y;
		file >> id >> hp >> x >> y;
		if (id == 9999){	//dodawanie bossa
			Boss* boss = new Boss(id, x, y, hp);
			level.enemy_list.push_back(boss);
		}
		else if (id % 3 == 0){	//dodawanie "zwyk³ych" przeciwników
			Enemy* enemy = new Enemy(id, x, y, hp);
			enemy->loadTexture();
			level.enemy_list.push_back(enemy);
		}
		else if (id % 3 == 1){	//dodawanie przeciwników unikaj¹cych
			EnemyDodger* enemy2 = new EnemyDodger(id, x, y, hp);
			level.enemy_list.push_back(enemy2);
		}
		else if (id % 3 == 2){	//dodawanie przeciwników strzelaj¹cych
			EnemyShooter* enemy3 = new EnemyShooter(id, x, y, hp);
			level.enemy_list.push_back(enemy3);
		}
	}
	file >> n;
	for (int i = 0; i < n; ++i)
	{	//dodawanie przeszkód
		unsigned int id; unsigned int size; double x; double y;
		file >> id >> size >> x >> y;
		Obstacle* obstacle = new Obstacle(id, size, x, y);
		obstacle->loadTexture();
		level.obstacle_list.push_back(obstacle);
	}
	file.close();
}