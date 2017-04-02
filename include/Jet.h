#pragma once
#define AMMO 30
#include "Enemy.h"
#include "Obstacle.h"
#include "MissileGuided.h"
#include "MissileEnemy.h"
class Jet
{
    public:
		Jet(double x = 0, double y = 0);
		void moove(double a, double b);
        virtual ~Jet();
        double getX();
        double getY();
        void setX(double a);
        void setY(double b);
		void shootPrimary(std::list <Missile*> &missile_list, unsigned int &rounds);
		void shootAkimbo(std::list <Missile*> &missile_list, unsigned int &rounds);
		void shootGuided(std::list <MissileGuided*> &missileGuided_list, std::list <Enemy*> &enemy_list,
			unsigned int &rounds);
        void display(sf::RenderWindow *game_window);
        bool doesCollide(std::list <Obstacle*> &obstacle_list, std::list <Enemy*> &enemy_list,
			std::list <MissileEnemy*> &missileE_list);
		unsigned int tilt;
		sf::Texture jet_tex;
		sf::Texture jet_tex1;
		sf::Texture jet_tex2;
		sf::Sprite jet_spr;
		sf::Sprite jet_spr1;
		sf::Sprite jet_spr2;
    protected:
        double x,y;
		sf::SoundBuffer buffer;
		sf::Sound sound;
};
