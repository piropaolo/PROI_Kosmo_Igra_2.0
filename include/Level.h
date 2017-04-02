#pragma once
#include "EnemyDodger.h"
#include "EnemyShooter.h"
#include "Boss.h"
#include "Obstacle.h"
#include "MissileGuided.h"
#include "MissileEnemy.h"
#include "Jet.h"
class Level
{
public:
	Level();
	virtual ~Level();
	int score;
	Jet jet;
	std::list <Enemy*> enemy_list;
	std::list <Obstacle*> obstacle_list;
	std::list <Missile*> missile_list;
	std::list <MissileGuided*> missileGuided_list;
	std::list <MissileEnemy*> missileEnemy_list;
	void manageEnemies(sf::RenderWindow *game_window, sf::Clock &clock);
	void manageObstacles(sf::RenderWindow *game_window);
	void manageMissiles(sf::RenderWindow *game_window, int &score);
	void manageMissilesGuided(sf::RenderWindow *game_window, int &score);
	void manageMissilesEnemy(sf::RenderWindow *game_window);
	void randomize(sf::Clock &clock);
	void correctJet();
private:
	unsigned int enemy_qty, obstacle_qty;
};

