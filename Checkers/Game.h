#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

class Game {
private:
   
    Board board;

    bool isGameOver;

    void processInput();
    void update();
    void render();

public:
    sf::RenderWindow window;
    Piece::Type currentPlayer;

    Game();
    void run();
    void stopGame(); // Declare the stopGame method
};
