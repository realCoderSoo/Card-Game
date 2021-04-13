/***************************FILE HEADER / COVER INFORMATION***********************************************
Filename:				game.cpp
Version:				1.0
**********************************************************************************************************
Author:					Soojin Han 
Student No:				040698591   
Course Name/Number:		C++ CST8219
Lab Sect:				303 
Assignment #:			Final Project
Assignment name:		Final Project (Card-game)
Due Date:				Aug 7 2020
Submission Date:		Jul 31 2020
Professor:				Eric Torunski
Purpose:				This program finds draws 10 pairs of cards on the screen. When user clicks
						 on a matching pair consecutively, they disppear and a happy sound is played.
						other wise, a sad sound is played and game continues until screen is cleared.
						After that user is offered to play again or quit.
***********************************************************************************************************/

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <stdlib.h> 
#include <cstdlib>
#include <algorithm>
using namespace std;
using namespace sf;

namespace FinalProject
{
	class game {

	public:
		short a = 0;
		int numClicks = 0;				// number of clicks during one play of the game--> used to track number of attempts 
		int matchCounter = 0;			// number of cards matched--> used to detects the game's end
		map<short, short> shuffleCards;	// map to map the values from the picId array with the texture/card number to be used in matching
		short picId[20] = {0};			// array to store the card name/number as a unique id
		short picFound = 0;
		short getId = 0;


		
		/********************************************************************
		Function name:							startGame
		Purpose:								The main body of the game. Function is used to start the game and when user selects
												to play gain
		In parameters:	Texture& backT b		Pointer to the Texture back
						vector<Sprite>* cards   Pointer to the Vector of sprites that holds the cards
		Out parameters:
		Version:								1.0
		Author:									Soojin Han
		**********************************************************************/
		void startGame(Texture& backT, vector<Sprite>* cards, vector<Texture>* frontT) {
			a = 0;
			numClicks = 0;
			matchCounter = 0;
			srand((unsigned int)time(NULL));
			float locX = 0.3f;
			float locY = 0.3f;


			if (!backT.loadFromFile("back.png")) {
				cout << "Error! failed to load a file required for the game to run" << endl;
			}

			for (int i = 0; i < 20; ++i)
			{
				picId[i] = i;
			}

			for (int i = 20 - 1; i > 0; i--)
			{
				// Pick a random index from 0 to i  
				int j = rand() % (i + 1);

				// Swap arr[i] with the element at random index  
				swap(picId[i], picId[j]);
			}

			// for the loop, if the map is empty--> first round of the game.
			if (shuffleCards.empty()) {
				for (short i = 0; i < frontT->size(); i++) {

					if (!frontT->at(picId[i]).loadFromFile(to_string(i + 1) + ".PNG")) {
						cout << "Error! failed to load file/s" << endl;
					}
					shuffleCards.insert(pair<short, short>(picId[i], i + 1));
				}
			}

			// for the loop, if the map is not empty-->not the first round, empty map first then proceed as normal.
			else {
				shuffleCards.clear();

				for (short i = 0; i < frontT->size(); i++) {

					if (!frontT->at(picId[i]).loadFromFile(to_string(i + 1) + ".PNG")) {
						cout << "Error! failed to load file/s" << endl;
					}

					shuffleCards.insert(pair<short, short>(picId[i], i + 1));
				}
			}

			if (cards->empty()) {

				for (size_t i = 0; i < 20; i++)
				{
					if (i > 0 && i % 4 == 0)
					{
						locY += 110;
						locX = 0.3f;
					}

					cards->push_back(Sprite(backT));
					cards->at(i).setScale(0.8f, 0.8f);
					cards->at(i).setPosition(locX, locY);
					locX += 100;
				}
			}
			else {
				cards->clear();

				for (size_t i = 0; i < 20; i++)
				{
					if (i > 0 && i % 4 == 0)
					{
						locY += 110;
						locX = 0.3f;
					}

					cards->push_back(Sprite(backT));
					cards->at(i).setScale(0.8f, 0.8f);
					cards->at(i).setPosition(locX, locY);
					locX += 100;
				}

			}
		}
	};
}
