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
	

	initializeBoard(); // Initialize the board

	// Initialize the white square
	whiteSquare.setSize(sf::Vector2f(tileSize, tileSize));  // Set the size of the square
	whiteSquare.setFillColor(sf::Color::White);        // Set the color to white

	// Position the square next to the board (to the right)
	float centerY = (8 * tileSize) / 2 - tileSize / 2;  // Calculate the center Y position of the board
	float nextToBoardX = 8 * tileSize + 175;       // Position to the right of the board, with an offset of 50
	whiteSquare.setPosition(320, 328);


	
	
	
	
	


	
	
	// Position next to the board
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

void Board::resetBoard() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if ((i + j) % 2 != 0) { // Only place pieces on black squares
				if (i < 3) {
					board[i][j] = Piece(Piece::Type::BLACK, false); // Black pieces, no coords
				}
				else if (i > 4) {
					board[i][j] = Piece(Piece::Type::WHITE, false); // White pieces, no coords
				}
				else {
					board[i][j] = Piece(Piece::Type::NONE, false); // Empty squares
				}
			}
			else {
				board[i][j] = Piece(Piece::Type::NONE, false); // Empty squares
			}
		}
	}
}

void Board::resGame() {
	// Reinitialize the board
	initializeBoard();

	// Reset any other necessary game state, e.g., currentPlayer
	gameInstance->currentPlayer = Piece::Type::WHITE;  // Example reset

	// Optionally, print something to debug
	std::cout << "Game Restarted!" << std::endl;
}



void Board::handleButtonClick(int x, int y) {
	
	
	std::cout << "Mouse click at: " << x << ", " << y << std::endl;

	
}



bool Board::isValidMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const {
	//Check if start and end coordinates are valid
	if (startX < 0 || startX >= 8 || startY < 0 || startY >= 8 ||
		endX < 0 || endX >= 8 || endY < 0 || endY >= 8)
		return false;

	//Get piece moving
	Piece piece = board[startY][startX];
	if (piece.type == Piece::Type::NONE || piece.type != currentPlayer) {
		std::cout << "Invalid piece selected\n";
		return false;
	}


	//Check if destination is empty
	if (board[startY][startX].type == Piece::Type::NONE) {
		std::cout << "Destination is empty\n";
		return false;
	}


	//Calculate distances
	int dx = abs(endX - startX); //Horizontal
	int dy = abs(endY - startY); //Vertical

	if (board[startY][startX].isKing && isValidKingMove(startX, startY, endX, endY, currentPlayer)) {
		return true;
	}


	if (dx == 1 && dy == 1) {

		//Check if destination is empty
		if (board[endY][endX].type != Piece::Type::NONE)
			return false;

		//Normal pieces may only move forward
		if (!piece.isKing && ((currentPlayer == Piece::Type::BLACK && endY <= startY) ||
			(currentPlayer == Piece::Type::WHITE && endY >= startY)))
			return false;
		return true;
	}

	if (dx == 2 && dy == 2) {
		//Check if destination is empty
		if (board[endY][endX].type != Piece::Type::NONE)
			return false;

		int midX = (startX + endX) / 2;
		int midY = (startY + endY) / 2;

		Piece midPiece = board[midY][midX];
		if (midPiece.type == Piece::Type::NONE || midPiece.type == currentPlayer)

			return false; //No piece or own piece

		return true;
	}

	return false; //Invalid move


};






bool Board::isValidKingMove(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) const {
	if (!isDiagonalMove(startX, startY, endX, endY)) {
		return false; // Not a valid diagonal move
	}

	int dx = (endX - startX) > 0 ? 1 : -1;
	int dy = (endY - startY) > 0 ? 1 : -1;

	int currentX = startX + dx;
	int currentY = startY + dy;

	while (currentX != endX && currentY != endY) {
		const Piece& currentPiece = board[currentY][currentX];

		if (currentPiece.type != Piece::Type::NONE) {
			return false; // Path is not clear, invalid move
		}

		currentX += dx;
		currentY += dy;
	}

	return board[endY][endX].type == Piece::Type::NONE; // Destination must be empty
}




bool Board::isDiagonalMove(int startX, int startY, int endX, int endY) const {
	return abs(endX - startX) == abs(endY - startY);
}


bool Board::movePiece(int startX, int startY, int endX, int endY, Piece::Type currentPlayer) {
	if (!isValidMove(startX, startY, endX, endY, currentPlayer))
		return false;

	//Move the Piece
	board[endY][endX] = board[startY][startX];
	board[startY][startX] = Piece(Piece::Type::NONE);

	if (abs(endX - startX) == 2) {
		int midX = (startX + endX) / 2;
		int midY = (startY + endY) / 2;
		board[midY][midX] = Piece(Piece::Type::NONE); // Remove captured piece
	}

	if ((currentPlayer == Piece::Type::BLACK && endY == 7) || (currentPlayer == Piece::Type::WHITE && endY == 0)) {
		board[endY][endX].isKing = true;
	}
	return true;
};

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


bool Board::canContinueTurn(int startX, int startY ) {
	int directions[4][2] = { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} }; // Diagonal directions
	bool canContinue = false;

	for (int i = 0; i < 4; i++) {
		int midX = startY + directions[i][0];
		int midY = startY + directions[i][1];
		int endX = startX + 2 * directions[i][0];
		int endY = startY + 2 * directions[i][1];

		// Check if mid and end positions are valid
		if (midX >= 0 && midX < 8 && midY >= 0 && midY < 8 &&
			endX >= 0 && endX < 8 && endY >= 0 && endY < 8) {

			Piece midPiece = board[midY][midX];
			

			// Check if mid position contains an opponent piece and end position is empty
			if (midPiece.type != Piece::Type::NONE && // Opponent's piece
				midPiece.type != gameInstance->currentPlayer && // Not current player's piece
				board[endY][endX].type == Piece::Type::NONE) { // End position is empty
				canContinue = true;
				break; // Exit loop if a valid continuation is found
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
		std::cout << "Failed to load white player square texture!" << std::endl;
	}
	else {
		std::cout << "White player square texture loaded successfully!" << std::endl;
	}

	if (!blackPlayerSquareTexture.loadFromFile("textures/black_king.png")) {
		std::cout << "Failed to load black player square texture!" << std::endl;
	}
	else {
		std::cout << "Black player square texture loaded successfully!" << std::endl;
	}


};

void Board::render(sf::RenderWindow& window) {
	const float tileSize = 75.0f; // Tile sizing
	const float offsetX = 60.0f; // Horizontal offset
	const float offsetY = 60.0f; // Vertical offset

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

	// Adjust the position and scale of the player square sprite
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
			if (canContinueTurn(selectedX, selectedY)) {
				handleClick(selectedX, selectedY, currentPlayer);
			}
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
	bool hasOpponentPieces = false;
	bool canMove = false;


	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			const Piece& piece = board[y][x];


			//Check if there are any opponent pieces remaining
			if (piece.type != Piece::Type::NONE && piece.type != currentPlayer) {
				hasOpponentPieces = true;
			}


			//Check if current player's pieces can make a move
			if (piece.type == currentPlayer) {
				//Check possible moves
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
				}
			}
		}
	}
	//Return GameOver if cant move or no pieces left
	return !hasOpponentPieces || !canMove;
}


	
