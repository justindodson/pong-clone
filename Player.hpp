#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
private:
	int score {0};
	std::string playerName;
	bool isWinner;
	sf::Font font;
	sf::RectangleShape paddle {sf::RectangleShape(sf::Vector2f(10.f, 100.f))};
	sf::Text playerBanner;
	sf::Text playerScore;

	
public:
	Player(std::string name);
	
	// setup functions
	void setName(std::string);
	void setFont();
	void setupPlayer(int player);
	void setPaddle(int player);
	
	// get functions
	sf::RectangleShape getPaddle();
	sf::Font getFont();
	sf::Text getBanner();
	sf::Text getScore();
	std::string getName();
	
	
	// operation functions
	void detectMovement(int player);
	void incrimentScore();
	void playerWon();
	
	~Player();

};

#endif // PLAYER_HPP
