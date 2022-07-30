#pragma once
#include <SFML/Graphics.hpp>
#define Max_button 4

class sudoku_buttons
{
public:
	sudoku_buttons(float width, float height);
	~sudoku_buttons();
	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int selected_index() { return Button_menu_selected; }

private:
	int Button_menu_selected;
	sf::Font font;
	sf::Text sudokuButtons[Max_button];

};