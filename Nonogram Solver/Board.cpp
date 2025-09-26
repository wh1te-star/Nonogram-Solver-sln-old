#include <typeinfo>
#include "Board.h"
#include "RowPlacement.h"
#include "ColumnPlacement.h"
#include <cassert>

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

std::vector<Cell>& Board::operator[](RowIndex rowIndex) {
    return board[rowIndex.getIndex()];
}

const std::vector<Cell>& Board::operator[](RowIndex rowIndex) const {
    return board[rowIndex.getIndex()];
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
		colorCell(cellLocation.getCoordinate(), cellLocation.getCell().get());
	}
}

