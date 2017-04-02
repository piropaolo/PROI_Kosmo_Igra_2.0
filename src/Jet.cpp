#include "Jet.h"
#define txtr TextureManager::Main().getMissileEnemy()

Jet::Jet(double x, double y){
    this->x=x;
    this->y=y;
	tilt = 0;
    jet_tex.loadFromFile("assets/player.png");			//tekstura domy�lna
	jet_tex1.loadFromFile("assets/playerLeft.png");		//tekstura, gdy samolot leci w g�r�
	jet_tex2.loadFromFile("assets/playerRight.png");	//tekstura, gdy samolot leci w d�
    jet_spr.setTexture(jet_tex);
	jet_spr1.setTexture(jet_tex1);
	jet_spr2.setTexture(jet_tex2);
	buffer.loadFromFile("assets/laserowa_dzida2.flac");
	sound.setBuffer(buffer);
}

void Jet::moove(double a, double b){
    x=x+a;
    y=y+b;
}

Jet::~Jet(){

}

double Jet::getX(){
    return x;
}

double Jet::getY(){
    return y;
}

void Jet::setX(double a){
    x=a;
}

void Jet::setY(double b){
    y=b;
}

void Jet::shootPrimary(std::list <Missile*> &missile_list, unsigned int &rounds) {
	sound.play();	//strza� ze zwyk�ego dzia�a
	Missile* missile = new Missile(getX(), getY() + 43);
	missile_list.push_back(missile);
	++rounds;
}

void Jet::shootAkimbo(std::list <Missile*> &missile_list, unsigned int &rounds)
{	//strza� z podw�jnego dzia�ka
	Missile* missile = new Missile(getX()-30, getY() + 80);
	missile_list.push_back(missile);
	if (rounds<(AMMO - 1)) {
		Missile* missile2 = new Missile(getX()-30, getY() + 10);
		missile_list.push_back(missile2);
	}
	rounds += 2;
}

void Jet::shootGuided(std::list <MissileGuided*> &missileGuided_list, std::list <Enemy*> &enemy_list, unsigned int &rounds)
{	//strza� pociskiem sterowanym
	MissileGuided* missileGuided = new MissileGuided(getX() + 100, getY() + 49.5);
	missileGuided->nearest = missileGuided->enemyNearest(enemy_list);
	missileGuided_list.push_back(missileGuided);
	++rounds;
}

void Jet::display(sf::RenderWindow *game_window){
	switch (tilt)
	{	//sprawdzenie czy samolot nie leci w g�r� lub w do�, w celu zmiany tekstury
		case 0:
			jet_spr.setPosition((float)getX(), (float)getY());
			game_window->draw(jet_spr);
			break;
		case 1:
			jet_spr1.setPosition((float)getX(), (float)getY());
			game_window->draw(jet_spr1);
			break;
		case 2:
			jet_spr2.setPosition((float)getX(), (float)getY());
			game_window->draw(jet_spr2);
			break;
	}
}

bool Jet::doesCollide(std::list <Obstacle*> &obstacle_list, std::list <Enemy*> &enemy_list,
	std::list <MissileEnemy*> &missileEnemy_list)
{
    for (auto it=obstacle_list.begin(); it!=obstacle_list.end(); ++it)	//kolizja z przeszkodami
    {
        double x, y;
        x=(*it)->getX()-getX();
        y=(*it)->getY()-getY();
		if (x<jet_tex.getSize().x && x>-1.0*(*it)->texture.getSize().x && 
			y<jet_tex.getSize().y && y>-1.0*(*it)->texture.getSize().y)
        {
            std::cout<<"Jet-to-obstacle collision."<<std::endl;
            return true;
        }
    }
    for (auto it=enemy_list.begin(); it!=enemy_list.end(); ++it)	//kolizja z przeciwnikami
    {
        double x, y;
        x=(*it)->getX()-getX();
        y=(*it)->getY()-getY();
        if (x<jet_tex.getSize().x && x>-1.0*(*it)->texture.getSize().x &&
			y<jet_tex.getSize().y && y>-1.0*(*it)->texture.getSize().y)
        {
            std::cout<<"Jet-to-enemy collision."<<std::endl;
            return true;
        }
    }
	for (auto it = missileEnemy_list.begin(); it != missileEnemy_list.end(); ++it)	//kolizja z pociskami wroga
	{
		double x, y;
		x = (*it)->getX() - getX();
		y = (*it)->getY() - getY();
		if (x<jet_tex.getSize().x && x>-1.0*txtr.getSize().x &&
			y<jet_tex.getSize().y && y>-1.0*txtr.getSize().y)
		{
			std::cout << "Jet-to-missile collision." << std::endl;
			return true;
		}

	}
    return false;
}
