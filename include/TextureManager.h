#pragma once
#include <SFML\Graphics.hpp>
class TextureManager
{
	TextureManager();
	virtual ~TextureManager();
	sf::Texture *Enemy1;
	sf::Texture *EnemyDodger;
	sf::Texture *EnemyShooter;
	sf::Texture *Boss;
	sf::Texture *Background;
	sf::Texture *Missle;
	sf::Texture *MissileGuided;
	sf::Texture *MissileEnemy;
	sf::Texture *Obstacle1;
	sf::Texture *Obstacle2;
	sf::Texture *Obstacle3;
	sf::Texture *Obstacle4;
	sf::Texture *Obstacle5;
	sf::Texture *Obstacle6;
	sf::Texture *Obstacle7;
	sf::Texture *Obstacle8;
	sf::Texture *Obstacle9;
	sf::Texture *Obstacle10;
public:
	sf::Texture& getEnemy1();
	sf::Texture& getEnemyDodger();
	sf::Texture& getEnemyShooter();
	sf::Texture& getBoss();
	sf::Texture& getBackground();
	sf::Texture& getMissle();
	sf::Texture& getMissileGuided();
	sf::Texture& getMissileEnemy();
	sf::Texture& getObstacle(unsigned int &size);
	static TextureManager& Main()
	{
		static TextureManager instance;
		return instance;
	}
};

