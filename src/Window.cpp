#include "Window.h"

Window::Window(){
    srand(time(NULL));
    isOver=0;
    score=0;

    font.loadFromFile("assets/kenvector_future_thin.ttf");
	back_spr.setTexture(TextureManager::Main().getBackground());

    text.setFont(font);	//napis: "Score: #)"
    text.setCharacterSize(50);
    text.setColor(sf::Color::White);

    text2.setFont(font);	//napis: "Bullets: #"
    text2.setCharacterSize(50);
    text2.setColor(sf::Color::White);
    text2.setPosition(1580, 0);

    text3.setFont(font);	//napis: "Reloading..."
    text3.setCharacterSize(50);
    text3.setColor(sf::Color::White);
    text3.setPosition(1580, 60);
    text3.setString("Reloading...");

    text4.setFont(font);	//napis: Time: #; pomocny w debugowaniu rzeczy zwi¹zanych z czasem"
    text4.setCharacterSize(50);
    text4.setColor(sf::Color::White);
    text4.setPosition(0, 60);
}

Window::~Window(){
    //dtor
}

void Window::displayWindow(){
	Level level;
	File file;
	sf::Clock clock /*dodawanie przeciwników*/, clock2 /*prze³adowywanie*/, clock3 /*wystrza³ przeciników*/;
	sf::Time t1, t2;
	bool isLeft = 0, isRight = 0, isUp = 0, isDown = 0, isShoot = 0, isReload = 0, isAkimbo = 0, isGuided = 0, //klawisze
		isBossFight = 0;
	unsigned int retarder = 0 /*ogranicznik strzelania*/, bulletCount = 0 /*wystrzelone naboje*/, backgroundCount = 0 /*licznik przesuniêæ t³a*/;
	sf::Music music;
	music.openFromFile("assets/background_music1.flac");
	music.setLoop(true);
	music.play();
	while (game_window->isOpen() && isOver == 0 && score < 100) {
		sf::Event event;
		t1 = clock.getElapsedTime();
		while (game_window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left)   isLeft = 1;
				if (event.key.code == sf::Keyboard::Right)  isRight = 1;
				if (event.key.code == sf::Keyboard::Up)     isUp = 1;
				if (event.key.code == sf::Keyboard::Down)   isDown = 1;
				if (event.key.code == sf::Keyboard::Space)  isShoot = 1;
				if (event.key.code == sf::Keyboard::D)		isAkimbo = 1;
				if (event.key.code == sf::Keyboard::G)      isGuided = 1;
				if (event.key.code == sf::Keyboard::S && isBossFight == false) {
					try {
						level.score = score;
						file.save(level);
					}
					catch (std::exception &e) { std::cout << e.what() << std::endl; }
				}
				if (event.key.code == sf::Keyboard::L)
				{
					try {
						file.load(level);
						score = level.score;
					}
					catch (std::exception &e) { std::cout << e.what() << std::endl; }
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Left)   isLeft = 0;
				if (event.key.code == sf::Keyboard::Right)  isRight = 0;
				if (event.key.code == sf::Keyboard::Up)     isUp = 0;
				if (event.key.code == sf::Keyboard::Down)   isDown = 0;
				if (event.key.code == sf::Keyboard::Space)  isShoot = 0;
				if (event.key.code == sf::Keyboard::D)		isAkimbo = 0;
				if (event.key.code == sf::Keyboard::G)      isGuided = 0;
			}
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				game_window->close();
		}
		game_window->clear(sf::Color::Black);
		if (backgroundCount == 481) {
			back_spr.setPosition(0, 0);
			backgroundCount = 0;
		}
		else if (backgroundCount > 0) {
			back_spr.move(-4, 0);
			++backgroundCount;
		}
		else if (backgroundCount == 0)
			++backgroundCount;
		game_window->draw(back_spr);
		if (sf::Joystick::isConnected(0)) {	//obs³uga pada
			double x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
			double y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
			if (x > 5 || x < -5 || y>5 || y < -5)
				level.jet.moove(0.2*x, 0.2*y);
		}
		level.jet.tilt = 0;	//zmiana tekstur statku w zale¿noœci od kierunku ruchu
		if (isLeft == 1)  level.jet.moove(-15, 0);	//ruch statku gracza
		if (isRight == 1) level.jet.moove(15, 0);
		if (isUp == 1)	{ level.jet.moove(0, -15); level.jet.tilt = 1; }
		if (isDown == 1) { level.jet.moove(0, 15); level.jet.tilt = 2; }
		level.correctJet();	//poprawa wspó³rzêdnych statku, tzn. czy nie wylecia³a za ekran
        if ((isShoot==1 || sf::Joystick::isButtonPressed(0, 1)) && retarder==0 && isReload==0)	//strza³ zwyk³y
			level.jet.shootPrimary(level.missile_list, bulletCount);
        if ((isAkimbo==1 || sf::Joystick::isButtonPressed(0, 2)) && retarder==0 && isReload==0)	//strza³ podwójny
			level.jet.shootAkimbo(level.missile_list, bulletCount);
        if ((isGuided==1 || sf::Joystick::isButtonPressed(0, 3)) && level.missileGuided_list.size()==0 && level.enemy_list.size()>0)	//strza³ kierowany
			level.jet.shootGuided(level.missileGuided_list, level.enemy_list, bulletCount);
		level.manageObstacles(game_window);	//metody zarz¹dzaj¹ce ruchem, kolizjami i innymi zachowaniami obiektów
		level.manageMissilesEnemy(game_window);
		level.manageEnemies(game_window, clock3);
		level.manageMissiles(game_window, score);
		level.manageMissilesGuided(game_window, score);
        if (t1.asSeconds()>2 && score<10)	//losowe dodawanie przeciwników
            level.randomize(clock);
		if (t1.asSeconds() > 5 && isBossFight == false)
		{	//walka z bossem
			Boss* boss = new Boss(9999, 2000, 550);
			level.enemy_list.push_back(boss);
			isBossFight = true;
		}
        if (bulletCount>=AMMO){	//rozpoczêcie prze³adowania dzia³
            bulletCount=0;
            isReload=1;
            clock2.restart();
        }
        t2=clock2.getElapsedTime();	//zakoñczenie prze³adowania dzia³
        if (isReload==1 && t2.asSeconds()>2){
            isReload=0;
            clock2.restart();
        }
        level.jet.display(game_window);	//wyœwietlanie statku gracza
        isOver=level.jet.doesCollide(level.obstacle_list, level.enemy_list, level.missileEnemy_list);	//kolizje statku gracza
        retarder++;    retarder=retarder%5;
        {
            std::stringstream ss;
            ss << score;
            std::string str = ss.str();
            text.setString("Score: " + str);
        }
        {
            std::stringstream ss;
            ss << AMMO-bulletCount;
            std::string str = ss.str();
            text2.setString("Bullets: " + str);
        }
        {
            std::stringstream ss;
            ss << t2.asSeconds();
            std::string str = ss.str();
            text4.setString("Time: " + str);
        }
        game_window->draw(text);	//wyœwietlanie tekstów
        game_window->draw(text2);
        if (isReload==1)	game_window->draw(text3);
        game_window->draw(text4);
        game_window->display();
    }
}

void Window::createWindow(){	//utworzenie okna i przygotwanie go do gry
	game_window = new sf::RenderWindow;
	game_window->create(sf::VideoMode(1920, 1080), "Kosmo Igra", sf::Style::Fullscreen);
	game_window->setVerticalSyncEnabled(true);
	game_window->setKeyRepeatEnabled(false);
	game_window->setMouseCursorVisible(false);
}


bool Window::scoreboard()
{
    sf::Text text1, text2, text3, text4;
    text1.setFont(font);
    text1.setCharacterSize(100);
    text1.setColor(sf::Color::White);
    text1.setString("Score");
    text1.setPosition(400, 100);

    text2.setFont(font);
    text2.setCharacterSize(100);
    text2.setColor(sf::Color::White);
    text2.setPosition(960, 300);

    text3.setFont(font);
    text3.setCharacterSize(100);
    text3.setColor(sf::Color::White);
    text3.setString("New Game -> [N]");
    text3.setPosition(400, 600);

    text4.setFont(font);
    text4.setCharacterSize(100);
    text4.setColor(sf::Color::White);
    text4.setString("Quit game -> [Esc]");
    text4.setPosition(400, 800);

	sf::Texture win_tex;
	sf::Sprite win_spr;
	win_tex.loadFromFile("assets/victory.png");
	win_spr.setTexture(win_tex);
	win_spr.setOrigin(619.5, 509.5);
	win_spr.setPosition(960, 550);

	sf::Texture lose_tex;
	sf::Sprite lose_spr;
	lose_tex.loadFromFile("assets/defeat.png");
	lose_spr.setTexture(lose_tex);
	lose_spr.setOrigin(288, 319.5);
	lose_spr.setPosition(960, 550);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("assets/boss_death.flac");
	sf::Sound sound;
	sound.setBuffer(buffer);

	sf::SoundBuffer buffer2;
	buffer2.loadFromFile("assets/def_snd.wav");
	sf::Sound sound2;
	sound2.setBuffer(buffer2);

	sf::Music music;
	music.openFromFile("assets/score_music.flac");
	music.play();

	if (score>=100) //co siê stanie, gdy gracz wygra
		sound.play();
	else	//a co, gdy przegra
		sound2.play();
	bool isEnter = 0;	//klawisze

    while (game_window->isOpen())
    {
        sf::Event event;
        while (game_window->pollEvent(event))	//zczytwanie eventów z klawiatury
        {
            if ((event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) || sf::Joystick::isButtonPressed(0, 8))
                game_window->close();
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) || sf::Joystick::isButtonPressed(0, 9))
                return true;	//to pozwala na zamkniêcie obrazka pora¿ki/wygranej
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return)
				isEnter = 1;
        }
        std::stringstream ss;
        ss << score;
        std::string str = ss.str();
        text2.setString(str);
        game_window->clear(sf::Color::Black);
        game_window->draw(text1);
        game_window->draw(text2);
        game_window->draw(text3);
        game_window->draw(text4);
		if (score >= 100 && isEnter==0)
			game_window->draw(win_spr); //obrazek wygranej
		else if (isEnter==0)
			game_window->draw(lose_spr);	//obrazek pora¿ki
        game_window->display();
    }
    return false;
}
