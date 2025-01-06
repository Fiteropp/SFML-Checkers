#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

class Game {
private:
        Board board;
    sf::RectangleShape stopButton2;
    sf::RectangleShape restartButton;
    sf::RectangleShape playBtn;
    sf::Sprite playBtnSprite;
    bool isPlayButtonVisible = true;  
    bool isGameOver;
    sf::RectangleShape logo;
    void processInput();
    void update();
    void render();
    void hideMenu();

public:
    sf::RenderWindow window;      

    Piece::Type currentPlayer;

    Game();
    void run();
    void stopGame();  
    void restartGame();
};
