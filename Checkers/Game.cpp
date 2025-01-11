#include "Game.h"
#include <SFML/Window.hpp>
#include "SFML/Graphics.hpp"
#include <iostream>

#define DEBUG // Comment this out to disable debug mode


//Reset button
sf::Texture resetButtonTexture;
sf::Sprite restartButtonSprite;

//Play Button in menu
sf::Texture playbtnTexture;
sf::Sprite playBtnSprite;

//Logo in menu
sf::Texture logoTexture;
sf::Sprite logoTextureSprite;

//Exit button in menu
sf::Texture menuGameExitTexture;
sf::Sprite menuGameExitSprite;

//CurrentPlayer Frame
sf::Texture currentPlayerFrameTexture;
sf::Sprite currentPlayerFrameSprite;

//Victory texture on winner screen
sf::Texture victoryTextTexture;
sf::Sprite victoryTextSprite;

//Winner text
sf::Texture winnerTextTexture;
sf::Sprite winnerTextSprite;

//Close button
sf::Texture closeVictoryScreenBtnTexture;
sf::Sprite  closeVictoryScreenBtnSprite;

//Black checker
sf::Texture playerWinnerTextureBlack;
sf::Sprite playerWinnerSpriteBlack;

//White checker
sf::Texture playerWinnerTextureWhite;
sf::Sprite playerWinnerSpriteWhite;


Game::Game()
    : window(sf::VideoMode(800, 600), "C++ Checkers", sf::Style::Titlebar | sf::Style::Close),
    currentPlayer(Piece::Type::WHITE), isGameOver(false),
    board(this), victoryScreenVisible(true) { 

    board.loadTextures();

    menuBackground.setSize(sf::Vector2f(800, 600));
    menuBackground.setFillColor(sf::Color(0, 128, 111, 255));

    winScreenBackground.setSize(sf::Vector2f(800, 180));
    winScreenBackground.setFillColor(sf::Color(116, 123, 123, 220));
    winScreenBackground.setPosition(0, 240);

    loadButtonsTextures();
}




bool Game::loadTexture(const std::string& filePath, sf::Texture& texture) {
    if (!texture.loadFromFile(filePath)) {
#ifdef DEBUG
        std::cerr << "Failed to load texture " << filePath << std::endl;
#endif
        return false; 
    }
#ifdef DEBUG
#endif
    return true; 
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

    // logo texture
    if (loadTexture("textures/logo.png", logoTexture)) {
        configureSprite(logoTextureSprite, logoTexture);
    }

    // play button texture
    if (loadTexture("textures/play_btn.png", playbtnTexture)) {
        configureSprite(playBtnSprite, playbtnTexture, { 267, 280 }, { 5.5f, 5.5f });
    }

    // restart button texture
    if (loadTexture("textures/restart_btn.png", resetButtonTexture)) {
        configureSprite(restartButtonSprite, resetButtonTexture, { 610, 20 }, { 2.25f, 2.25f });
    }

    // current player frame
    if (loadTexture("textures/current_player_frame.png", currentPlayerFrameTexture)) {
        configureSprite(currentPlayerFrameSprite, currentPlayerFrameTexture, { 630, 200 }, { 2.0f, 2.0f });
    }

    // victory text texture
    if (loadTexture("textures/victory_text.png", victoryTextTexture)) {
        configureSprite(victoryTextSprite, victoryTextTexture, { 80, 20 }, { 1.0f, 1.0f });
    }

    // winner text texture
    if (loadTexture("textures/winner_text.png", winnerTextTexture)) {
        configureSprite(winnerTextSprite, winnerTextTexture, { 180, 270 }, { 1.0f, 1.0f });
    }
    
    // close button
    if (loadTexture("textures/close_btn.png", closeVictoryScreenBtnTexture)) {
        configureSprite(closeVictoryScreenBtnSprite, closeVictoryScreenBtnTexture, { 350, 370 }, { 1.5f, 1.5f });
    }

    // white checker texture
    if (loadTexture("textures/white_king.png", playerWinnerTextureWhite)) {
        configureSprite(playerWinnerSpriteWhite, playerWinnerTextureWhite, { 85, 270 }, { 5.0f, 5.0f });
    }

    // white black texture
    if (loadTexture("textures/black_king.png", playerWinnerTextureBlack)) {
        configureSprite(playerWinnerSpriteBlack, playerWinnerTextureBlack, { 85, 270 }, { 5.0f, 5.0f });
    }
    
}

void Game::hideMenu() {
    isMenuVisible = false;  
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

            int gridX = mouseX / tileSize; 
            int gridY = mouseY / tileSize;

            board.handleClick(gridX, gridY, currentPlayer);  

            if (restartButtonSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                restartGame();
            }

            if (playBtnSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                hideMenu();
            }

            if (closeVictoryScreenBtnSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                restartGame();
            }

            if (menuGameExitSprite.getGlobalBounds().contains(mouseX, mouseY)) {
                std::cout << "Exit button clicked" << std::endl;
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

}


void Game::restartGame() {
    std::cout << "Restarting Game" << std::endl;
    isGameOver = false;
    currentPlayer = Piece::Type::WHITE; 
    board.initializeBoard();  
    victoryScreenVisible = false;
}


void Game::update() {
   
    if (board.checkWinCondition(currentPlayer)) {
         
        
        victoryScreenVisible = true;

    }
}


void Game::run() {
    
    while (window.isOpen()) {
        processInput(); 
        update();       
        render();       
    }
}

void Game::render() {
    window.clear(sf::Color(0, 24, 30));   

    board.render(window);

    window.draw(restartButtonSprite);

    logoTextureSprite.setPosition(20, 25);
    logoTextureSprite.setScale(1.65, 1.65f);

    menuGameExitSprite.setPosition(280, 420);
    menuGameExitSprite.setScale(5.0f, 5.0f);

    
    if (isMenuVisible) {
        window.draw(menuBackground);   
        window.draw(playBtnSprite);
        window.draw(logoTextureSprite);
        window.draw(menuGameExitSprite);
    }
    else {
        menuGameExitSprite.setScale(2.0f, 2.0f);
        menuGameExitSprite.setPosition(650, 530);

        window.draw(menuGameExitSprite);

        window.draw(restartButtonSprite);

        window.draw(currentPlayerFrameSprite);
    }

    
    if (victoryScreenVisible) {
        
        window.draw(winScreenBackground);
        window.draw(victoryTextSprite);
        window.draw(winnerTextSprite);
        window.draw(closeVictoryScreenBtnSprite);

        currentPlayer == Piece::Type::BLACK ? window.draw(playerWinnerSpriteWhite) : window.draw(playerWinnerSpriteBlack);
    };

    window.display();
}
