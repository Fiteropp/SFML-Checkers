#include "Board.h"
#include "Piece.h"
#include "SFML/Graphics.hpp"


Board::Board() {
	initializeBoard();
}

void Board::initializeBoard() {
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			if (y < 3 && (x + y) % 2 != 0) {
				board[y][x] = Piece(Piece::BLACK);
			}
			else if (y > 4 && (x + y) % 2 != 0) {
				board[y][x] = Piece(Piece::WHITE);
			}
			else {
				board[y][x] = Piece(Piece::NONE);
			}
		}
	}
}

bool Board::isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) {
	if (startX < 0 || startX >= 8 ||)
}
	
