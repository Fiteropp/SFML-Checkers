#include "Game.h"
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

#define DEBUG // Comment this out to disable debug mode

sf::Texture resetButtonTexture;
sf::Sprite restartButtonSprite;

sf::Texture playbtnTexture;
sf::Sprite playBtnSprite;

sf::Texture logoTexture;
sf::Sprite logoTextureSprite;

sf::Texture menuGameExitTexture;
sf::Sprite menuGameExitSprite;

Game::Game()
    : window(sf::VideoMode(900, 720), "C++ Checkers", sf::Style::Titlebar | sf::Style::Close), 
    currentPlayer(Piece::Type::WHITE), isGameOver(false),
    board(this) {

    logo.setSize(sf::Vector2f(50.0f, 50.0f));
    logo.setFillColor(sf::Color::White);
    logo.setSize(sf::Vector2f(100, 50));

    board.loadTextures();

    playBtn.setSize(sf::Vector2f(900, 720));
    playBtn.setFillColor(sf::Color(0, 128, 111, 255));
    loadButtonsTextures();
}



// Function to load textures
bool Game::loadTexture(const std::string& filePath, sf::Texture& texture) {
    if (!texture.loadFromFile(filePath)) {
#ifdef DEBUG
        std::cerr << "Failed to load texture: " << filePath << std::endl;
#endif
        return false; // Indicate failure
    }
#ifdef DEBUG
    std::cout << "Successfully loaded texture: " << filePath << std::endl;
#endif
    return true; // Indicate success
}

void Game::configureSprite(sf::Sprite& sprite, sf::Texture& texture,
    sf::Vector2f position,
    sf::Vector2f scale) {
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(scale);
}



void Game::loadButtonsTextures()
{

    if (loadTexture("textures/exit_btn.png", menuGameExitTexture)) {
        configureSprite(menuGameExitSprite, menuGameExitTexture);
    }

    // Load and configure the logo texture
    if (loadTexture("textures/logo.png", logoTexture)) {
        configureSprite(logoTextureSprite, logoTexture);
    }

    // Load and configure the play button texture
    if (loadTexture("textures/play_btn.png", playbtnTexture)) {
        configureSprite(playBtnSprite, playbtnTexture, { 330, 280 }, { 5.5f, 5.5f });
    }

    // Load and configure the restart button texture
    if (loadTexture("textures/restart_btn.png", resetButtonTexture)) {
        configureSprite(restartButtonSprite, resetButtonTexture, { 690, 60 }, { 2.25f, 2.25f });
    }
}

void Game::hideMenu() {
    isPlayButtonVisible = false;  // Set the flag to hide the play button
}

void Game::processInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;

            const float tileSize = 75;

            int gridX = mouseX / tileSize; // Assuming tile size is 50px
            int gridY = mouseY / tileSize;

            board.handleClick(gridX, gridY, currentPlayer);  // Handle click on the board

            if (restartButtonSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                restartGame();
            }
            if (playBtnSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                hideMenu();
            }

            if (menuGameExitSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                std::cout << "Stop button clicked!" << std::endl;
                window.close();
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
        processInput(); 
        update();       
        render();       
    }
}

void Game::render() {
    window.clear(sf::Color());   // Clear the window

    // Render the board and other elements
    board.render(window);

    // Render the restart button sprite
    window.draw(restartButtonSprite);
    logoTextureSprite.setPosition(20, 35);
    logoTextureSprite.setScale(1.85f, 1.85f);

    menuGameExitSprite.setPosition(342, 420);
    menuGameExitSprite.setScale(5.0f, 5.0f);

    // Render the play button and sprite only if it's visible
    if (isPlayButtonVisible) {
        window.draw(playBtn);   
        window.draw(playBtnSprite);
        window.draw(logoTextureSprite);
        window.draw(menuGameExitSprite);// Draw the Exit button sprite
    }
    else {
        //Move Exit Button
        menuGameExitSprite.setScale(2.0f, 2.0f);
        menuGameExitSprite.setPosition(730, 610);
        window.draw(menuGameExitSprite);

        window.draw(restartButtonSprite);
    }

    // Display everything drawn so far
    window.display();
}
