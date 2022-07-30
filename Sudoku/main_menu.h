#pragma once
#include <SFML/Graphics.hpp>
#define Max_main_menu 3

class main_menu
{

	//public functions of main menu class
public:

	main_menu(float width, float height);
	~main_menu();
	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
	int mainMenuPressed() { return mainMenuSelected; }

private:

	int mainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];

};

