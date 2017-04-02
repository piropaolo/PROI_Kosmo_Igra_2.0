#include "..\include\TextureManager.h"

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

sf::Texture& TextureManager::getEnemy1()
{
	if (Enemy1 == NULL) {
		Enemy1 = new sf::Texture;
		Enemy1->loadFromFile("assets/enemyBlue1.png");
	}
	return *Enemy1;
}

sf::Texture& TextureManager::getEnemyDodger()
{
	if (EnemyDodger == NULL) {
		EnemyDodger = new sf::Texture;
		EnemyDodger->loadFromFile("assets/enemyGreen2.png");
	}
	return *EnemyDodger;
}

sf::Texture& TextureManager::getEnemyShooter()
{
	if (EnemyShooter == NULL) {
		EnemyShooter = new sf::Texture;
		EnemyShooter->loadFromFile("assets/enemyBlack3.png");
	}
	return *EnemyShooter;
}

sf::Texture& TextureManager::getBoss()
{
	if (Boss == NULL) {
		Boss = new sf::Texture;
		Boss->loadFromFile("assets/boss.png");
	}
	return *Boss;
}

sf::Texture& TextureManager::getBackground()
{
	if (Background == NULL) {
		Background = new sf::Texture;
		Background->loadFromFile("assets/bckgnd.png");
	}
	return *Background;
}

sf::Texture& TextureManager::getMissle()
{
	if (Missle == NULL) {
		Missle = new sf::Texture;
		Missle->loadFromFile("assets/laserRed16.png");
	}
	return *Missle;
}

sf::Texture& TextureManager::getMissileGuided()
{
	if (MissileGuided == NULL) {
		MissileGuided = new sf::Texture;
		MissileGuided->loadFromFile("assets/laserGreen10.png");
	}
	return *MissileGuided;
}

sf::Texture& TextureManager::getMissileEnemy()
{
	if (MissileEnemy == NULL) {
		MissileEnemy = new sf::Texture;
		MissileEnemy->loadFromFile("assets/laserBlue16.png");
	}
	return *MissileEnemy;
}

sf::Texture& TextureManager::getObstacle(unsigned int &size)
{	//zwrócenie odpowiedniej tekstury w zale¿noœci od rozmiaru przeszkody
	if (Obstacle1 == NULL) {
		Obstacle1 = new sf::Texture;
		Obstacle1->loadFromFile("assets/meteorGrey_big1.png");
	}
	if (Obstacle2 == NULL) {
		Obstacle2 = new sf::Texture;
		Obstacle2->loadFromFile("assets/meteorGrey_big2.png");
	}
	if (Obstacle3 == NULL) {
		Obstacle3 = new sf::Texture;
		Obstacle3->loadFromFile("assets/meteorGrey_big3.png");
	}
	if (Obstacle4 == NULL) {
		Obstacle4 = new sf::Texture;
		Obstacle4->loadFromFile("assets/meteorGrey_big4.png");
	}
	if (Obstacle5 == NULL) {
		Obstacle5 = new sf::Texture;
		Obstacle5->loadFromFile("assets/meteorGrey_med1.png");
	}
	if (Obstacle6 == NULL) {
		Obstacle6 = new sf::Texture;
		Obstacle6->loadFromFile("assets/meteorGrey_med2.png");
	}
	if (Obstacle7 == NULL) {
		Obstacle7 = new sf::Texture;
		Obstacle7->loadFromFile("assets/meteorGrey_small1.png");
	}
	if (Obstacle8 == NULL) {
		Obstacle8 = new sf::Texture;
		Obstacle8->loadFromFile("assets/meteorGrey_small2.png");
	}
	if (Obstacle9 == NULL) {
		Obstacle9 = new sf::Texture;
		Obstacle9->loadFromFile("assets/meteorGrey_tiny1.png");
	}
	if (Obstacle10 == NULL) {
		Obstacle10 = new sf::Texture;
		Obstacle10->loadFromFile("assets/meteorGrey_tiny2.png");
	}
	switch (size)
	{
	case 1:	return *Obstacle1;	break;
	case 2:	return *Obstacle2;	break;
	case 3:	return *Obstacle3;	break;
	case 4:	return *Obstacle4;	break;
	case 5:	return *Obstacle5;	break;
	case 6:	return *Obstacle6;	break;
	case 7:	return *Obstacle7;	break;
	case 8:	return *Obstacle8;	break;
	case 9:	return *Obstacle9;	break;
	case 10:return *Obstacle10;	break;
	}
}