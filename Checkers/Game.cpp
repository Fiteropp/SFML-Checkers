#include "Game.h"
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"


Game::Game()
	: window(sf::VideoMode(720, 720), "C++ Checkers"),
	currentPlayer(Piece::WHITE), isGameOver(false) {
	board.loadTextures();
}

void Game::processInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button = sf::Mouse::Left) {
			int mouseX = event.mouseButton.x;
			int mouseY = event.mouseButton.y;

			int gridX = mouseX / 50; //Divide by tile size
			int gridY = mouseY / 50;

			board.handleclick
		}
	}
}
