#include "Piece.h"


// Checks if the piece is a king
bool Piece::isPieceKing() const {
    return isKing;
}

// Promotes the piece to a king
void Piece::promoteToKing() {
    isKing = true;
}
