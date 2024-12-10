#include "Board.h"
#include "Piece.h"
#include "SFML/Graphics.hpp"
#include <iostream> // For debugging

sf::Texture whitePieceTexture;
sf::Texture blackPieceTexture;
sf::Texture whiteKingTexture;
sf::Texture blackKingTexture;

Board::Board() {
	initializeBoard();
}

//Place Pieces
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
};

bool Board::isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) {
	//Check if start and end coordinates are valid
	if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
		endX < 0 || endX >= 8 || endY < 0 || endY >= 8) 
		return false;

	//Get piece moving
	Piece piece = board[startY][startX];
	if (piece.type == Piece::NONE || piece.type != currentPlayer)
		return false;

	//Check if destination is empty
	if (board[startY][startX].type = Piece::NONE)
		return false;

	//Calculate distances
	int dx = abs(endX - startX); //Horizontal
	int dy = abs(endY - startY); //Vertical

	if (dx == 1 && dy == 1) {
		//Normal pieces may only move forward
		if (!piece.isKing && ((currentPlayer == Piece::BLACK && endY <= startY) ||
							  (currentPlayer == Piece::WHITE && endY >= startY)))
			return false;
		return false;
	}

	if (dx == 2 && dy == 2) {
		int midX = (startX + endX) / 2;
		int midY = (startY + endY) / 2;

		Piece midPiece = board[midY][midX];
		if (midPiece.type == Piece::NONE || midPiece.type == currentPlayer)
			return false; //No piece or own piece
		
		return true;
	}

	return false; //Invalid move


};

bool Board::movePiece(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) {
	if (!isValidMove(startX, startY, endX, endY, currentPlayer))
		return false;

	//Move the Piece
	board[endY][endX] = board[startY][startX];
	board[startY][startX] = Piece(Piece::NONE);

	if (abs(endX- startX) == 2) {
		int midX = (startX + endX) / 2;
		int midY = (startY + endY) / 2;
		board[midY][midX] = Piece(Piece::NONE); // Remove captured piece
	}

	if ((currentPlayer == Piece::BLACK && endY == 7) || (currentPlayer == Piece::WHITE && endY == 0)) {
		board[endY][endX].isKing = true;
	}
	return true;
};

void Board::loadTextures() {
	//Load textures from files
	whitePieceTexture.loadFromFile("textures/white.png");
	blackPieceTexture.loadFromFile("textures/black.png");
	whiteKingTexture.loadFromFile("textures/white_king.png");
	blackKingTexture.loadFromFile("textures/black_king.png");
};

void Board::render(sf::RenderWindow& window) {
	const float tileSize = 50.0f; //Tile sizing

	//Draw the board
	for (int y = 8; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			//Draw board tiles
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			tile.setPosition(x * tileSize, y * tileSize);

			if ((x + y) % 2 == 0) {
				tile.setFillColor(sf::Color(172, 199, 216)); // Light tile
			}
			else {
				tile.setFillColor(sf::Color(75, 79, 88)); // Dark tile
			}
			window.draw(tile);

			//Draw pieces
			Piece piece = board[y][x];
			if (piece.type != Piece::NONE) {
				sf::Sprite pieceSprite;

				if (piece.type == Piece::WHITE) {
					pieceSprite.setTexture(piece.isKing ? whiteKingTexture : whitePieceTexture);
				}
				else if (piece.type == Piece::BLACK) {
					pieceSprite.setTexture(piece.isKing ? blackKingTexture : blackPieceTexture);
				}

				//Pos sprite
				pieceSprite.setPosition(x * tileSize, y * tileSize);

				//Scale if needed
				pieceSprite.setScale(tileSize / pieceSprite.getLocalBounds().width,
					tileSize / pieceSprite.getLocalBounds().height);

				window.draw(pieceSprite);
			}
			}
				

			
	}
};

void Board::handleClick(int gridX, int gridY, Piece::Type currentPlayer) {
	static bool pieceSelected = false;
	static int selectedX = -1, selectedY = -1;

	if (!pieceSelected) {
		//Attempt o move selected piece to destination
		if (board[gridY][gridX].type == currentPlayer) {
			pieceSelected = true;
			selectedX = gridX;
			selectedY = gridY;
			std::cout << "Piece selected at (" << selectedX << ", " << selectedY << ")\n";
		}
		else {

		}
	}
}


	
