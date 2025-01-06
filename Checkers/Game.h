#pragma once
#include "SFML/Graphics.hpp"
#include "Board.h"
#include "Piece.h"
#include "Player.h"

class Game {
private:
    Board board;

    // Buttons
    sf::RectangleShape stopButton;
    sf::RectangleShape restartButton;

    bool isGameOver;

    void processInput();
    void update();
    void render();

public:
    sf::RenderWindow window;
    Piece::Type currentPlayer;

    Game();
    void run();
    void stopGame();  // Stop the game
    void restartGame(); // Restart the game
};
