#pragma once
#include <SFML\Graphics.hpp>
#define Max_level_menu 3

class level_menu
{
	//public functions of levels menu class

public:
	level_menu(float width, float height);
	~level_menu();
	void draw(sf::RenderWindow &window3);
	void MoveUp();
	void MoveDown();
	int selected_index() { return level_menu_selected; }

private:
	int level_menu_selected;
	sf::Font font;
	sf::Text levelMenu[Max_level_menu];
};

