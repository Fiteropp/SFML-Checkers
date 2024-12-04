#ifndef BOARD_H
#define BOARD_H

class Board {
private:
	Piece board[8][8];
	void initializeBoard();
public:
	Board();

	bool isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer);
	bool movePiece(int startX, int startY, int endX, int endY, Piece::Type currentPlayer);
	void render(sf::RenderWindow& window);

};

#endif