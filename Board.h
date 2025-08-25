#include "Tile.h"
#include <vector>

class Board
{
private:
    std::vector<std::vector<Tile>> chessboard;

public:
    Board();
    ~Board();
};
