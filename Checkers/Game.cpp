#include "Game.h"
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

sf::Texture resetButtonTexture;
sf::Sprite restartButtonSprite; 

sf::Texture playbtnTexture;
sf::Sprite playBtnSprite;

sf::Texture logoTexture;
sf::Sprite logoTextureSprite;

sf::Texture stopButtonTexture2;
sf::Sprite stopButtonSprite2;


Game::Game()
    : window(sf::VideoMode(720, 720), "C++ Checkers"),
    currentPlayer(Piece::Type::WHITE), isGameOver(false),
    board(this) {  
   
    stopButton2.setSize(sf::Vector2f(150, 75));  
    stopButton2.setFillColor(sf::Color::Red); 
    stopButton2.setPosition(460, 340);


    logo.setSize(sf::Vector2f(50.0f, 50.0f)); 
	logo.setFillColor(sf::Color::White);
	logo.setSize(sf::Vector2f(100, 50));
  
    board.loadTextures(); 



    playBtn.setSize(sf::Vector2f(720, 720));
	playBtn.setFillColor(sf::Color(255, 255, 255, 150));


    if (!stopButtonTexture2.loadFromFile("textures/exit_btn.png")) {
        std::cout << "Failed to load stop button texture!" << std::endl;
    }
    else {
        std::cout << "Stop button texture loaded successfully!" << std::endl;
        stopButtonSprite2.setTexture(stopButtonTexture2);
    }


	if (!logoTexture.loadFromFile("textures/logo.png")) {
		std::cout << "Failed to load logo texture!" << std::endl;
	}
	else {
		std::cout << "Stop button texture loaded successfully!" << std::endl;
		logoTextureSprite.setTexture(logoTexture);
	}


    if (!playbtnTexture.loadFromFile("textures/play_btn.png")) {
        std::cerr << "Failed to load play button texture!" << std::endl;
    }
    else {
        std::cout << "play button texture loaded successfully!" << std::endl;
        playBtnSprite.setTexture(playbtnTexture); 
        playBtnSprite.setPosition(250, 280); 
        playBtnSprite.setScale(5.5f, 5.5f);

    }




    // Load the restart button texture
    if (!resetButtonTexture.loadFromFile("textures/restart_btn.png")) {
        std::cerr << "Failed to load restart button texture!" << std::endl;
    }
    else {
        std::cout << "Restart button texture loaded successfully!" << std::endl;
        restartButtonSprite.setTexture(resetButtonTexture); // Set the texture to the sprite
        restartButtonSprite.setPosition(460, 30); // Position the sprite
        restartButtonSprite.setScale(3.0f, 3.0f);

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

            int gridX = mouseX / 50; // Assuming tile size is 50px
            int gridY = mouseY / 50;

            board.handleClick(gridX, gridY, currentPlayer);  // Handle click on the board

            // Handle the restart and play buttons
            if (restartButtonSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                restartGame();
            }
            if (playBtnSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                hideMenu();
            }

            if (stopButtonSprite2.getGlobalBounds().contains(mouseX, mouseY)) {
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
        processInput(); // Handle user input
        update();       // Update game state
        render();       // Render graphics to the window
    }
}


void Game::render() {
    window.clear(sf::Color());   // Clear the window

    // Render the board and other elements
    board.render(window);

    // Render the restart button sprite
    window.draw(restartButtonSprite);
logoTextureSprite.setPosition(10, 50);
logoTextureSprite.setScale(1.5f, 1.5f); 

stopButtonSprite2.setPosition(260, 420);
stopButtonSprite2.setScale(5.0f, 5.0f);
    // Render the play button and sprite only if it's visible
    if (isPlayButtonVisible) {
        window.draw(playBtn);      // Draw the rectangle (background of the play button)
        window.draw(playBtnSprite); 
        window.draw(logoTextureSprite);
        window.draw(stopButtonSprite2);// Draw the play button sprite
    }


  
    // Display everything drawn so far
    window.display();
}

