#include "..\include\Level.h"

Level::Level()
{
	jet.setX(275);
	jet.setY(650);
	enemy_qty = 0;
	obstacle_qty = 0;
}


Level::~Level()
{
}

void Level::manageEnemies(sf::RenderWindow *game_window, sf::Clock &clock)	//zarz¹dzanie przeciwnikami
{
	sf::Time t3;
	t3 = clock.getElapsedTime();
	for (auto it = enemy_list.begin(); it != enemy_list.end(); ) {
		(*it)->display(game_window);
		if (((*it)->id)%3==2 && t3.asSeconds()>3) {	//strza³ przeciwników
			MissileEnemy* missileEnemy = new MissileEnemy((*it)->getX()+30, (*it)->getY() + 45);
			missileEnemy_list.push_back(missileEnemy);
			clock.restart();
		}
		if ((*it)->id == 9999 && t3.asSeconds()>1)	//strzelanie bossa
		{
			MissileEnemy* missileEnemy = new MissileEnemy((*it)->getX()-30, (*it)->getY() + 50);
			missileEnemy_list.push_back(missileEnemy);
			MissileEnemy* missileEnemyDodger = new MissileEnemy((*it)->getX() - 30, (*it)->getY() + 100);
			missileEnemy_list.push_back(missileEnemyDodger);
			MissileEnemy* missileEnemyShooter = new MissileEnemy((*it)->getX() - 30, (*it)->getY() + 150);
			missileEnemy_list.push_back(missileEnemyShooter);
			MissileEnemy* missileEnemy4 = new MissileEnemy((*it)->getX() - 30, (*it)->getY() + 200);
			missileEnemy_list.push_back(missileEnemy4);
			MissileEnemy* missileEnemy5 = new MissileEnemy((*it)->getX() - 30, (*it)->getY() + 250);
			missileEnemy_list.push_back(missileEnemy5);
			MissileEnemy* missileEnemy6 = new MissileEnemy((*it)->getX() - 30, (*it)->getY() + 300);
			missileEnemy_list.push_back(missileEnemy6);
			clock.restart();
		}
		if ((*it)->doesCollide(enemy_list)) {
			delete *it;
			it = enemy_list.erase(it);
		}
		else ++it;
	}
}

void Level::manageObstacles(sf::RenderWindow *game_window)	//zarz¹dzanie przeszkodami
{
	for (auto it = obstacle_list.begin(); it != obstacle_list.end(); ) {
		(*it)->display(game_window);
		if ((*it)->doesCollide(obstacle_list)) {
			delete *it;
			it = obstacle_list.erase(it);
		}
		else ++it;
	}
}

void Level::manageMissiles(sf::RenderWindow *game_window, int &score)	//zarz¹dzanie pociskami "zwyk³ymi"
{
	for (auto it = missile_list.begin(); it != missile_list.end(); ) {
		(*it)->display(game_window);
		if ((*it)->doesCollide(enemy_list, obstacle_list, score))
		{
			delete *it;
			it = missile_list.erase(it);
		}
		else ++it;
	}
}

void Level::manageMissilesGuided(sf::RenderWindow *game_window, int &score)	//zarz¹dzanie pociskami sterowanymi
{
	for (auto it = missileGuided_list.begin(); it != missileGuided_list.end(); ) {
		if (enemy_list.size()) {
			double y = (*it)->nearest->getY() - (*it)->getY() + 42;
			(*it)->display(game_window, y);
			if ((*it)->doesCollide(enemy_list, obstacle_list, score)) {
				delete *it;
				it = missileGuided_list.erase(it);
			}
			else ++it;
		}
	}
}

void Level::manageMissilesEnemy(sf::RenderWindow *game_window)	//zarz¹dzanie pociskami wroga
{
	for (auto it = missileEnemy_list.begin(); it != missileEnemy_list.end(); ) {
		(*it)->display(game_window);
		if ((*it)->doesCollide(missile_list))
		{
			delete *it;
			it = missileEnemy_list.erase(it);
		}
		else ++it;
	}
}

void Level::randomize(sf::Clock &clock)	//losowe generowanie przeciwników i przeszkód
{
	Enemy* enemy = new Enemy(enemy_qty++);
	enemy->randomize();
	while (enemy->doesOverlap(enemy_list)) {
		enemy->randomize();
	}
	enemy->loadTexture();
	enemy_list.push_back(enemy);
	EnemyDodger* enemy2 = new EnemyDodger(enemy_qty++);
	enemy2->randomize();
	while (enemy2->doesOverlap(enemy_list)) {
		enemy2->randomize();
	}
	enemy_list.push_back(enemy2);
	EnemyShooter* enemy3 = new EnemyShooter(enemy_qty++);
	enemy3->randomize();
	while (enemy3->doesOverlap(enemy_list)) {
		enemy3->randomize();
	}
	enemy_list.push_back(enemy3);
	Obstacle* obstacle = new Obstacle(obstacle_qty++);
	obstacle->randomize();
	while (obstacle->doesOverlap(obstacle_list)) {
		obstacle->randomize();
	}
	obstacle->loadTexture();
	obstacle_list.push_back(obstacle);
	clock.restart();
}

void Level::correctJet()	//sprawdzenie czy samolot nie wylecia³ za ekran
{
	jet.getX()<0 ? jet.setX(0) : jet.setX(std::min(1920 - 1.0*jet.jet_tex.getSize().x, jet.getX()));
	jet.getY()<0 ? jet.setY(0) : jet.setY(std::min(1080 - 1.0*jet.jet_tex.getSize().y, jet.getY()));
}