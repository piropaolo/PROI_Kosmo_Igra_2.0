#pragma once
#include "TextureManager.h"
#include "File.h"
#include <sstream>
class Window
{
    public:
        sf::RenderWindow *game_window;
        bool isOver;
        int score;
        void displayWindow();
        void createWindow();
        bool scoreboard();
        Window();
        virtual ~Window();
    protected:
    private:
		sf::Sprite back_spr;

        sf::Font font;
        sf::Text text;
        sf::Text text2;
        sf::Text text3;
        sf::Text text4;
};