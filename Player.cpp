#include "Player.hpp"
#include <iostream>

Player::Player(std::string name)
{
	setName(name);
	setFont();
}

void Player::setName(std::string name) {
	playerName = name;
}

void Player::setFont() {
	font.loadFromFile("Starjedi.ttf");
}

void Player::playerWon() {
	isWinner = true;
}

void Player::incrimentScore(){
	score++;
	playerScore.setString(std::to_string(score));
	if(score == 10) {
		playerWon();
	}
}

void Player::setupPlayer(int player) {
	paddle.setFillColor(sf::Color::White);
	
	playerBanner.setFont(font);
	playerBanner.setString(playerName);
	playerBanner.setFillColor(sf::Color::White);
	playerBanner.setCharacterSize(24);
	
	playerScore.setFont(font);
	playerScore.setString(std::to_string(score));
	playerScore.setFillColor(sf::Color::Red);
	playerScore.setCharacterSize(24);
	
	if(player == 1){
		setPaddle(1);
		playerBanner.setPosition(100, 20);
		playerScore.setPosition(playerBanner.getPosition().x + playerBanner.getGlobalBounds().width + 20, 20);
	} else{
		setPaddle(2);
		playerBanner.setPosition(600, 20);
		playerScore.setPosition(playerBanner.getPosition().x - 40, 20);
	}
}

void Player::setPaddle(int player){
	if(player == 1){
		paddle.setPosition(50, 250);
	} else{
		paddle.setPosition(750, 250);
	}
}

// operation methods
void Player::detectMovement(int player){
	if(player == 1){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			paddle.move(0.f, 10.f);
			if(paddle.getPosition().y + paddle.getGlobalBounds().height > 600) {
				paddle.setPosition(paddle.getPosition().x, 600 - paddle.getGlobalBounds().height);
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			paddle.move(0.f, -10.f);
			if(paddle.getPosition().y < 0) {
				paddle.setPosition(paddle.getPosition().x, 0);
			}
		}
	} else{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			paddle.move(0.f, 10.f);
			if(paddle.getPosition().y + paddle.getGlobalBounds().height > 600) {
				paddle.setPosition(paddle.getPosition().x, 600 - paddle.getGlobalBounds().height);
			}
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			paddle.move(0.f, -10.f);
			if(paddle.getPosition().y < 0) {
				paddle.setPosition(paddle.getPosition().x, 0);
			}
		}
	}
}

// get methods
sf::RectangleShape Player::getPaddle(){
	return paddle;
}

sf::Font Player::getFont(){
	return font;
}
sf::Text Player::getBanner(){
	return playerBanner;
}

sf::Text Player::getScore(){
	return playerScore;
}

std::string Player::getName(){
	return playerName;
}

Player::~Player()
{
}

