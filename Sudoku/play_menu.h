#pragma once
#include <SFML/Graphics.hpp>
#define max_play_menu 2

class play_menu
{
	//public fnctions of play menu class

public:
	play_menu(float width, float height);
	~play_menu();
	void draw(sf::RenderWindow &window2);
	void MoveUp();
	void MoveDown();
	int selected_index() { return play_menu_selected; }

private:
	int play_menu_selected;
	sf::Font font;
	sf::Text playMenu[max_play_menu];
};

