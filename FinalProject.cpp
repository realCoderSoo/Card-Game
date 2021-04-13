/***************************FILE HEADER / COVER INFORMATION***********************************************
Filename:				FinalProject.cpp
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

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <stdlib.h> 
#include <cstdlib>
#include <algorithm>
#include "game.cpp"
using namespace std;
using namespace sf;


RenderWindow window(VideoMode(500, 675), "My window");
vector<Sprite>* cards = new vector<Sprite>; // vector of sprites to hold the cards
vector<Texture>front(20);					// vector of textures to hold 10 pairs of textures
Texture back;							   // texture for the back of the crads
Color customGreen(7, 76, 10);			  // rgb color of the back board


/********************************************************************
Function name:					main
Purpose:						main function
In parameters:					none
Out parameters:					0 for successful execution
Version:						1.0
Author:							Soojin Han
**********************************************************************/
int main()
{
	Sprite playAgain, quitSprite; // sprite for the play again & quit options
	Texture play, quitTexture;	 //	Textures for the play again and quit sprites
	SoundBuffer happyBuffer, unhappyBuffer, gameWonBuffer;
	Sound happySound, unhappySound, gameWon;
	happySound.setBuffer(happyBuffer);
	unhappySound.setBuffer(unhappyBuffer);
	gameWon.setBuffer(gameWonBuffer);
	Font font;
	Text winMessage;

	/*check if sound files are loaded successfully*/
	if (!happyBuffer.loadFromFile("happy.wav") || !unhappyBuffer.loadFromFile("sad.wav") || !gameWonBuffer.loadFromFile("gameWon.wav")) {
		cout << "Error! failed to load file/s" << endl;
	}

	/*check if image files are loaded successfully*/
	if (!back.loadFromFile("back.PNG") || !play.loadFromFile("playAgain.png") || !quitTexture.loadFromFile("quit.png")) {
		cout << "Error! failed to load a file/s" << endl;
	}

	if (!font.loadFromFile("arial.ttf")) {
		cout << "Error! failed to load file/s" << endl;
	}

	/*setting winning, play again, and quit features*/
	winMessage.setFont(font);
	winMessage.setFillColor(Color::Red);
	winMessage.setCharacterSize(28);
	winMessage.setPosition(0, 300);
	playAgain.setTexture(play);
	playAgain.setPosition(10, 540);
	quitSprite.setTexture(quitTexture);
	quitSprite.setPosition(235, 545);

	FinalProject::game cardGame = FinalProject::game();
	cardGame.startGame(back, cards, &front);

	// run the program as long as the window is open
	while (window.isOpen())
	{
		auto mouse_pos = Mouse::getPosition(window); // Mouse position relative to the window
		auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position into screen coordinates

		// find if mouse is clicked inside a card
		if (Mouse::isButtonPressed(Mouse::Left)) {

			for (short i = 0; i < 20; i++) {
				// Mouse is inside the card.
				if (cards->at(i).getGlobalBounds().contains(translated_pos)) {
					cardGame.numClicks++;
					cards->at(i).setTexture(front.at(i));

					// if cards match
					if ((cardGame.shuffleCards.find(i)->second == cardGame.picFound + 10 ||
						cardGame.shuffleCards.find(i)->second == cardGame.picFound - 10) && cardGame.a == 1)
					{
						// increment number of matched cards
						cardGame.matchCounter++;
						window.clear(Color(customGreen));

						/*diaplaying matching cards before removed*/
						for (size_t i = 0; i < cards->size(); i++)
						{
							window.draw(cards->at(i));
						}

						window.display();
						// move matched cards out of screen's boundaries
						cards->at(i).setPosition(-100, -100);
						cards->at(cardGame.getId).setPosition(-100, -100);
						window.clear(Color(customGreen));
						// play happy sound on match
						happySound.play();
						sleep(milliseconds(3000));
						cardGame.a = 0;

						if (cardGame.matchCounter == 10) {
							gameWon.play();
						}

						break;
					}

					// if cards clicked don not match
					else
					{
						/*two cards are clicked so it will be displayed for 3 seconds before flipped back*/
						if (cardGame.a == 1)
						{
							window.clear(Color(customGreen));

							for (size_t i = 0; i < cards->size(); i++)
							{
								window.draw(cards->at(i));
							}

							window.display();
							cards->at(i).setTexture(back);/*setting the picture to the original card picture*/
							cards->at(cardGame.getId).setTexture(back);
							cardGame.a = 0;
							unhappySound.play();/*sound for no match*/
							sleep(milliseconds(3000));
						}
						else
						{							
							cardGame.a++;
							sleep(milliseconds(200));
						}

					}

					/*getting the index for the shape*/
					cardGame.picFound = cardGame.shuffleCards.find(i)->second;
					cardGame.getId = (short)i;
					break;
				}
			}

			// if a game round is done and user click on play again
			if (cardGame.matchCounter == 10) {
				if (playAgain.getGlobalBounds().contains(translated_pos)) {// game done and user clciks play again
					window.clear(Color(customGreen));
					cardGame.startGame(back, cards, &front);

					for (size_t i = 0; i < cards->size(); i++)
					{
						window.draw(cards->at(i));
						window.display();
					}

				}
				else if (quitSprite.getGlobalBounds().contains(translated_pos)) {// game done and user clicks quit
					return 0;
				}
			}
		}

		window.clear(Color(customGreen));

		// draw all cards
		for (size_t i = 0; i < cards->size(); i++)
		{
			window.draw(cards->at(i));
		}

		// if game round is over, display win message and game stats
		if (cardGame.matchCounter == 10) {
			winMessage.setString("You won! good job! Number of tries: " + to_string((cardGame.numClicks / 2)));
			window.draw(winMessage);
			window.draw(playAgain);
			window.draw(quitSprite);
		}

		window.display();
	}

	delete[] cards;
	return 0;
}

