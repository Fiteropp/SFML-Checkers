#include "Game.h"

#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>


// Constructor: Initialize window, set current player, and load board textures
Game::Game()
	: window(sf::VideoMode(720, 720), "C++ Checkers"),
	currentPlayer(Piece::Type::WHITE), isGameOver(false),
	board(this) {  // Pass the 'this' pointer to the Board constructor
	board.loadTextures();
}

// Process mouse input events, including player move selection
void Game::processInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close(); // Close the window when the close event is triggered
			return; // Exit after closing the window to prevent further processing
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			int mouseX = event.mouseButton.x;
			int mouseY = event.mouseButton.y;

			int gridX = mouseX / 50; // Tile size of 50px
			int gridY = mouseY / 50; // Tile size of 50px

			// Handle board click or other actions as needed
			board.handleClick(gridX, gridY, currentPlayer);
		}
	}
}




void Game::stopGame() {
	std::cout << "Game Over!" << std::endl;

	if (window.isOpen()) {
		window.close();
	}
	else {
		std::cerr << "Window is already closed!" << std::endl;
	}
}





// Update the game state, check for win condition
void Game::update() {
	// Check if the current player has won
	if (board.checkWinCondition(currentPlayer)) {
		stopGame(); // Stop the game when a win condition is met
		std::cout << (currentPlayer == Piece::Type::BLACK ? "Black" : "White") << " wins!" << std::endl;
	}
}



void Game::render() {
	window.clear();
	board.render(window);
	window.display();
}

void Game::run() {
	// Main game loop
	while (window.isOpen()) {
		processInput(); // Handle user input
		update();       // Update game state
		render();       // Render graphics to the window
	}

}
