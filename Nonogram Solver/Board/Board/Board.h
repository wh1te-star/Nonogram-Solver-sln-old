#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Cell/CellVector2D/CellVector2D.h"
#include "Cell/CellColor/CellColor.h"
#include "Index/Coordinate/Coordinate.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Index/CellIndex/RowIndex.h"
#include "Placement/Placement/Placement.h"

class Board {
private:
	RowLength rowLength;
	ColumnLength columnLength;
	CellVector2D board;

public:
	Board(RowLength rowLength, ColumnLength columnLength);

public:
	const RowLength& getRowLength() const;
	const ColumnLength& getColumnLength() const;
	const CellVector2D& getBoard() const;
	
public:
	bool operator==(const Board& other) const;
	bool operator!=(const Board& other) const;

public:
	bool isInRange(const Coordinate& coordinate) const;
	const Cell& getCell(const Coordinate& coordinate) const;

public:
	void applyCell(const Coordinate& coordinate, const Cell& cellColor);
	void applyPlacement(const Coordinate& coordinate, const Placement& placement);
};


#endif
