#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "CellState.h"
#include "Coordinate.h"
#include "Line.h"

class Board {
private:
	std::vector<std::vector<CellState>> board;

public:
	Board(int rows, int cols);
	~Board();

	Board fillCell(Coordinate coordinate, CellState cellState);
	Board fillLine(Coordinate coordinate, Line line);

	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const;
};


#endif
