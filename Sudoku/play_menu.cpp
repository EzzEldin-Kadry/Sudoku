#include "play_menu.h"


play_menu::play_menu(float width, float height)
{
	if (!font.loadFromFile("Optimal Solutions.ttf")){}

	//New game

	playMenu[0].setFont(font);
	playMenu[0].setColor(sf::Color::Red);
	playMenu[0].setString("New game");
	playMenu[0].setCharacterSize(60);
	playMenu[0].setStyle(sf::Text::Bold);
	playMenu[0].setPosition(sf::Vector2f(width / 2 - 110, height / (max_play_menu + 1)));

	//Load game

	playMenu[1].setFont(font);
	playMenu[1].setColor(sf::Color(255, 200, 100));
	playMenu[1].setString("Load game");
	playMenu[1].setCharacterSize(40);
	playMenu[1].setStyle(sf::Text::Bold);
	playMenu[1].setPosition(sf::Vector2f(width / 2 - 110, height / (max_play_menu + 1) * 2));

	//Main menu


	play_menu_selected = 0;  //start from zero index (New game)


}


play_menu::~play_menu()
{
}


//********************************Function of drawing play menu**********************************************



void play_menu::draw(sf::RenderWindow &window2)   //function of drawing play menu
{
	for (int i = 0; i < 2; i++)
	{
		window2.draw(playMenu[i]);
	}
}


//********************************Function of Moving up*******************************************************


void play_menu::MoveUp()
{
	if (play_menu_selected - 1 >= -1) // check if not on the first item (New game)

	{

		playMenu[play_menu_selected].setColor(sf::Color(255, 200, 100));  //change the pervious item's color
		playMenu[play_menu_selected].setCharacterSize(40);

		play_menu_selected--;    //move to the upper item 
		if (play_menu_selected == -1)
		{
			play_menu_selected = 1;
		}
		playMenu[play_menu_selected].setColor(sf::Color::Red);           //change the new item's color
		playMenu[play_menu_selected].setCharacterSize(60);
	}
}


//********************************Function of Moving down*******************************************************


void play_menu::MoveDown()
{
	if (play_menu_selected + 1 <= max_play_menu) // check if not on the last item (main menu)

	{
		playMenu[play_menu_selected].setColor(sf::Color(255, 200, 100));   //change the pervious item's color
		playMenu[play_menu_selected].setCharacterSize(40);


		play_menu_selected++;      //move to the lower item
		if (play_menu_selected == max_play_menu)
		{
			play_menu_selected = 0;
		}
		playMenu[play_menu_selected].setColor(sf::Color::Red); //change the new item's color
		playMenu[play_menu_selected].setCharacterSize(60);
	}
}
