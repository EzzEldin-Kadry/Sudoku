#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include<SFML/Audio.hpp>
#include <iostream>
#include "main_menu.h"
#include"play_menu.h"
#include"sudoku_buttons.h"
#include <SFML\Graphics.hpp>
#include <time.h>
#include <string>
#include <sstream>
#include "level_menu.h"
#include<ctime>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include<fstream>

using namespace std;
using namespace sf;
int play=0;
int staticArr[9][9] = { 0 };  
int arr[9][9];
int cinArr[9][9] = { 0 }; //To cin>>Numbers 
int randomArr[9][9] = { 0 };//To cout<<RAndom Numbers
bool goodnum[9][9] = { 0 };//To Check if the Index is Empty
bool flagRow[9][9] = { 0 };
bool flagColumn[9][9] = { 0 };
bool flagBlock[9][9] = { 0 };
int saveArr[9][9] = {0};
int solverArr[9][9] = { 0 };
int counterErrors = 0;
int screenNum ;
int level;
int countererrorArray[1] = { 0 };
int problemSudoku[9][9] = { 0 };
bool tagRow[9][9] = { 0 };
bool tagCol[9][9] = { 0 };
bool tagBlock[9][9] = { 0 };
int buttonGame ;

/////////////////////////////////////////////////Play menu function///////////////////////////////////////////////////////
void playMenuFn()
{
	sf::RenderWindow window2(sf::VideoMode(800, 585), "Sudoku V 1.00 ");  //decleration of play menu screen
	play_menu playMenu(window2.getSize().x, window2.getSize().y);        //decleration of play menu's texts

	sf::Texture sudoku_texture;
	if (!sudoku_texture.loadFromFile("Pictures/Sudoku.png")){}
	sf::Sprite sudoku_sprite;
	sudoku_sprite.setTexture(sudoku_texture);

	while (window2.isOpen())  //play menu's loop
	{

		sf::Event event2;

		while (window2.pollEvent(event2))
		{

			switch (event2.type)
			{

			case sf::Event::Closed:
				screenNum = 2;
				window2.close();
				break;
			case sf::Event::KeyReleased:

				switch (event2.key.code)

				{
				case sf::Keyboard::Up:       //move up
					playMenu.MoveUp();
					break;

				case sf::Keyboard::Down:      //move down
					playMenu.MoveDown();
					break;

				case sf::Keyboard::Escape:  
					screenNum = 0;
					window2.close();
					break;
				case sf::Keyboard::BackSpace:
					screenNum = 0;
					window2.close();
					break;

				case sf::Keyboard::Return:  //Enter pressed


					switch (playMenu.selected_index())  //whitch item selected
					{
					case 0:                //new game selected
						screenNum = 3;    //change the variable to 3
						window2.close();  //close play menu
						break;

					case 1:                //load game selected
						screenNum = 6;
						break;            //Nothing will happen

					case 2:              //main menu item selected

						screenNum = 0;   //change the variable back to 0
						window2.close(); //close play menu
						break;
					}
				}


			}

			if (screenNum != 1) break;    //if the variable != 1 , then close play menu's loop

		}


		if (screenNum != 1) break;        //if the variable != 1 , break from play menu's loop


		window2.clear();
		window2.draw(sudoku_sprite);
		playMenu.draw(window2);          //call thr function of drawing play menu
		window2.display();
	}
}

///////////////////////////////////////////////Level menu function////////////////////////////////////////////////////////

void levelMenuFn()
{
	sf::RenderWindow window3(sf::VideoMode(800, 580), ("Sudoku"));   //decleration of levels menu screen
	level_menu levelMenu(window3.getSize().x, window3.getSize().y);  //decleration of levels menu's texts

	sf::Font font;
	if (!font.loadFromFile("Fonts/arial.ttf")) {}

	sf::Texture sudoku_texture;
	if (!sudoku_texture.loadFromFile("Pictures/Sudoku.png")){}
	sf::Sprite sudoku_sprite;
	sudoku_sprite.setTexture(sudoku_texture);


	while (window3.isOpen()) //levels menu screen's loop
	{
		sf::Event event3;

		while (window3.pollEvent(event3))
		{
			switch (event3.type)
			{
			case sf::Event::Closed:
				screenNum = 2;
				window3.close();
				break;

			case sf::Event::KeyPressed:
				switch (event3.key.code)
				{
				case sf::Keyboard::Up:     //move up
					levelMenu.MoveUp();
					break;

				case sf::Keyboard::Down:      //move down
					levelMenu.MoveDown();
					break;

				case sf::Keyboard::BackSpace:  //if backspace pressed
					screenNum = 1;             //change the variable back to 1
					window3.close();           //close levels menu
					break;

				case sf::Keyboard::Escape:  //if backspace pressed
					screenNum = 1;             //change the variable back to 1
					window3.close();           //close levels menu
					break;

				case sf::Keyboard::Return:  // Enter pressed
					switch (levelMenu.selected_index())  //which item selected
					{
					case 0:        //easy selected
						screenNum = 4;
						level = 41;
						break;

					case 1:        //medium selected
						screenNum = 4;
						level = 27;
						break;     

					case 2:   //hard selected
						screenNum = 4;
						level = 11;
						break;   

					}
				}
			}

		if (screenNum != 3) break;     //if the variable != 3 , break from levels menu's loop

		}

		if (screenNum != 3) break;      //if the variable != 3 , break from levels menu's loop

		window3.clear();
		window3.draw(sudoku_sprite);
		levelMenu.draw(window3);       //call the function of drawing levels menu
		window3.display();
	}
}
////////////////////////////////////////////////Put Flags on the Random Numbers ///////////////////////////////////////////


////////////////////////////////////////////////////////////functions of solver//////////////////////////////////////////////////////
void assignTag(int i, int j, int num)
{
	if (num == 0)
		return;
	num--;
	tagRow[i][num] = 1;
	tagCol[num][j] = 1;
	tagBlock[(i / 3) * 3 + j / 3][num] = 1;
}

void fillTags()
{
	for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
		assignTag(i, j, problemSudoku[i][j]);
}

bool checkValid(int i, int j, int num)
{
	num--;
	if (tagRow[i][num] == 1)
		return 0;
	if (tagCol[num][j] == 1)
		return 0;
	if (tagBlock[(i / 3) * 3 + j / 3][num] == 1)
		return 0;
	return 1;
}

void resetTag(int i, int j, int num)
{
	if (num == 0)
		return;
	num--;
	tagRow[i][num] = 0;
	tagCol[num][j] = 0;
	tagBlock[(i / 3) * 3 + j / 3][num] = 0;
}

bool solveBacktrack(int i, int j, int proMat[9][9])
{
	if (j == 9) // This function goes checking row after row.
	{
		j = 0;
		if (++i == 9)   // Once a row is finished, go to next row.
			return 1; // If final cell is reached, puzzle is solved.
	}
	if (proMat[i][j] > 0)  // Skip filled cells
		return solveBacktrack(i , j+1, proMat); // Check next row of current column.

	for (int val = 1; val <= 9; val++) // Empty cell found. Check from 1 to 9.
	{
		if (checkValid(i, j, val)) 
		{
			proMat[i][j] = val;
			assignTag(i, j, val); // Also set the tags for checking next value.
			if (solveBacktrack(i , j+1, proMat)) // And call the solve function again.
				return 1; // If it returns true that means the puzzle is solved.
			else // If not then we need to reset the tags and backtrack.
				resetTag(i, j, proMat[i][j]);
		}
	}
	resetTag(i, j, proMat[i][j]); // Reset tags and backtrack.
	proMat[i][j] = 0; // Also reset the value for next iteration.
	return 0;
}
bool solvePuzzle()
{
	//solveLogical();
	return solveBacktrack(0, 0, problemSudoku);
}
void printPuzzle()
{
	sf::RenderWindow windowSolver(sf::VideoMode(585, 585), "			      						   We will Solve", sf::Style::Close);
	sf::Font font, fontError;
	if (!font.loadFromFile("ShineBright-Demo.ttf"))
		cout << "Not found";

	if (!font.loadFromFile("BebasNeue.otf"))
		cout << "Not found";


	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(45);
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			/*if (randomArr[i][j]>0 && randomArr[i][j] == cinArr[i][j]){
			text.setColor(sf::Color::Red);
			text.setCharacterSize(80);
			text.setString("Try  by yourself");
			text.setPosition(100, 250);
			windowgrid.draw(text);*/

			if (problemSudoku[i][j] == 1){
				text.setString("1");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 2){
				text.setString("2");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 3){
				text.setString("3");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 4){

				text.setString("4");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);

			}
			else if (problemSudoku[i][j] == 5){

				text.setString("5");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 6){

				text.setString("6");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 7){

				text.setString("7");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 8){

				text.setString("8");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
			else if (problemSudoku[i][j] == 9){

				text.setString("9");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowSolver.draw(text);
			}
		}
	}
}
void printMessageErrorOfSolver()
{
	sf::RenderWindow windowSolverError(sf::VideoMode(400, 400), "			      								   Message Error", sf::Style::Close);
	sf::Font font, fontError;
	if (!font.loadFromFile("ShineBright-Demo.ttf"))
		cout << "Not found";

	if (!font.loadFromFile("BebasNeue.otf"))
		cout << "Not found";


	sf::Text text;
	text.setFont(font);

	while (windowSolverError.isOpen())
	{
		sf::Event event;
		while (windowSolverError.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				screenNum = 0;
				windowSolverError.close();
				break;
			}

			text.setColor(sf::Color(130, 70, 5));
			text.setString("This Sodoku can't be solved ^_^ ");
			text.setCharacterSize(85);
			text.setStyle(sf::Text::Bold);
			text.setPosition(30, 190);
		}
		windowSolverError.draw(text);
		windowSolverError.display();
	}
}
//////////////////////////////////////////////////Checker////////////////////////////////////////
bool checkerForSolver(int sOdUkO[9][9])
{
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (sOdUkO[i][j] != 0)
			{
				int num = sOdUkO[i][j]-1;
				if (flagRow[i][num] == 1)
					return false;
				if (flagColumn[num][j] == 1)
					return false;
				if (flagBlock[(i / 3) * 3 + j / 3][num] == 1)
					return false;

				flagRow[i][num] = 1;
				flagColumn[num][j] = 1;
				flagBlock[(i / 3) * 3 + j / 3][num] = 1;
			}
		}
	}
}
void SudokuSolver(int inputSudoku[9][9])
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			if (inputSudoku[i][j] < 1 || inputSudoku[i][j] > 9)
				continue;
			else
				problemSudoku[i][j] = inputSudoku[i][j];
		}
	fillTags();
	
	if (checkerForSolver(problemSudoku))
	{
		if (solvePuzzle())
		{
			printPuzzle();
		}
	
		else
		{
			cout << "error";
			printMessageErrorOfSolver();
		}
	}
	else
	{
		printMessageErrorOfSolver();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 void flagsForOrignalNumbers(){
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (randomArr[i][j] != 0){
				int num = randomArr[i][j] - 1;
				flagRow[i][num] = 1;
				flagColumn[num][j] = 1;
				flagBlock[(i / 3) * 3 + j / 3][num] = 1;
			}
		}
	}
}

bool  checkingNumsFromUser(int num, int i, int j){

	if (cinArr[i][j] != 0){
		int num = cinArr[i][j] - 1;
		if (flagRow[i][num] == 1)
			return 0;
		if (flagColumn[num][j] == 1)
			return 0;
		if (flagBlock[(i / 3) * 3 + j / 3][num] == 1)
			return 0;

		return 1;
	}
}


/////////////////////////////////////////////choose The Name Of Raandom Sodoku //////////////////////////////////////////
int randNameSudoku() //rand sudoku number
{
	srand(time(0));
	int randy = rand() % (10 - 1 + 1) + 1;
	cout << randy << endl;
	return randy;
}



//////////////////////////////////////////////Put The indexes Of Name Sodoku in using sudoko///////////////////////////////////////////
void randomSodoku(int usingSudoku[][9])
{
	int sudoku = randNameSudoku();

	int s1[9][9] = { { 9, 5, 6, 8, 7, 2, 3, 1, 4 },
					{ 2, 8, 1, 5, 3, 4, 7, 9, 6 },
					{ 7, 4, 3, 1, 9, 6, 5, 2, 8 },
					{ 5, 1, 4, 7, 8, 9, 2, 6, 3 },
					{ 8, 9, 2, 3, 6, 1, 4, 5, 7 },
					{ 3, 6, 7, 2, 4, 5, 9, 8, 1 },
					{ 4, 3, 5, 9, 1, 8, 6, 7, 2 },
					{ 1, 7, 9, 6, 2, 3, 8, 4, 5 },
					{ 6, 2, 8, 4, 5, 7, 1, 3, 9 } };
	int s2[9][9] = { { 5, 9, 1, 7, 4, 3, 6, 2, 8 },
					{ 8, 3, 7, 2, 5, 6, 4, 1, 9 },
					{ 4, 2, 6, 8, 9, 1, 3, 5, 7 },
					{ 7, 4, 2, 9, 1, 8, 5, 3, 6 },
					{ 1, 6, 5, 3, 7, 4, 8, 9, 2 },
					{ 9, 8, 3, 5, 6, 2, 1, 7, 4 },
					{ 6, 7, 9, 1, 8, 5, 2, 4, 3 },
					{ 3, 5, 4, 6, 2, 9, 7, 8, 1 },
					{ 2, 1, 8, 4, 3, 7, 9, 6, 5 } };

	int s3[9][9] = { { 7, 5, 9, 2, 8, 3, 6, 4, 1 },
					{ 4, 2, 1, 5, 7, 6, 8, 9, 3 },
					{ 8, 6, 3, 9, 1, 4, 5, 7, 2 },
					{ 1, 8, 7, 3, 5, 9, 2, 6, 4 },
					{ 5, 3, 4, 7, 6, 2, 1, 8, 9 },
					{ 6, 9, 2, 1, 4, 8, 3, 5, 7 },
					{ 9, 4, 8, 6, 2, 1, 7, 3, 5 },
					{ 2, 7, 6, 4, 3, 5, 9, 1, 8 },
					{ 3, 1, 5, 8, 9, 7, 4, 2, 6 } };
	int s4[9][9] = { { 6, 5, 2, 7, 4, 1, 9, 3, 8 },
					{ 7, 3, 1, 2, 9, 8, 4, 6, 5 },
					{ 8, 4, 9, 6, 3, 5, 7, 2, 1 },
					{ 5, 9, 6, 4, 7, 2, 1, 8, 3 },
					{ 4, 1, 3, 8, 5, 6, 2, 9, 7 },
					{ 2, 7, 8, 9, 1, 3, 5, 4, 6 },
					{ 1, 2, 7, 3, 6, 9, 8, 5, 4 },
					{ 9, 6, 5, 1, 8, 4, 3, 7, 2 },
					{ 3, 8, 4, 5, 2, 7, 6, 1, 9 } };
	int s5[9][9] = { { 7, 3, 6, 8, 1, 5, 4, 2, 9 },
					{ 5, 1, 9, 3, 4, 2, 7, 8, 6 },
					{ 2, 4, 8, 6, 7, 9, 5, 1, 3 },
					{ 1, 2, 3, 4, 5, 7, 9, 6, 8 },
					{ 4, 6, 7, 9, 2, 8, 1, 3, 5 },
					{ 9, 8, 5, 1, 6, 3, 2, 7, 4 },
					{ 6, 5, 4, 2, 3, 1, 8, 9, 7 },
					{ 3, 9, 1, 7, 8, 4, 6, 5, 2 },
					{ 8, 7, 2, 5, 9, 6, 3, 4, 1 } };

	int s6[9][9] = { { 9, 5, 6, 8, 7, 2, 3, 1, 4 }, { 2, 8, 1, 5, 3, 4, 7, 9, 6 }, { 7, 4, 3, 1, 9, 6, 5, 2, 8 }, { 5, 1, 4, 7, 8, 9, 2, 6, 3 }, { 8, 9, 2, 3, 6, 1, 4, 5, 7 }, { 3, 6, 7, 2, 4, 5, 9, 8, 1 }, { 4, 3, 5, 9, 1, 8, 6, 7, 2 }, { 1, 7, 9, 6, 2, 3, 8, 4, 5 }, { 6, 2, 8, 4, 5, 7, 1, 3, 9 } };
	int s7[9][9] = { { 5, 9, 1, 7, 4, 3, 6, 2, 8 }, { 8, 3, 7, 2, 5, 6, 4, 1, 9 }, { 4, 2, 6, 8, 9, 1, 3, 5, 7 }, { 7, 4, 2, 9, 1, 8, 5, 3, 6 }, { 1, 6, 5, 3, 7, 4, 8, 9, 2 }, { 9, 8, 3, 5, 6, 2, 1, 7, 4 }, { 6, 7, 9, 1, 8, 5, 2, 4, 3 }, { 3, 5, 4, 6, 2, 9, 7, 8, 1 }, { 2, 1, 8, 4, 3, 7, 9, 6, 5 } };
	int s8[9][9] = { { 7, 5, 9, 2, 8, 3, 6, 4, 1 }, { 4, 2, 1, 5, 7, 6, 8, 9, 3 }, { 8, 6, 3, 9, 1, 4, 5, 7, 2 }, { 1, 8, 7, 3, 5, 9, 2, 6, 4 }, { 5, 3, 4, 7, 6, 2, 1, 8, 9 }, { 6, 9, 2, 1, 4, 8, 3, 5, 7 }, { 9, 4, 8, 6, 2, 1, 7, 3, 5 }, { 2, 7, 6, 4, 3, 5, 9, 1, 8 }, { 3, 1, 5, 8, 9, 7, 4, 2, 6 } };
	int s9[9][9] = { { 6, 5, 2, 7, 4, 1, 9, 3, 8 }, { 7, 3, 1, 2, 9, 8, 4, 6, 5 }, { 8, 4, 9, 6, 3, 5, 7, 2, 1 }, { 5, 9, 6, 4, 7, 2, 1, 8, 3 }, { 4, 1, 3, 8, 5, 6, 2, 9, 7 }, { 2, 7, 8, 9, 1, 3, 5, 4, 6 }, { 1, 2, 7, 3, 6, 9, 8, 5, 4 }, { 9, 6, 5, 1, 8, 4, 3, 7, 2 }, { 3, 8, 4, 5, 2, 7, 6, 1, 9 } };
	int s10[9][9] = { { 7, 3, 6, 8, 1, 5, 4, 2, 9 }, { 5, 1, 9, 3, 4, 2, 7, 8, 6 }, { 2, 4, 8, 6, 7, 9, 5, 1, 3 }, { 1, 2, 3, 4, 5, 7, 9, 6, 8 }, { 4, 6, 7, 9, 2, 8, 1, 3, 5 }, { 9, 8, 5, 1, 6, 3, 2, 7, 4 }, { 6, 5, 4, 2, 3, 1, 8, 9, 7 }, { 3, 9, 1, 7, 8, 4, 6, 5, 2 }, { 8, 7, 2, 5, 9, 6, 3, 4, 1 } };


	if (sudoku == 1)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s1[i][j];
			}
		}
	}//end if
	//2
	if (sudoku == 2)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s2[i][j];
			}
		}
	}//end if
	//3
	if (sudoku == 3)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s3[i][j];
			}
		}
	}//end if
	//4
	if (sudoku == 4)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s4[i][j];
			}
		}
	}//end if
	//5
	if (sudoku == 5)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s5[i][j];
			}
		}
	}//end if
	//6
	if (sudoku == 6)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s6[i][j];
			}
		}
	}//end if

	//7
	if (sudoku == 7)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s7[i][j];
			}
		}
	}//end if

	//8
	if (sudoku == 8)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s8[i][j];
			}
		}
	}//end if

	//9
	if (sudoku == 9)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s9[i][j];
			}
		}
	}//end if

	//10
	if (sudoku == 10)
	{
		for (int i = 0; i<9; i++)
		{
			for (int j = 0; j<9; j++)
			{
				usingSudoku[i][j] = s10[i][j];
			}
		}
	}//end if


}


//////////////////////////////////////////////////Assign RandomArray////////////////////////////////////////////////////
void AssignRandomArr()
{
	int rand_x=0, rand_y=0;
	int counter = 0;
		int a, b;
	for (int i = 0, j = 0; counter < level;)
	{
		rand_x = rand() % 9;
		rand_y = rand() % 9;
		i = rand_x;
		j = rand_y;
		if (goodnum[i][j] == 0)
		{
			randomArr[i][j] = arr[i][j];
			counter++;
			goodnum[i][j] = 1;
		}
	}
	//cout << counter;
		/*for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++)*/

		cout << endl;
	
}



///////////////////////////////To  display random Numbers ////////////////////////////////
void displayRandomNumbers(Text &text, RenderWindow& windowgrid){
	text.setColor(sf::Color::Black);
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (randomArr[i][j] == 1){
				staticArr[i][j] = 1;
				text.setString("1");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);
			}

			else if (randomArr[i][j] == 2){
				staticArr[i][j] = 2;
				text.setString("2");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);
			}
			else if (randomArr[i][j] == 3){
				staticArr[i][j] = 3;
				text.setString("3");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);

			}
			else if (randomArr[i][j] == 4){
				staticArr[i][j] = 4;
				text.setString("4");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);

			}
			else if (randomArr[i][j] == 5){
				staticArr[i][j] = 5;
				text.setString("5");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);

			}
			else if (randomArr[i][j] == 6){
				staticArr[i][j] = 6;
				text.setString("6");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);
			}
			else if (randomArr[i][j] == 7){
				staticArr[i][j] = 7;

				text.setString("7");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);

			}
			else if (randomArr[i][j] == 8){
				staticArr[i][j] = 8;
				text.setString("8");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);

			}
			else if (randomArr[i][j] == 9){
				staticArr[i][j] = 9;
				text.setString("9");
				text.setPosition(65 * j + 30, 65 * i + 1);
				windowgrid.draw(text);

			}
		}
	}
}


//////////////////////////////////////////Cin>>Number////////////////////////////////////////////////////////////
void cinNumber(Text &text, RenderWindow &windowgrid){
	int x, y;
	bool flagOfActive = 0;
	if (sf::Event::MouseButtonPressed){
		x = sf::Mouse::getPosition(windowgrid).x / 65;
		y = sf::Mouse::getPosition(windowgrid).y / 65;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
			cinArr[y][x] = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
			cinArr[y][x] = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
			cinArr[y][x] = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
			cinArr[y][x] = 4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
			cinArr[y][x] = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
			cinArr[y][x] = 6;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
			cinArr[y][x] = 7;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
			cinArr[y][x] = 8;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
			cinArr[y][x] = 9;
		}
	}
	//////////////////////////////////////////////////////////Display_Cin>>Numbers///////////////////////////////////////////////////////
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (randomArr[i][j] == 0){
				if (checkingNumsFromUser(cinArr[i][j], i, j) == 0){
					text.setColor(sf::Color::Red);
					if (cinArr[i][j] == 1){
						text.setString("1");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 2){
						text.setString("2");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 3){
						text.setString("3");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 4){

						text.setString("4");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);

					}
					else if (cinArr[i][j] == 5){

						text.setString("5");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 6){

						text.setString("6");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 7){

						text.setString("7");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 8){

						text.setString("8");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 9){

						text.setString("9");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
				}
				else if (checkingNumsFromUser(cinArr[i][j], i, j) == 1){
					text.setColor(sf::Color::Black);
					//flagsForCi3n_n3umbers(cinArr[i][j], i, j);

					if (cinArr[i][j] == 1){
						text.setString("1");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 2){
						text.setString("2");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 3){
						text.setString("3");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 4){

						text.setString("4");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);

					}
					else if (cinArr[i][j] == 5){

						text.setString("5");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 6){

						text.setString("6");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 7){

						text.setString("7");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 8){

						text.setString("8");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
					else if (cinArr[i][j] == 9){

						text.setString("9");
						text.setPosition(65 * j + 30, 65 * i + 1);
						windowgrid.draw(text);
					}
				}
			}
		}
	}
}


//////////////////////////////////////////////////
int checkSudokuWhenPressCheck(){
	int finCheck;
	bool error = 0;
	bool rowFlag[9][9] = {0};
	bool colFlag[9][9]={0};
	bool BlockFlag[9][9] = { 0 };
	int testArr[9][9] = { 0 };

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (randomArr[i][j] != 0){
				int num = randomArr[i][j] - 1;
				rowFlag[i][num] = 1;
				colFlag[num][j] = 1;
				BlockFlag[(i / 3) * 3 + j / 3][num] = 1;
			}
		}
	}
	for (int i = 0; i < 9; i ++ ){
		for (int j = 0; j < 9; j++){
			if (cinArr[i][j] != 0){
				int num = cinArr[i][j]-1;
				bool numIsRight = 1;
				if (rowFlag[i][num] == 1)
			        {
						numIsRight = 0;
						error = 1;
				    }
				if (colFlag[num][j] == 1)
					{
						numIsRight = 0;
						error = 1;
					}
				if (BlockFlag[(i / 3) * 3 + j / 3][num] == 1)
					{
						numIsRight = 0;
						error = 1;
					}
				//cout << error;
				if (numIsRight == 1){
					rowFlag[i][num] = 1;
					colFlag[num][j] = 1;
					BlockFlag[(i / 3) * 3 + j / 3][num] = 1;
				}
			}
		}
	}
	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
			if (rowFlag[i][j] == 1 && flagRow[i][j] == 0)
				flagRow[i][j] = rowFlag[i][j];			
			if (colFlag[i][j] == 1 && flagColumn[i][j] == 0)
				flagColumn[i][j] = colFlag[i][j];
			if (BlockFlag[i][j] == 1 && flagBlock[i][j] == 0)
				flagBlock[i][j] = BlockFlag[i][j];
		}
	}
	int count = 0;

	if (error == 1){
		finCheck = 1;
	}

	else {
		for (int i = 0; i < 9; i++){
			for (int j = 0; j < 9; j++){
				if (cinArr[i][j]>0)
					count++;
				}
			}
		if (count==81-level)
			finCheck = 0;
		else
			finCheck = 2;


	}
	return finCheck;
}

//////////////////////////////////////////when click check////////////////////////////////////////////////////////////
void   checkIfTheSudokoIsRight(Font font,Text &text, RenderWindow &windowgrid){

	int sOdUkO[9][9] = { 0 };
	int output;
	output = checkSudokuWhenPressCheck();
	cout << output;
	if (output != 1){
		if (output == 0){
			sf::RenderWindow windowTrue(sf::VideoMode(400, 400), "                   Congratulstion", sf::Style::Close);
			while (windowTrue.isOpen())
			{
				sf::Event event;
				while (windowTrue.pollEvent(event))
				{
					switch (event.type)
					{
					case sf::Event::Closed:
						screenNum = 4;
						windowTrue.close();
						break;
					}
					text.setCharacterSize(85);
					text.setFont(font);
					text.setColor(sf::Color(255, 200, 100));
					text.setString("Congratulation");
					text.setStyle(sf::Text::Bold);
					text.setPosition(30, 130);

					windowTrue.draw(text);
					windowTrue.display();
				}
			}
		}
		else if (output==2)
			cout << "right";
	}
		else{
			cout << "\a";
			counterErrors++;
			countererrorArray[0] = counterErrors;
			cout << endl << counterErrors << endl;
			
		}
	}

void drawCounterError(RenderWindow &windowgrid, Text &text, Font &font){
	for (int i = 0; i < 1; i++){

		if (countererrorArray[i] == 1){
			text.setString("1");
			text.setColor(sf::Color::Black);
			text.setPosition(775, 450);
			windowgrid.draw(text);
		}
		else if (countererrorArray[i] == 2){
			text.setString("2");
			text.setColor(sf::Color::Black);
			text.setPosition(775, 450);
			windowgrid.draw(text);
		}
		else if (countererrorArray[i] == 3){
			text.setString("3");
			text.setColor(sf::Color::Black);
			text.setPosition(775, 450);
			windowgrid.draw(text);
		}
	}
}


/////////////////////////////////////Drawing WindowPause in side game////////////////////////////////////////////
void WindowPause(RenderWindow &windowgrid, Font font) {
	
	sf::RenderWindow windowPaaause(sf::VideoMode(400, 400), "Pause", sf::Style::Close);
	while (windowPaaause.isOpen())
	{
		sf::Event event;
		while (windowPaaause.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				screenNum = 2;
				windowPaaause.close();
				break;
			}
		}
	}
}


/////////////////////////////////////Drawing Window Save in side game////////////////////////////////////////////
 void windowSave(int &x,int &y,int &z){

	ofstream out ("saved sudoku.txt"); //saving array
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
	out << randomArr[i][j]<< " ";
	out << cinArr[i][j]<<" ";
		} //end for j
		cout << endl;
	} //end for i
	out.close();

	ofstream out2("Timer&checker.txt"); //save error counter then x,y,z
	out2  << " " << x << " " << y << " " << z;
	out2.close();
}


 /////////////////////////////////////////Drawing Button in the side of the grid window///////////////////////////////////
 void drawintButtonsInSides(RenderWindow &windowgrid, Font font, Font &fontError) {
	 sf::Text errors;

	 errors.setFont(font);
	 errors.setColor(sf::Color::Black);
	 errors.setString("Errors :");
	 errors.setCharacterSize(50);
	 errors.setStyle(sf::Text::Bold);
	 errors.setPosition(610, 445);
	 windowgrid.draw(errors);
 }


 //////////////////////////////////////////////Draw Grid////////////////////////////////////////////////////////
 void drawingGridOfSudoko(RenderWindow &windowgrid){

	 ////////////////////////////////////////////////////////////Set Gound///////////////////////////////////////////////////////
	 sf::Texture texture;
	 if (!texture.loadFromFile("groundPhotoShop.png"))
		 std::cout << "load failed" << std::endl;

	 sf::Sprite sprite;
	 sprite.setTexture(texture);

	 ////////////////////////////////////////////////////////Set Ground Of Ground/////////////////////////////////////////////////////////
	 sf::Texture Ground;
	 if (!Ground.loadFromFile("groundOfGroundPhotoShop.png"))
		 std::cout << "Not Found" << std::endl;

	 sf::Sprite	spriteOfGroundOfGround;
	 spriteOfGroundOfGround.setTexture(Ground);

	 //////////////////////////////////////////////Draw Grid////////////////////////////////////////////////////////
	 sf::Font font, fontError;
	 if (!font.loadFromFile("ShineBright-Demo.ttf"))
		 cout << "Not found";

	 if (!font.loadFromFile("BebasNeue.otf"))
		 cout << "Not found";

	 sf::RectangleShape rectangle(sf::Vector2f(5, 600));
	 rectangle.setFillColor(sf::Color(0, 0, 0));
	 rectangle.setPosition(sf::Vector2f(65, 0));

	 sf::RectangleShape rectangle2(sf::Vector2f(5, 600));
	 rectangle2.setFillColor(sf::Color(0, 0, 0));
	 rectangle2.setPosition(sf::Vector2f(130, 0));

	 sf::RectangleShape rectangle3(sf::Vector2f(5, 600));
	 rectangle3.setFillColor(sf::Color(0, 0, 0));
	 rectangle3.setPosition(sf::Vector2f(260, 0));

	 sf::RectangleShape rectangle4(sf::Vector2f(5, 600));
	 rectangle4.setFillColor(sf::Color(0, 0, 0));
	 rectangle4.setPosition(sf::Vector2f(325, 0));

	 sf::RectangleShape rectangle5(sf::Vector2f(5, 600));
	 rectangle5.setFillColor(sf::Color(0, 0, 0));
	 rectangle5.setPosition(sf::Vector2f(455, 0));

	 sf::RectangleShape rectangle6(sf::Vector2f(5, 600));
	 rectangle6.setFillColor(sf::Color(0, 0, 0));
	 rectangle6.setPosition(sf::Vector2f(520, 0));

	 //Horizontal lines 

	 sf::RectangleShape rectangle_(sf::Vector2f(585, 5));
	 rectangle_.setFillColor(sf::Color(0, 0, 0));
	 rectangle_.setPosition(sf::Vector2f(0, 65));
	 sf::RectangleShape rectangle_2(sf::Vector2f(585, 5));
	 rectangle_2.setFillColor(sf::Color(0, 0, 0));
	 rectangle_2.setPosition(sf::Vector2f(0, 130));
	 sf::RectangleShape rectangle_3(sf::Vector2f(585, 5));
	 rectangle_3.setFillColor(sf::Color(0, 0, 0));
	 rectangle_3.setPosition(sf::Vector2f(0, 260));
	 sf::RectangleShape rectangle_4(sf::Vector2f(585, 5));
	 rectangle_4.setFillColor(sf::Color(0, 0, 0));
	 rectangle_4.setPosition(sf::Vector2f(0, 325));
	 sf::RectangleShape rectangle_5(sf::Vector2f(585, 5));
	 rectangle_5.setFillColor(sf::Color(0, 0, 0));
	 rectangle_5.setPosition(sf::Vector2f(0, 455));
	 sf::RectangleShape rectangle_6(sf::Vector2f(585, 5));
	 rectangle_6.setFillColor(sf::Color(0, 0, 0));
	 rectangle_6.setPosition(sf::Vector2f(0, 520));
	 ///////////////////////////////////End grid///////////////////////////////////////////////////////////////
	 ////////////////////////////////&&&&&&&&DRAW&&&&&&&&//////////////////////////

	 windowgrid.draw(spriteOfGroundOfGround);
	 windowgrid.draw(sprite);
	 windowgrid.draw(rectangle);
	 windowgrid.draw(rectangle2);
	 windowgrid.draw(rectangle3);
	 windowgrid.draw(rectangle4);
	 windowgrid.draw(rectangle5);
	 windowgrid.draw(rectangle6);
	 windowgrid.draw(rectangle_);
	 windowgrid.draw(rectangle_2);
	 windowgrid.draw(rectangle_3);
	 windowgrid.draw(rectangle_4);
	 windowgrid.draw(rectangle_5);
	 windowgrid.draw(rectangle_6);
	 drawintButtonsInSides(windowgrid, font, fontError);

 }


 void loadSavedArray(int &x,int &y,int &z)
 {
	 ifstream in("saved sudoku.txt"); //load from file
	 for (int i = 0; i<9; i++)
	 {
		 for (int j = 0; j<9; j++)
		 {
			 in >> randomArr[i][j];
			 in >> cinArr[i][j];
		 }
		 cout << endl;
	 }
	 in.close();

	 ifstream in2("Timer&checker.txt"); //save error counter then x,y,z
	 in2  >> x>>y>>z;
	 in2.close();

 }

void screenSixload(){
		sf::RenderWindow windowload(sf::VideoMode(800, 585), "                                                             Saved Game", sf::Style::Close);
		sudoku_buttons sudokuButtons(windowload.getSize().x, windowload.getSize().y);
		//// load array from a file its name is "saved sudoku.txt"
		int a, b, c;
		loadSavedArray(a,b,c);
		cout << a << " " << b << " " << c<<endl;

		int x=a, y = b, z = c, check;
		cout << x << " " << y << " " << z;

	sf::Time seconds = sf::seconds(x);
	sf::Clock clock;

		sf::Music music;


	flagsForOrignalNumbers();
	sf::Font font, fontError;
	if (!font.loadFromFile("ShineBright-Demo.ttf"))
		cout << "Not found";

	if (!font.loadFromFile("BebasNeue.otf"))
		cout << "Not found";

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(45);

	sf::Text textSeconds;
	textSeconds.setFont(font);
	textSeconds.setPosition(720, 550);

	sf::Text textMinutes;
	textMinutes.setFont(font);
	textMinutes.setPosition(680, 550);

	sf::Text textMinutes2;
	textMinutes2.setFont(font);
	textMinutes2.setPosition(660, 550);


	sf::Text textTwoPoints;
	textTwoPoints.setFont(font);
	textTwoPoints.setString(":");
	textTwoPoints.setPosition(700, 550);
	bool TRUE=1;
	while (windowload.isOpen())
	{
		sf::Time elepased = clock.getElapsedTime();
		if(TRUE==0)
			x = elepased.asSeconds();
		if(TRUE==1)
		{
			x = a+elepased.asSeconds();
		}
		std::stringstream ssSeconds;
		ssSeconds << x;
		textSeconds.setString(ssSeconds.str().c_str());


		std::stringstream ssMinutes;
		ssMinutes << y;
		textMinutes.setString(ssMinutes.str().c_str());

		std::stringstream ssMinutes2;
		ssMinutes2 << z;
		textMinutes2.setString(ssMinutes2.str().c_str());

		if (x == 60) { clock.restart(); y++; x = 9; TRUE=0;}
		if (x == 60 && y == 9) { clock.restart(); z++; y = 0; }

		sf::Event event;
		while (windowload.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				screenNum = 2;
				windowload.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					sudokuButtons.MoveUp();
					break;

				case sf::Keyboard::Down:
					sudokuButtons.MoveDown();
					break;

				case sf::Keyboard::Return:  // Enter pressed
					switch (sudokuButtons.selected_index())
					{
					case 0: //go to function check
						if (sf::Keyboard::A)
							cout << "a";
						checkIfTheSudokoIsRight(font, text, windowload);
						break;
					case 1: //go to file of music
						if (sf::Keyboard::B)
						if (sf::Keyboard::Return)
							play++;
						if (play == 1){
							music.openFromFile("LastTouchOfAudio/EDM.ogg");
							music.play();
						}
						else if (play == 2){
							music.openFromFile("LastTouchOfAudio/Hip-Hop&Alternative.ogg");
							music.play();
						}
						else if (play == 3){
							play = 0;
							music.openFromFile("LastTouchOfAudio/Piano&Jazz.ogg");
							music.play();
						}
						break;
					case 2://draw window of pause
						if (sf::Keyboard::D)
							WindowPause(windowload, font);
						break;
					case 3:// go to function save 
						if (sf::Keyboard::C)
							windowSave(x, y, z);
						break;

					}
				}
			}
		//if (screenNum != 4) break;     //if the variable != 3 , break from levels menu's loop
	}
		drawingGridOfSudoko(windowload);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				text.setColor(sf::Color::Black);

				if (randomArr[i][j] == 1)
				{
					text.setString("1");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);
				}

				else if (randomArr[i][j] == 2)
				{
					text.setString("2");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);
				}
				else if (randomArr[i][j] == 3)
				{
					text.setString("3");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);

				}
				else if (randomArr[i][j] == 4)
				{
					text.setString("4");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);

				}
				else if (randomArr[i][j] == 5)
				{
					text.setString("5");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);

				}
				else if (randomArr[i][j] == 6)
				{
					text.setString("6");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);
				}
				else if (randomArr[i][j] == 7)
				{
					text.setString("7");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);

				}
				else if (randomArr[i][j] == 8)
				{
					text.setString("8");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);

				}
				else if (randomArr[i][j] == 9)
				{
					text.setString("9");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowload.draw(text);
				}
			}
		}
			cinNumber(text, windowload);


		/*	int x, y, z;
			int postion_x, position_y;
			if (event.key.code == sf::Mouse::Left){
				postion_x = sf::Mouse::getPosition(windowload).x;
				position_y = sf::Mouse::getPosition(windowload).y;
				if (postion_x > 635 && postion_x<730 && position_y>130 && position_y < 160){
					checkIfTheSudokoIsRight(windowload, font, text);
					cout << position_y << "   " << postion_x << endl;
				}
				else if (postion_x > 640 && postion_x<720 && position_y>390 && position_y < 431){
					windowSave(windowload, font, x, y, z);
				}
				else if (postion_x > 635 && postion_x<735 && position_y>215 && position_y < 255){
					windowMusic(windowload, font);
				}
				else if (postion_x > 631 && postion_x<725 && position_y>310 && position_y < 350){
					WindowPause(windowload, font);
				}
			}*/
			drawCounterError(windowload, text, font);


			windowload.draw(text);
			sudokuButtons.draw(windowload);
			windowload.draw(textSeconds);
			windowload.draw(textTwoPoints);
			windowload.draw(textMinutes);
			windowload.draw(textMinutes2);
			windowload.display();
	}
}

//////////////////////////////////////////////////////cin>>For Solver///////////////////////////////////////
void cinNumberForSolver(RenderWindow &windowgrid){
	sf::Font font, fontError;
	if (!font.loadFromFile("ShineBright-Demo.ttf"))
		cout << "Not found";

	if (!font.loadFromFile("BebasNeue.otf"))
		cout << "Not found";


	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(45);
	text.setColor(sf::Color::Black);
	int x, y;

	bool flagOfActive = 0;
	if (sf::Event::MouseButtonPressed){
		x = sf::Mouse::getPosition(windowgrid).x / 65;
		y = sf::Mouse::getPosition(windowgrid).y / 65;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
			problemSudoku[y][x] = 1;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
			problemSudoku[y][x] = 2;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
			problemSudoku[y][x] = 3;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
			problemSudoku[y][x] = 4;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
			problemSudoku[y][x] = 5;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
			problemSudoku[y][x] = 6;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
			problemSudoku[y][x] = 7;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
			problemSudoku[y][x] = 8;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
			problemSudoku[y][x] = 9;
		}
	}
	//////////////////////////////////////////////////////////Display_Cin>>Numbers///////////////////////////////////////////////////////

	for (int i = 0; i < 9; i++){
		for (int j = 0; j < 9; j++){
	
			if (problemSudoku[i][j] == 1){
					text.setString("1");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 2){
					text.setString("2");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 3){
					text.setString("3");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 4){

					text.setString("4");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);

				}
			else if (problemSudoku[i][j] == 5){

					text.setString("5");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 6){

					text.setString("6");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 7){

					text.setString("7");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 8){

					text.setString("8");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			else if (problemSudoku[i][j] == 9){

					text.setString("9");
					text.setPosition(65 * j + 30, 65 * i + 1);
					windowgrid.draw(text);
				}
			}
		}
	}
////////////////////////////////////////FunctionSolver//////////////////////////////
void screenSolverScreenfive(){
	int inputSudoku[9][9];
	sf::RenderWindow windowSolver(sf::VideoMode(585, 585), "			      									Solver V 1.0 plus ", sf::Style::Close);
	sf::Font font, fontError;
	if (!font.loadFromFile("ShineBright-Demo.ttf"))
		cout << "Not found";

	if (!font.loadFromFile("BebasNeue.otf"))
		cout << "Not found";


	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(45);

	while (windowSolver.isOpen())
	{
		sf::Event event;
		while (windowSolver.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				screenNum = 0;
				windowSolver.close();
				break;
			}
		}			drawingGridOfSudoko(windowSolver);
				cinNumberForSolver(windowSolver);
				if (event.key.code == Keyboard::Return){
					SudokuSolver(inputSudoku);
				}
			
			windowSolver.display();

	}

}

void screenPlayScreenFour(){
	///////////////////*****//////////////////////////choose The Name Of Raandom Sodoku //////////////*****////////////////////////////
	randomSodoku(arr);
	int x, y = 0, z = 0;
	sf::RenderWindow windowgrid(sf::VideoMode(800, 585), "Every thing will be ok", sf::Style::Close);
	sudoku_buttons sudokuButtons(windowgrid.getSize().x, windowgrid.getSize().y);
	//	window.setFramerateLimit(60);
	//windowgrid.setKeyRepeatEnabled(false);
	sf::Time seconds = sf::seconds(1);
	sf::Clock clock;
	sf::Music music;

	/////////////////////////////////////////Set File Of Font And Its Properties///////////////////////////////////////////////////////////////
	sf::Font font, fontError;
	if (!font.loadFromFile("ShineBright-Demo.ttf"))
		cout << "Not found";

	if (!font.loadFromFile("BebasNeue.otf"))
		cout << "Not found";


	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(45);

	///////////////////////*****///////////////Assign Random Numbers////////////////////*****//////////////////////
	srand(time(0));
	AssignRandomArr();


	///////////////////////*****/////////////////////Put Flags on the Random Numbers /////*****///////////////////////////////////
	flagsForOrignalNumbers();

	sf::Text textSeconds;
	textSeconds.setFont(font);
	textSeconds.setPosition(720, 550);

	sf::Text textMinutes;
	textMinutes.setFont(font);
	textMinutes.setPosition(680, 550);

	sf::Text textMinutes2;
	textMinutes2.setFont(font);
	textMinutes2.setPosition(660, 550);


	sf::Text textTwoPoints;
	textTwoPoints.setFont(font);
	textTwoPoints.setString(":");
	textTwoPoints.setPosition(700, 550);


	/////////////////////////////////////////////window ///////////////////////////////////////////////////////////////
	while (windowgrid.isOpen())
	{
		sf::Time elepased = clock.getElapsedTime();
		x = elepased.asSeconds();
		std::stringstream ssSeconds;
		ssSeconds << x;
		textSeconds.setString(ssSeconds.str().c_str());


		std::stringstream ssMinutes;
		ssMinutes << y;
		textMinutes.setString(ssMinutes.str().c_str());

		std::stringstream ssMinutes2;
		ssMinutes2 << z;
		textMinutes2.setString(ssMinutes2.str().c_str());

		if (x == 60) { clock.restart(); y++; x = 9; }
		if (x == 60 && y == 9) { clock.restart(); z++; y = 0; }

		sf::Event event;
		while (windowgrid.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				screenNum = 2;
				windowgrid.close();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					sudokuButtons.MoveUp();
					break;

				case sf::Keyboard::Down:
					sudokuButtons.MoveDown();
					break;

				case sf::Keyboard::Return:  // Enter pressed
					switch (sudokuButtons.selected_index())
					{
					case 0: //go to function check
						if (sf::Keyboard::A)
							cout << "a";
						checkIfTheSudokoIsRight(font, text, windowgrid);
						break;
					case 1: //go to file of music
						if (sf::Keyboard::B)
						if (sf::Keyboard::Return)
							play++;
						if (play == 1){
							music.openFromFile("LastTouchOfAudio/EDM.ogg");
							music.play();
						}
						else if (play == 2){
							music.openFromFile("LastTouchOfAudio/Hip-Hop&Alternative.ogg");
							music.play();
						}
						else if (play == 3){
							play = 0;
							music.openFromFile("LastTouchOfAudio/Piano&Jazz.ogg");
							music.play();
						}
						cout << play;
						break;
						case 2://draw window of pause
							if (sf::Keyboard::D)
							WindowPause(windowgrid, font);
							break;
					case 3:// go to function save 
						if (sf::Keyboard::C)
							windowSave(x, y, z);
						break;
					}
				/*case sf::Keyboard::H:
							music.stop();
				case sf::Keyboard::O:
							music.play();*/
				}
			}

		}
	//	if (screenNum != 4) break;     //if the variable != 3 , break from levels menu's loop

		///////////////////////////////////////////////Grid/////////////////////////////////////////////////////////////////
		drawingGridOfSudoko(windowgrid);


		////////////////////////////////&&&&&&&&&&&&&&&&/////////////////////////

	//drawintButtonsInSides(windowgrid, font, fontError);

		///////////////////*****////////////To  display random Numbers /////////////*****///////////////////
		displayRandomNumbers(text, windowgrid);



		////////////////////////*****//////////////////Cin>>Number///////////////////////////*****/////////////////////////////////
		cinNumber(text, windowgrid);
		drawCounterError(windowgrid, text, font);

		

		windowgrid.draw(text);
		sudokuButtons.draw(windowgrid);
		windowgrid.draw(textSeconds);
		windowgrid.draw(textTwoPoints);
		windowgrid.draw(textMinutes);
		windowgrid.draw(textMinutes2);


		windowgrid.display();
	}
}
int main()
{
	int x,y,z;
	/*sf::Music nextEpisode;
	nextEpisode.openFromFile("Songs/next_episode.ogg");
	nextEpisode.play();*/

	//main loop responsible for the management of screens
	while (true)
	{
		sf::RenderWindow window(sf::VideoMode(800, 585), "Sudoku V 1.00 ");   //main menu screen's decleration
		if (screenNum == 0)  //the variable will open main menu

		{
			sf::RenderWindow window(sf::VideoMode(800, 585), "Sudoku V 1.00 ");   //main menu screen's decleration
			main_menu mainMenu(window.getSize().x, window.getSize().y); //call main menu class

			sf::Texture sudoku_texture;
			if (!sudoku_texture.loadFromFile("Pictures/Sudoku.png")){}
			sf::Sprite sudoku_sprite;
			sudoku_sprite.setTexture(sudoku_texture);


			while (window.isOpen())   //main menu loop
			{

				sf::Event event;

				while (window.pollEvent(event))
				{

					switch (event.type)
					{
					case sf::Event::KeyReleased:
					{
												   switch (event.key.code)
												   {
												   case sf::Keyboard::Up: //move up
													   mainMenu.moveUp();
													   break;

												   case sf::Keyboard::Down: //move down
													   mainMenu.moveDown();
													   break;

												   case sf::Keyboard::Return:  //Enter pressed

													   switch (mainMenu.mainMenuPressed())  //whitch item selected
													   {

													   case 0:  //play selected

														   screenNum = 1;  //change the variable to 1
														   window.close();   //close main menu
														   break;

													   case 1:       //solver selected
														   screenNum = 5;
														   break;       //Nothing will happen

													   case 2:     //exit selected
														   screenNum = 2;   //change the variable to 2
														   window.close();  //close main menu
														   break;
													   }
												   }
					}
					}

				/*	if (event.key.code == sf::Keyboard::Right)
					{
						std::cout << "Riiiiight" << std::endl;
						auto newpos = nextEpisode.getPlayingOffset() + sf::seconds(5);
						nextEpisode.setPlayingOffset(sf::Time(newpos));

					}*/

					if (screenNum != 0)   //if variable changed !=0 , break from main menu's loop
					{
						break;
					}
				}

				if (screenNum != 0)     //if variable changed !=0 , break from main menu's loop
				{
					break;
				}


				window.clear(sf::Color::Transparent);
				window.draw(sudoku_sprite);
				mainMenu.draw(window);
				window.display();
			}

		}

		//********************************************play menu******************************************************************
		if (screenNum == 1)     //the variable will open play menu
		{

			playMenuFn();

		}

		//****************************************levels menu*********************************************************************
		if (screenNum == 3) //if the variable = 3 , then levels menu will open
		{
			levelMenuFn();
		}
		//*******************************************The game*********************************************************************


		if (screenNum == 4)
		{
			screenPlayScreenFour();
			
		}
		//********************************************Solver*******************************************************************
		if (screenNum == 5)
		{
			screenSolverScreenfive();
		}
		if (screenNum == 6)
		{
			screenSixload();
		}

		//********************************************Application exit**********************************************************

		if (screenNum == 2||screenNum==10)         //if the variable = 2 , then break from main while true loop 
		{
			break;
		}
		


	}
	return 0;
}
