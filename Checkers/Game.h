#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"

class Game{
private:
	sf::RenderWindow window;
	Board board;
	Piece::Type currentPlayer;
	bool isGameOver;

	void processInput();
	void process();
	void render();

public:
	Game();
	void run();

};

