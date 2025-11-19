#include "Board/NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintSetList rowHintSetList,
		ColumnHintSetList columnHintSetList
) : board(std::move(board)),
    rowHintSetList(std::move(rowHintSetList)),
    columnHintSetList(std::move(columnHintSetList)) {}

const Board& NonogramBoard::getBoard() const {
	return board;
}

const RowLength& NonogramBoard::getRowCount() const {
	return board.getRowLength();
}

const ColumnLength& NonogramBoard::getColumnCount() const {
	return board.getColumnLength();
}

const RowHintSetList& NonogramBoard::getRowHintSetList() const {
	return rowHintSetList;
}

const ColumnHintSetList& NonogramBoard::getColumnHintSetList() const {
	return columnHintSetList;
}

Row NonogramBoard::getRowLine(RowIndex rowIndex) const {
	return board.getRowLine(rowIndex);
}

Column NonogramBoard::getColumnLine(ColumnIndex columnIndex) const {
	return board.getColumnLine(columnIndex);
}

HintSet NonogramBoard::getRowHintSet(RowIndex rowIndex) const {
	return rowHintSetList[rowIndex];
}

HintSet NonogramBoard::getColumnHintSet(ColumnIndex columnIndex) const {
	return columnHintSetList[columnIndex];
}

bool NonogramBoard::isSolved() const {
	return board.isSolved();
}

void NonogramBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	board.applyCell(coordinate, cell);
}

void NonogramBoard::applyRow(const RowIndex& rowIndex, const Row& row) {
	return board.applyRow(rowIndex, row);
}

void NonogramBoard::applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement) {
	return board.applyRow(rowIndex, rowPlacement);
}

void NonogramBoard::applyColumn(const ColumnIndex& columnIndex, const Column& column) {
	return board.applyColumn(columnIndex, column);
}

void NonogramBoard::applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement) {
	return board.applyColumn(columnIndex, columnPlacement);
}
