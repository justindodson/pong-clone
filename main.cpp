#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include "Player.hpp"

using namespace sf;
using std::cout;

// global variables

const unsigned int WINDOW_WIDTH = 800 ;
const unsigned int WINDOW_HEIGHT = 600;

float xEasy = 5.f;
float yEasy = 5.f;
float xMed = 7.5f;
float yMed = 7.5f;
float xHard = 10.f;
float yHard = 10.f;

float moveX = xMed;
float moveY = yMed;

bool gameStart = false;
bool paused = false;

// game method prototype
void detectWallCollision(sf::CircleShape ball, unsigned int winWidth, unsigned int winHeight);
void paddleCollision(sf::CircleShape ball, sf::RectangleShape paddle1, sf::RectangleShape paddle2);
void detectScore(sf::CircleShape *ball, unsigned int winWidth, unsigned int winHeight, Player *player1, Player *player2);
void ballReset(sf::CircleShape *ball);


int main()
{
   sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong");
   window.setFramerateLimit(60);
   
   // build the ball
    sf::CircleShape ball(10.f);
	ball.setFillColor(sf::Color::White);
	ballReset(&ball);
	
	// build the players and set up controls
	Player player1 = Player("Player 1");
	player1.setupPlayer(1);
	Player player2 = Player("Player 2");
	player2.setupPlayer(2);
	
	
    while (window.isOpen())
    {
        sf::Event event;
		
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
		
		if(Keyboard::isKeyPressed(Keyboard::Space) && !gameStart){
			gameStart = true;
			Sleep(100);
		} 
		else if(Keyboard::isKeyPressed(Keyboard::Space) && gameStart){
			gameStart = false;
			Sleep(100);
		}

		// start game loop
		if(gameStart){
			ball.move(moveX, moveY);
			detectWallCollision(ball, WINDOW_WIDTH, WINDOW_HEIGHT);
			player1.detectMovement(1);
			player2.detectMovement(2);
			paddleCollision(ball, player1.getPaddle(), player2.getPaddle());
			detectScore(&ball, WINDOW_WIDTH, WINDOW_HEIGHT, &player1, &player2);
		}

		
		// update the window (draw)
        window.clear();
        window.draw(ball);
		window.draw(player1.getPaddle());
		window.draw(player1.getBanner());
		window.draw(player1.getScore());
		window.draw(player2.getPaddle());
		window.draw(player2.getBanner());
		window.draw(player2.getScore());
        window.display();
		

		
		
    }
	return 0;
}

void ballReset(sf::CircleShape *ball){
	std::cout << "ball reset called" << std::endl;
	ball->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT /2);
}

void detectWallCollision(sf::CircleShape ball, unsigned int winWidth, unsigned int winHeight){
	
	// bottom collision
	if(ball.getPosition().y + ball.getGlobalBounds().height > winHeight) {
		moveY = -moveY;
		ball.move(moveX, moveY);
	}
	
	// top collision
	if(ball.getPosition().y < 0) {
		moveY = moveY * (-1);
		ball.move(moveX, moveY);
	}
}

void paddleCollision(sf::CircleShape ball, sf::RectangleShape paddle1, sf::RectangleShape paddle2){
	if(ball.getPosition().x + ball.getGlobalBounds().width >  paddle2.getPosition().x){
		if(ball.getPosition().y >= paddle2.getPosition().y 
			&& ball.getPosition().y <= paddle2.getPosition().y + paddle2.getGlobalBounds().height){
				moveX = -moveX;
				ball.move(moveX, moveY);
			}
	}
	
	if(ball.getPosition().x <  paddle1.getPosition().x + paddle1.getGlobalBounds().width){
		if(ball.getPosition().y >= paddle1.getPosition().y 
			&& ball.getPosition().y <= paddle1.getPosition().y + paddle1.getGlobalBounds().height){
				moveX = moveX * (-1);
				ball.move(moveX, moveY);
			}
	}
}

void detectScore(sf::CircleShape *ball, unsigned int winWidth, unsigned int winHeight, Player *player1, Player *player2){
	// right collision - Player 1 score
	if(ball->getPosition().x + ball->getGlobalBounds().width > winWidth) {
		// incriment score for player 1
		// reset the ball position
		// reset the game active to false
		player1->incrimentScore();
		player1->setPaddle(1);
		player2->setPaddle(2);
		ballReset(ball);
		gameStart = false;
		std::cout << "Player One Score" << std::endl;
	}
	
	// left collision - Player 2 score
	if(ball->getPosition().x < 0) {
		player2->incrimentScore();
		player2->setPaddle(2);
		player1->setPaddle(1);
		ballReset(ball);
		gameStart = false;
		std::cout << "Player Two Score" << std::endl;
	}
}