#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

class Game{
private:
	sf::RenderWindow window;
	Board board;
	
	bool isGameOver;


	void processInput();
	void update();
	void render();

public:
	Piece::Type currentPlayer;
	Game();
	void run();

};

