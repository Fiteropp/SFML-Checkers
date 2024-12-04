class Piece
{
public:
	enum Type { NONE, BLACK, WHITE };

	Type type;
	bool isKing;

	Piece(Type t = NONE, bool king = false) : type(t), isKing(king) {};
};