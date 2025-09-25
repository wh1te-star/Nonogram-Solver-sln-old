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

void Board::colorLine(Coordinate coordinate, Placement placement) {
	RowIndex rowIndex = coordinate.getRowIndex();
	ColumnIndex columnIndex = coordinate.getColumnIndex();

	/*
	if(typeid(placement) == typeid(RowPlacement)){
		if (row < 0 || row >= board.size()) {
			return;
		}
		for (int i = 0; i < placement.line.size(); ++i) {
			int colIdx = column + i;
			if (colIdx < 0 || colIdx >= board[0].size()) {
				continue;
			}
			if (board[row][colIdx].canColor(placement.line[i].get())) {
				board[row][colIdx] = placement.line[i];
			}
		}
	} else if (typeid(placement) == typeid(ColumnPlacement)) {
		if (column < 0 || column >= board[0].size()) {
			return;
		}
		for (int i = 0; i < placement.line.size(); ++i) {
			int rowIdx = row + i;
			if (rowIdx < 0 || rowIdx >= board.size()) {
				continue;
			}
			if (board[rowIdx][column].canColor(placement.line[i].get())) {
				board[rowIdx][column] = placement.line[i];
			}
		}
	}
	else {
		assert(false);
	}
	*/
}

