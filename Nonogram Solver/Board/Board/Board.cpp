#include <typeinfo>
#include <cassert>
#include "Board.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Board/BoardLength/RowLength.h"
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"
#include "Index/CellIndex/RowIndex.h"
#include "Placement/Placement/ColumnPlacement.h"
#include "Placement/Placement/RowPlacement.h"

Board::Board(RowLength rowLength, ColumnLength columnLength)
	: rowLength(rowLength), columnLength(columnLength) {
	board.resize(rowLength.getLength(), std::vector<Cell>(columnLength.getLength(), Cell()));
}

bool Board::operator==(const Board& other) const {
	return board == other.board;
}

bool Board::operator!=(const Board& other) const {
	return !(*this == other);
}

RowLength Board::getRowLength() const {
	return rowLength;
}

ColumnLength Board::getColumnLength() const {
	return columnLength;
}

Cell Board::getCell(Coordinate coordinate) const {
	assert(isInRange(coordinate));
	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();
	return board[rowIndex.getIndex()][columnIndex.getIndex()];
}

ColumnIndex Board::leftMostColumnIndex() const {
	return ColumnIndex(0);
}

ColumnIndex Board::rightMostColumnIndex() const {
	return ColumnIndex(columnLength.getLength() - 1);
}

RowIndex Board::topMostRowIndex() const {
	return RowIndex(0);
}

RowIndex Board::bottomMostRowIndex() const {
	return RowIndex(rowLength.getLength() - 1);
}

bool Board::isInRange(Coordinate coordinate) const {
	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();
	if (columnIndex < leftMostColumnIndex() || rightMostColumnIndex() < columnIndex) {
		return false;
	}
	if(rowIndex < topMostRowIndex() || bottomMostRowIndex() < rowIndex) {
		return false;
	}
	return true;
}

void Board::colorCell(Coordinate coordinate, CellColor cellColor) {
	if(!isInRange(coordinate)) {
		return;
	}

	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();
	Cell& cell = board[rowIndex.getIndex()][columnIndex.getIndex()];
	if (cell.canColor(cellColor)) {
		cell = Cell(cellColor);
	}
}

void Board::applyPlacement(Coordinate coordinate, Placement& placement) {
	assert(
		typeid(placement) == typeid(RowPlacement) ||
		typeid(placement) == typeid(ColumnPlacement)
	);

	for(CellLocation cellLocation : placement.getCellLocationList()) {
		colorCell(cellLocation.getCoordinate(), cellLocation.getCell().getColor());
	}
}

