#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Cell/Cell/Cell.h"
#include "Cell/CellColor/CellColor.h"
#include "Index/Coordinate/Coordinate.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Index/CellIndex/RowIndex.h"
#include "Placement/Placement/Placement.h"

class Board {
private:
	RowLength rowLength;
	ColumnLength columnLength;
	std::vector<std::vector<Cell>> board;

public:
	Board(RowLength rowLength, ColumnLength columnLength);

	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const;

	RowLength getRowLength() const;
	ColumnLength getColumnLength() const;
	Cell getCell(Coordinate coordinate) const;
	void setCell(Coordinate coordinate, Cell cell);
	
	bool isInRange(Coordinate coordinate) const;
	void colorCell(Coordinate coordinate, CellColor cellColor);
	void applyPlacement(Coordinate coordinate, Placement& placement);
};


#endif
