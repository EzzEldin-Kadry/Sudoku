#include "main_menu.h"


main_menu::main_menu(float width, float height)
{
	if (!font.loadFromFile("Optimal Solutions.ttf")){}

	//play

	mainMenu[0].setFont(font);
	mainMenu[0].setColor(sf::Color::Red);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(60);
	mainMenu[0].setStyle(sf::Text::Bold);
	mainMenu[0].setPosition(sf::Vector2f(width / 2 - 90, height / (Max_main_menu + 1)));

	//solver

	mainMenu[1].setFont(font);
	mainMenu[1].setColor(sf::Color(255, 200, 100));
	mainMenu[1].setString("Solver");
	mainMenu[1].setCharacterSize(40);
	mainMenu[1].setStyle(sf::Text::Bold);
	mainMenu[1].setPosition(sf::Vector2f(width / 2 - 90, height / (Max_main_menu + 1) * 2));

	//exit

	mainMenu[2].setFont(font);
	mainMenu[2].setColor(sf::Color(255, 200, 100));
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(40);
	mainMenu[2].setStyle(sf::Text::Bold);
	mainMenu[2].setPosition(sf::Vector2f(width / 2 - 90, height / (Max_main_menu + 1) * 3));

	

	mainMenuSelected = 0;  //start from zero index (play)

}


main_menu::~main_menu()
{
}


//********************************Function of drawing main menu**********************************************


void main_menu::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		window.draw(mainMenu[i]);
	}
}


//********************************Function of moving up***************************************************


void main_menu::moveUp()
{
	if (mainMenuSelected - 1 >= -1) // check if not on the first item (play)

	{

		mainMenu[mainMenuSelected].setColor(sf::Color(255, 200, 100));  //change the pervious item's color
		mainMenu[mainMenuSelected].setCharacterSize(40);


		mainMenuSelected--;      //move to the upper item       
		if (mainMenuSelected == -1)
		{
			mainMenuSelected = 2;
		}
		mainMenu[mainMenuSelected].setColor(sf::Color::Red);      //change the new item's color
		mainMenu[mainMenuSelected].setCharacterSize(60);



	}
}


//********************************Function of moving down***************************************************


void main_menu::moveDown()
{
	if (mainMenuSelected + 1 <= Max_main_menu) //check if not on the last item (exit)

	{
		mainMenu[mainMenuSelected].setColor(sf::Color(255, 200, 100));  //change the pervious item's color
		mainMenu[mainMenuSelected].setCharacterSize(40);

		mainMenuSelected++;  //move to the lower item
		if (mainMenuSelected == 3)
		{
			mainMenuSelected = 0;
		}
		mainMenu[mainMenuSelected].setColor(sf::Color::Red);           //change the new item's color
		mainMenu[mainMenuSelected].setCharacterSize(60);

	}
}