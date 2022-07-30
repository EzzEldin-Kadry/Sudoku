#include "level_menu.h"


level_menu::level_menu(float width, float height)
{
	if (!font.loadFromFile("Optimal Solutions.ttf")){}

	//Easy

	levelMenu[0].setFont(font);
	levelMenu[0].setColor(sf::Color::Red);
	levelMenu[0].setStyle(sf::Text::Bold);
	levelMenu[0].setString("Easy");
	levelMenu[0].setCharacterSize(60);
	levelMenu[0].setPosition(sf::Vector2f(width / 2 - 110, height / (Max_level_menu + 1)));

	//Medium

	levelMenu[1].setFont(font);
	levelMenu[1].setColor(sf::Color(255, 200, 100));
	levelMenu[1].setString("Medium");
	levelMenu[1].setStyle(sf::Text::Bold);
	levelMenu[1].setCharacterSize(40);
	levelMenu[1].setPosition(sf::Vector2f(width / 2 - 110, height / (Max_level_menu + 1) * 2));

	//Hard

	levelMenu[2].setFont(font);
	levelMenu[2].setColor(sf::Color(255, 200, 100));
	levelMenu[2].setStyle(sf::Text::Bold);
	levelMenu[2].setString("Hard");
	levelMenu[2].setCharacterSize(sf::Text::Bold);
	levelMenu[2].setCharacterSize(40);
	levelMenu[2].setPosition(sf::Vector2f(width / 2 - 110, height / (Max_level_menu + 1) * 3));

	level_menu_selected = 0;      //start from zero index (Easy)

}


level_menu::~level_menu()
{
}


//********************************Function of drawing levels menu**********************************************


void level_menu::draw(sf::RenderWindow &window3)  //function of drawing levels menu

{
	for (int i = 0; i < 3; i++)
	{
		window3.draw(levelMenu[i]);
	}
}


//******************************Moving up function*************************************************


void level_menu::MoveUp()
{
	if (level_menu_selected - 1 >= -1)   // check if not on the first item (Easy)

	{
		levelMenu[level_menu_selected].setColor(sf::Color(255, 200, 100));   //change the pervious item's color
		levelMenu[level_menu_selected].setCharacterSize(40);


		level_menu_selected--;   //move to the upper item
		if (level_menu_selected == -1)
		{
			level_menu_selected = 2;
		}
		levelMenu[level_menu_selected].setColor(sf::Color::Red);             //change the new item's color
		levelMenu[level_menu_selected].setCharacterSize(60);

	}
}


//******************************Moving down function*************************************************


void level_menu::MoveDown()
{
	if (level_menu_selected + 1 <= Max_level_menu)      // check if not on the last item (Hard)

	{
		levelMenu[level_menu_selected].setColor(sf::Color(255, 200, 100));  //change the pervious item's color
		levelMenu[level_menu_selected].setCharacterSize(40);


		level_menu_selected++;  //Move to the lower item
		if (level_menu_selected == 3)
		{
			level_menu_selected = 0;
		}
		levelMenu[level_menu_selected].setColor(sf::Color::Red);            //change the new item's color
		levelMenu[level_menu_selected].setCharacterSize(60);

	}
}

