#include "Game.h"
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

sf::Texture resetButtonTexture;
sf::Sprite restartButtonSprite;  // Change to sf::Sprite

// Constructor: Initialize window, set current player, load board textures, and button setup
Game::Game()
    : window(sf::VideoMode(720, 720), "C++ Checkers"),
    currentPlayer(Piece::Type::WHITE), isGameOver(false),
    board(this) {  // Pass the 'this' pointer to the Board constructor

    // Load textures for the board and buttons
    board.loadTextures(); // Call Board's loadTextures method once during initialization

    // Load the restart button texture
    if (!resetButtonTexture.loadFromFile("textures/restart_btn.png")) {
        std::cerr << "Failed to load restart button texture!" << std::endl;
    }
    else {
        std::cout << "Restart button texture loaded successfully!" << std::endl;
        restartButtonSprite.setTexture(resetButtonTexture); // Set the texture to the sprite
        restartButtonSprite.setPosition(420, 328); // Position the sprite
        restartButtonSprite.setScale(2.0f, 2.0f);

    }
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

            // Check if the Restart button is clicked
            if (restartButtonSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                restartGame();
            }
        }
    }
}

// Stop the game
void Game::stopGame() {
    std::cout << "Game Over!" << std::endl;
    isGameOver = true;
    if (window.isOpen()) {
        window.close();
    }
    else {
        std::cerr << "Window is already closed!" << std::endl;
    }
}

// Restart the game
void Game::restartGame() {
    std::cout << "Restarting Game..." << std::endl;
    isGameOver = false;
    currentPlayer = Piece::Type::WHITE; // Reset current player
    board.resetBoard();  // Reset the board state
}

// Update the game state, check for win condition
void Game::update() {
    // Check if the current player has won
    if (board.checkWinCondition(currentPlayer)) {
        stopGame(); // Stop the game when a win condition is met
        std::cout << (currentPlayer == Piece::Type::BLACK ? "Black" : "White") << " wins!" << std::endl;
    }
}

// Main game loop
void Game::run() {
    // Main game loop
    while (window.isOpen()) {
        processInput(); // Handle user input
        update();       // Update game state
        render();       // Render graphics to the window
    }
}

// Render the game content, including buttons
void Game::render() {
    // Set the background color (e.g., light blue)
    window.clear(sf::Color());  // Clear the window with light blue color

    // Render the game content (e.g., board, pieces)
    board.render(window);

    // Render buttons
    window.draw(restartButtonSprite); // Draw the restart button sprite

    // Display everything drawn so far
    window.display();
}
