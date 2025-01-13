#include "Board.h"
#include "Game.h"
#include "Piece.h"
#include "SFML/Graphics.hpp"
#include <iostream> // For debugging


sf::Texture whitePieceTexture;
sf::Texture blackPieceTexture;
sf::Texture whiteKingTexture;
sf::Texture blackKingTexture;

sf::Texture currentPlayerTexture;
sf::Sprite currentPlayerSprite;

sf::Texture whitePlayerSquareTexture;
sf::Texture blackPlayerSquareTexture;



Board::Board(Game* game) : gameInstance(game) {
	
const float tileSize = 75.0f;

	initializeBoard(); 
}


//Place Pieces
void Board::initializeBoard() {
	std::cout << "Initializing board...\n";
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			if (y < 3 && (x + y) % 2 != 0) {
				board[y][x] = Piece(Piece::Type::BLACK);
			}
			else if (y > 4 && (x + y) % 2 != 0) {
				board[y][x] = Piece(Piece::Type::WHITE);
			}
			else {
				board[y][x] = Piece(Piece::Type::NONE);
			}
		}
	}
};


bool Board::isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const {

	if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
		endX < 0 || endX >= 8 || endY < 0 || endY >= 8)
		return false;

	
	Piece piece = board[startY][startX];
	if (piece.type == Piece::Type::NONE || piece.type != currentPlayer) {
		return false;
	}


	
	if (board[startY][startX].type == Piece::Type::NONE) {
		return false;
	}


	int dx = abs(endX - startX); 
	int dy = abs(endY - startY); 

	if (board[startY][startX].isKing && isValidKingMove(startX, startY, endX, endY, currentPlayer)) {
		return true;
	}


	if (dx == 1 && dy == 1) {

		
		if (board[endY][endX].type != Piece::Type::NONE)
			return false;

		
		if (!piece.isKing && ((currentPlayer == Piece::Type::BLACK && endY <= startY) ||
			(currentPlayer == Piece::Type::WHITE && endY >= startY)))
			return false;
		return true;
	}

	if (dx == 2 && dy == 2) {
		
		if (board[endY][endX].type != Piece::Type::NONE)
			return false;

		int midX = (startX + endX) / 2;
		int midY = (startY + endY) / 2;

		Piece midPiece = board[midY][midX];
		if (midPiece.type == Piece::Type::NONE || midPiece.type == currentPlayer)

			return false;

		return true;
	}

	return false; 
};


bool Board::isValidKingMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const {
	if (!isDiagonalMove(startX, startY, endX, endY)) {
		return false;
	}

	int dx = (endX - startX) > 0 ? 1 : -1;
	int dy = (endY - startY) > 0 ? 1 : -1;

	int currentX = startX + dx;
	int currentY = startY + dy;
	bool hasCaptured = false;

	while (currentX != endX && currentY != endY) {
		const Piece& currentPiece = board[currentY][currentX];

		if (currentPiece.type != Piece::Type::NONE) {
			if (currentPiece.type == currentPlayer || hasCaptured) {
				return false; 
			}
			hasCaptured = true;
		}

		currentX += dx;
		currentY += dy;
	}

	return board[endY][endX].type == Piece::Type::NONE;
}


bool Board::isDiagonalMove(int startX, int startY, int endX, int endY) const {
	return abs(endX - startX) == abs(endY - startY);
}



bool Board::movePiece(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) {
	if (!isValidMove(startX, startY, endX, endY, currentPlayer))
		return false;

	// Move the Piece
	board[endY][endX] = board[startY][startX];
	board[startY][startX] = Piece(Piece::Type::NONE);

	if (abs(endX - startX) == 2) {
		int midX = (startX + endX) / 2;
		int midY = (startY + endY) / 2;
		board[midY][midX] = Piece(Piece::Type::NONE); 
	}
	else if (board[endY][endX].isKing) {
		
		int dx = (endX - startX) > 0 ? 1 : -1;
		int dy = (endY - startY) > 0 ? 1 : -1;
		int currentX = startX + dx;
		int currentY = startY + dy;

		while (currentX != endX && currentY != endY) {
			if (board[currentY][currentX].type != Piece::Type::NONE && board[currentY][currentX].type != currentPlayer) {
				board[currentY][currentX] = Piece(Piece::Type::NONE); 
				break;
			}
			currentX += dx;
			currentY += dy;
		}
	}

	if ((currentPlayer == Piece::Type::BLACK && endY == 7) || (currentPlayer == Piece::Type::WHITE && endY == 0)) {
		board[endY][endX].isKing = true;
	};
	
	return true;

}


void Board::switchPlayer() {
	if (gameInstance->currentPlayer == Piece::Type::WHITE) {
		gameInstance->currentPlayer = Piece::Type::BLACK;
		std::cout << "Current Checkers Color = Black\n";
	}
	else {
		gameInstance->currentPlayer = Piece::Type::WHITE;
		std::cout << "Current Checkers Color = White\n";
	}
}


bool Board::canContinueTurn(int gridX, int gridY ) {
	int directions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} }; 
	bool canContinue = false;

	for (int i = 0; i < 4; i++) {
		int midX = gridX + directions[i][0];
		int midY = gridY + directions[i][1];
		int endX = gridX + 2 * directions[i][0];
		int endY = gridY + 2 * directions[i][1];

		// Check if mid and end positions are valid
		if (midX >= 0 && midX < 8 && midY >= 0 && midY < 8 &&
			endX >= 0 && endX < 8 && endY >= 0 && endY < 8) {

			Piece midPiece = board[midY][midX];
			

			
			if (midPiece.type != Piece::Type::NONE && 
				midPiece.type != gameInstance->currentPlayer && 
				board[endY][endX].type == Piece::Type::NONE) { 
				canContinue = true;
				break; 
			}
		}
	}

	if (canContinue) {
		std::cout << "Player can continue their turn.\n";
		return true;
	}
	else {
		std::cout << "Turn over, no valid moves.\n";
		return false;
	}
}


void Board::loadTextures() {
	//Load textures from files
	whitePieceTexture.loadFromFile("textures/white.png");
	blackPieceTexture.loadFromFile("textures/black.png");
	whiteKingTexture.loadFromFile("textures/white_king.png");
	blackKingTexture.loadFromFile("textures/black_king.png");


	if (!whitePlayerSquareTexture.loadFromFile("textures/white_king.png")) {
		std::cout << "failed to load white player square  " << std::endl;
	}
	

	if (!blackPlayerSquareTexture.loadFromFile("textures/black_king.png")) {
		std::cout << "failed to load black player square texture" << std::endl;
	}

};


void Board::render(sf::RenderWindow& window) {
	
	const float tileSize = 75.0f; 

	// Draw the board
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			// Draw board tiles
			sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
			tile.setPosition(x * tileSize, y * tileSize);

			if ((x + y) % 2 == 0) {
				tile.setFillColor(sf::Color(172, 199, 216)); // Light tile
			}
			else {
				tile.setFillColor(sf::Color(75, 79, 88)); // Dark tile
			}
			window.draw(tile);

			// Draw pieces
			Piece piece = board[y][x];
			if (piece.type != Piece::Type::NONE) {
				sf::Sprite pieceSprite;

				if (piece.type == Piece::Type::WHITE) {
					pieceSprite.setTexture(piece.isKing ? whiteKingTexture : whitePieceTexture);
				}
				else if (piece.type == Piece::Type::BLACK) {
					pieceSprite.setTexture(piece.isKing ? blackKingTexture : blackPieceTexture);
				}

				// Set sprite position
				pieceSprite.setPosition(x * tileSize, y * tileSize);

				// Scale sprite if needed
				pieceSprite.setScale(tileSize / pieceSprite.getLocalBounds().width,
					tileSize / pieceSprite.getLocalBounds().height);

				window.draw(pieceSprite);
			}
		}
	}

	if (gameInstance->currentPlayer == Piece::Type::WHITE) {
		currentPlayerSprite.setTexture(whitePlayerSquareTexture);
	}
	else {
		currentPlayerSprite.setTexture(blackPlayerSquareTexture);
	}

	currentPlayerSprite.setPosition(650, 220);
	currentPlayerSprite.setScale(7.0f, 7.0f);

	window.draw(currentPlayerSprite);
};



void Board::handleClick(int gridX, int gridY, Piece::Type& currentPlayer) {
	static bool pieceSelected = false;
	static int selectedX = -1, selectedY = -1;


	// Handle piece selection and movement if the button is not clicked
	if (!pieceSelected) {
		// Select piece
		if (board[gridY][gridX].type == currentPlayer) {
			pieceSelected = true;
			selectedX = gridX;
			selectedY = gridY;
			std::cout << "Piece selected at (" << selectedX << ", " << selectedY << ")\n";
		}
		else {
			std::cout << "No piece to select at (" << gridX << ", " << gridY << ")\n";
		}
	}
	else {
		// Try to move selected piece
		if (isValidMove(selectedX, selectedY, gridX, gridY, currentPlayer)) {
			movePiece(selectedX, selectedY, gridX, gridY, currentPlayer);
			std::cout << "Moved piece to (" << gridX << ", " << gridY << ")\n";

			// Switch player after a valid move
			if (canContinueTurn(gridX, gridY)) {
				return;
			};
			currentPlayer = (currentPlayer == Piece::Type::BLACK) ? Piece::Type::WHITE : Piece::Type::BLACK;
			std::cout << "It's now " << (currentPlayer == Piece::Type::BLACK ? "Black" : "White") << "'s turn\n";
		}
		else {
			std::cout << "Invalid move\n";
		}

		// Reset selection
		pieceSelected = false;
		selectedX = -1;
		selectedY = -1;
	}
}


bool Board::checkWinCondition(Piece::Type currentPlayer) const {
	int whitePieces = 0;
	int blackPieces = 0;
	bool canMove = false;

	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			const Piece& piece = board[y][x];

			// Count the number of pieces for each player
			if (piece.type == Piece::Type::WHITE) {
				whitePieces++;
			}
			else if (piece.type == Piece::Type::BLACK) {
				blackPieces++;
			}

			// Check if the current player's pieces can make a move
			if (piece.type == currentPlayer) {
				for (int dy = -1; dy <= 1; ++dy) {
					for (int dx = -1; dx <= 1; ++dx) {
						if (dx == 0 || dy == 0) continue;

						int newX = x + dx;
						int newY = y + dy;

						if (isValidMove(x, y, newX, newY, currentPlayer)) {
							canMove = true;
							break;
						}
					}
					if (canMove) break;
				}
			}
		}
	}

	if (currentPlayer == Piece::Type::WHITE) {
		return blackPieces == 0 || !canMove;
	}
	else {
		return whitePieces == 0 || !canMove;
	}
}