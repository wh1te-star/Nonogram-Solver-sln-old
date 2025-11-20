#include "Board/Board/Board.h"

#include <typeinfo>
#include <cassert>
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

Row Board::getRowLine(RowIndex rowIndex) const {
	std::vector<Cell> row;
	for (ColumnIndex columnIndex : ColumnIndex::iterate(0, columnLength.getLength())) {
		Coordinate coordinate = Coordinate(rowIndex, columnIndex);
		Cell cell = getCell(coordinate);
		row.push_back(cell);
	}
	return Row(row);
}

Column Board::getColumnLine(ColumnIndex columnIndex) const {
	std::vector<Cell> column;
	for (RowIndex rowIndex : RowIndex::iterate(0, rowLength.getLength())) {
		Coordinate coordinate = Coordinate(rowIndex, columnIndex);
		Cell cell = getCell(coordinate);
		column.push_back(cell);
	}
	return Column(column);
}

bool Board::isInRange(Coordinate coordinate) const {
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

bool Board::isSolved() const {
	for (std::vector<Cell> row : board) {
		for (Cell cell : row) {
			if (cell.getColor() == None) {
				return false;
			}
		}
	}
	return true;
}

void Board::applyCell(Coordinate coordinate, const Cell& cell) {
    if(!isInRange(coordinate)) {
        return;
    }

    RowIndex rowIndex = coordinate.getRowIndex();
    ColumnIndex columnIndex = coordinate.getColumnIndex();
	board[rowIndex.getIndex()][columnIndex.getIndex()] = cell;
}

void Board::applyRow(RowIndex rowIndex, const Row& row) {
	assert(row.size() == columnLength.getLength());

	for (ColumnIndex columnIndex : ColumnIndex::iterate(0, row.size())) {
		Coordinate coordinate = Coordinate(rowIndex, columnIndex);
		Cell cell = row[columnIndex];
		applyCell(coordinate, cell);
	}
}

void Board::applyRow(RowIndex rowIndex, const RowPlacement& rowPlacement) {
	assert(rowPlacement.size() == columnLength.getLength());

	for (ColumnIndex columnIndex : ColumnIndex::iterate(0, rowPlacement.size())) {
		Coordinate coordinate = Coordinate(rowIndex, columnIndex);
		Cell cell = rowPlacement[columnIndex];
		applyCell(coordinate, cell);
	}
}

void Board::applyColumn(ColumnIndex columnIndex, const Column& column) {
	assert(column.size() == rowLength.getLength());

	for (RowIndex rowIndex : RowIndex::iterate(0, column.size())) {
		Coordinate coordinate = Coordinate(rowIndex, columnIndex);
		Cell cell = column[rowIndex];
		applyCell(coordinate, cell);
	}
}

void Board::applyColumn(ColumnIndex columnIndex, const ColumnPlacement& columnPlacement) {
	assert(columnPlacement.size() == rowLength.getLength());

	for (RowIndex rowIndex : RowIndex::iterate(0, columnPlacement.size())) {
		Coordinate coordinate = Coordinate(rowIndex, columnIndex);
		Cell cell = columnPlacement[rowIndex];
		applyCell(coordinate, cell);
	}
}

