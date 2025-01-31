#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <SFML/Graphics.hpp>

class Game;

class Board {
private:
    sf::RectangleShape whiteSquare;  
    sf::RectangleShape stopButton;
    sf::RectangleShape restartButton;
    sf::RectangleShape chosenChecker;
    
    bool pieceSelected;
    int selectedX;
    int selectedY;

    bool captureMade;

    Piece board[8][8];
    
    Game* gameInstance;

	

public:
    Board(Game* game);

    void initializeBoard();

    bool isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const;
    bool movePiece(int startX, int startY, int endX, int endY, Piece::Type currentPlayer);
    bool isValidKingMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const;
    bool isDiagonalMove(int startX, int startY, int endX, int endY) const;
    bool canContinueTurn(int gridX, int gridY);
    void handleClick(int gridX, int gridY, Piece::Type& currentPlayer);
    void render(sf::RenderWindow& window);
    void switchPlayer();
    void loadTextures();
    bool checkWinCondition(Piece::Type currentPlayer);


    int whitePieceWinsCounter;
    int blackPieceWinsCounter;
    int whitePieceMoveCounter;
    int blackPieceMoveCounter;
};

#endif
