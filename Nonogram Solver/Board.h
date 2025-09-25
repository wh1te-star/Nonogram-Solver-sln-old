#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Cell.h"
#include "Coordinate.h"
#include "Placement.h"
#include "RowLength.h"
#include "ColumnLength.h"

class Board {
private:
	RowLength rowLength;
	ColumnLength columnLength;
	std::vector<std::vector<Cell>> board;

public:
	Board(RowLength rowLength, ColumnLength columnLength);

	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const;
	std::vector<Cell>& operator[](RowIndex rowIndex);
	const std::vector<Cell>& operator[](RowIndex rowIndex) const;

	ColumnIndex leftMostColumnIndex() const;
	ColumnIndex rightMostColumnIndex() const;
	RowIndex topMostRowIndex() const;
	RowIndex bottomMostRowIndex() const;
	bool isInRange(Coordinate coordinate) const;
	void colorCell(Coordinate coordinate, CellColor cellColor);
	void colorLine(Coordinate coordinate, Placement placement);
};


#endif
