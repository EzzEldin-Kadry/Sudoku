#include "sudoku_buttons.h"


sudoku_buttons::sudoku_buttons(float width, float height)
{
	if (!font.loadFromFile("BebasNeue.otf")) {}

	sudokuButtons[0].setFont(font);
	sudokuButtons[0].setColor(sf::Color::Red);
	sudokuButtons[0].setString("Check");
	sudokuButtons[0].setCharacterSize(60);
	sudokuButtons[0].setStyle(sf::Text::Bold);
	sudokuButtons[0].setPosition(627, 109);

	sudokuButtons[1].setFont(font);
	sudokuButtons[1].setColor(sf::Color(255, 200, 100));
	sudokuButtons[1].setString("Music");
	sudokuButtons[1].setCharacterSize(60);
	sudokuButtons[1].setStyle(sf::Text::Bold);
	sudokuButtons[1].setPosition(633, 196.5);

	sudokuButtons[2].setFont(font);
	sudokuButtons[2].setColor(sf::Color(255, 200, 100));
	sudokuButtons[2].setString("Pause");
	sudokuButtons[2].setCharacterSize(60);
	sudokuButtons[2].setStyle(sf::Text::Bold);
	sudokuButtons[2].setPosition(634, 274.5);

	sudokuButtons[3].setFont(font);
	sudokuButtons[3].setColor(sf::Color(255, 200, 100));
	sudokuButtons[3].setString("Save");
	sudokuButtons[3].setCharacterSize(60);
	sudokuButtons[3].setStyle(sf::Text::Bold);
	sudokuButtons[3].setPosition(634, 365);

	Button_menu_selected = 0;
}


sudoku_buttons::~sudoku_buttons()
{
}


void sudoku_buttons::draw(sf::RenderWindow & window)
{
	for (int i = 0; i < 4; i++)
	{
		window.draw(sudokuButtons[i]);
	}
}

void sudoku_buttons::MoveUp()
{
	if (Button_menu_selected - 1 >= -1) // check if not on the first item (New game)

	{

		sudokuButtons[Button_menu_selected].setColor(sf::Color(255, 200, 100));  //change the pervious item's color
		sudokuButtons[Button_menu_selected].setCharacterSize(40);

		Button_menu_selected--;    //move to the upper item 
		if (Button_menu_selected == -1)
		{
			Button_menu_selected = 3;
		}
		sudokuButtons[Button_menu_selected].setColor(sf::Color::Red);           //change the new item's color
		sudokuButtons[Button_menu_selected].setCharacterSize(60);
	}
}

void  sudoku_buttons::MoveDown()

{
	if (Button_menu_selected + 1 <= Max_button) // check if not on the last item (main menu)

	{
		sudokuButtons[Button_menu_selected].setColor(sf::Color(255, 200, 100));   //change the pervious item's color
		sudokuButtons[Button_menu_selected].setCharacterSize(40);


		Button_menu_selected++;      //move to the lower item
		if (Button_menu_selected == Max_button)
		{
			Button_menu_selected = 0;
		}
		sudokuButtons[Button_menu_selected].setColor(sf::Color::Red); //change the new item's color
		sudokuButtons[Button_menu_selected].setCharacterSize(60);
	}
}