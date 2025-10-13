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

bool Board::operator==(const Board& other) const {
	return board == other.board;
}

bool Board::operator!=(const Board& other) const {
	return !(*this == other);
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

bool Board::isInRange(const Coordinate& coordinate) const {
	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();
	if (columnIndex < ColumnLength(0) || columnLength <= columnIndex) {
		return false;
	}
	if(rowIndex < RowLength(0) || rowLength < rowIndex) {
		return false;
	}
	return true;
}

void Board::applyCell(const Coordinate& coordinate, const CellColor& cellColor) {
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

void Board::applyPlacement(const Coordinate& coordinate, const Placement& placement) {
	assert(
		typeid(placement) == typeid(RowPlacement) ||
		typeid(placement) == typeid(ColumnPlacement)
	);

	for(const CellLocation& cellLocation : placement.getCellLocationList()) {
		applyCell(cellLocation.getCoordinate(), cellLocation.getCell().getColor());
	}
}

void Board::applyBoard(const Coordinate& coordinate, const Board& board) {
	RowIndex startRowIndex = coordinate.getRowIndex();
	ColumnIndex startColumnIndex = coordinate.getColumnIndex();
	RowLength boardRowLength = board.getRowLength();
	ColumnLength boardColumnLength = board.getColumnLength();
	for(int i = 0; i < boardRowLength.getLength(); i++) {
		for(int j = 0; j < boardColumnLength.getLength(); j++) {
			Coordinate cellCoordinate(
				startRowIndex + RowIndex(i),
				startColumnIndex + ColumnIndex(j)
			);
			Cell cell = board.getBoard()[i][j];
			applyCell(cellCoordinate, cell.getColor());
		}
	}
}
