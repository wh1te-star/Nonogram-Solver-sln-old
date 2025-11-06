#include "Board/Board/Board.h"

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
	: rowLength(std::move(rowLength)),
	columnLength(std::move(columnLength)) {
	board.resize(
		rowLength.getLength(),
		std::vector<Cell>(
			columnLength.getLength(),
			Cell()
		)
	);
}

const RowLength& Board::getRowLength() const {
	return rowLength;
}

const ColumnLength& Board::getColumnLength() const {
	return columnLength;
}

const CellVector2D& Board::getBoard() const {
	return board;
}

bool Board::operator==(const Board& other) const {
	return board == other.board;
}

bool Board::operator!=(const Board& other) const {
	return !(*this == other);
}

bool Board::isInRange(const Coordinate& coordinate) const {
	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();
	if (columnIndex < ColumnLength(0) || columnLength <= columnIndex) {
		return false;
	}
	if(rowIndex < RowLength(0) || rowLength <= rowIndex) {
		return false;
	}
	return true;
}

const Cell& Board::getCell(const Coordinate& coordinate) const {
	assert(isInRange(coordinate));
	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();
	return board[rowIndex.getIndex()][columnIndex.getIndex()];
}

void Board::applyCell(const Coordinate& coordinate, const Cell& cell) {
    if(!isInRange(coordinate)) {
        return;
    }

    RowIndex rowIndex = coordinate.getRowIndex();
    ColumnIndex columnIndex = coordinate.getColumnIndex();
	board[rowIndex.getIndex()][columnIndex.getIndex()] = cell;
}

void Board::applyPlacement(const Coordinate& coordinate, const Placement& placement) {
	assert(
		typeid(placement) == typeid(RowPlacement) ||
		typeid(placement) == typeid(ColumnPlacement)
	);

	for(const CellLocation& cellLocation : placement.getCellLocationList(coordinate)) {
		applyCell(cellLocation.getCoordinate(), cellLocation.getCell());
	}
}
