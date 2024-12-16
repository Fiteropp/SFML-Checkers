#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <SFML/Graphics.hpp>

class Game;

class Board {
private:
    Piece board[8][8];
    void initializeBoard();
    Game* gameInstance;

public:
    Board();

    bool isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const;
    bool movePiece(int startX, int startY, int endX, int endY, Piece::Type currentPlayer);
    void handleClick(int gridX, int gridY, Piece::Type& currentPlayer);
    void render(sf::RenderWindow& window);
    void switchPlayer();
    void loadTextures();
    bool checkWinCondition(Piece::Type currentPlayer) const;
};

#endif
