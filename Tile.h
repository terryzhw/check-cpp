class Tile
{
private:
    int sideOccupied; // 0 no side, 1 white, 2 black
    int pieceOccupied; // 0 no piece, 1 pawn, 2 bishop, 3 knight, 4 rook, 5 queen, 6 king
public:
    Tile();
    ~Tile();
    int getSideOccupied() const;
    int getPieceOccupied() const;
};
