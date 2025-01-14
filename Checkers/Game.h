#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

class Game {
private:
        Board board;
    sf::RectangleShape menuBackground;
    sf::RectangleShape winScreenBackground;
    sf::Sprite playBtnSprite;
    bool isMenuVisible = true;  
    bool victoryScreenVisible = false;
    bool isGameOver;
    

    bool loadTexture(const std::string& filePath, sf::Texture& texture);
    void configureSprite(sf::Sprite& sprite, sf::Texture& texture, sf::Vector2f position = { 0, 0 }, sf::Vector2f scale = { 1.0f, 1.0f });
    void processInput();
    void update();
    void render();
    void hideMenu();

public:
    sf::RenderWindow window;      

    Piece::Type currentPlayer;

    Game();
    void loadButtonsTextures();
    void run();
    void stopGame();  
    void restartGame();
};
