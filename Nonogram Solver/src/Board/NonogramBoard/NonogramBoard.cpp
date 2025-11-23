#include "Board/NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintSetList rowHintSetList,
		ColumnHintSetList columnHintSetList
) : board(std::move(board)),
    rowHintSetList(std::move(rowHintSetList)),
    columnHintSetList(std::move(columnHintSetList)) {}

RowLength NonogramBoard::getRowLength() const {
	return board.getRowLength();
}

ColumnLength NonogramBoard::getColumnLength() const {
	return board.getColumnLength();
}

Board NonogramBoard::getBoard() const {
	return board;
}

Cell NonogramBoard::getCell(Coordinate coordinate) const {
	return board.getCell(coordinate);
}

Row NonogramBoard::getRowLine(RowIndex rowIndex) const {
	return board.getRowLine(rowIndex);
}

Column NonogramBoard::getColumnLine(ColumnIndex columnIndex) const {
	return board.getColumnLine(columnIndex);
}

bool NonogramBoard::isInRange(Coordinate coordinate) const {
	return board.isInRange(coordinate);
}

bool NonogramBoard::isSolved() const {
	return board.isSolved();
}

void NonogramBoard::applyCell(Coordinate coordinate, const Cell& cell, bool overwriteNone) {
	board.applyCell(coordinate, cell, overwriteNone);
}

void NonogramBoard::applyRow(RowIndex rowIndex, const Row& row, bool overwriteNone) {
	return board.applyRow(rowIndex, row, overwriteNone);
}

void NonogramBoard::applyRow(RowIndex rowIndex, const RowPlacement& rowPlacement) {
	return board.applyRow(rowIndex, rowPlacement);
}

void NonogramBoard::applyColumn(ColumnIndex columnIndex, const Column& column, bool overwriteNone) {
	return board.applyColumn(columnIndex, column, overwriteNone);
}

void NonogramBoard::applyColumn(ColumnIndex columnIndex, const ColumnPlacement& columnPlacement) {
	return board.applyColumn(columnIndex, columnPlacement);
}

RowHintSetList NonogramBoard::getRowHintSetList() const {
	return rowHintSetList;
}

ColumnHintSetList NonogramBoard::getColumnHintSetList() const {
	return columnHintSetList;
}

