#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
    enum class Type {
        NONE,
        WHITE,
        BLACK
    };

    Type type;
    bool isKing;
    
    bool isPieceKing() const;
    void promoteToKing();



    // Constructor
    Piece(Type type = Type::NONE, bool isKing = false)
        : type(type), isKing(isKing) {
    }
    };

#endif
