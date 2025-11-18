#include "Board/NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList
) : board(std::move(board)),
    rowHintLineList(std::move(rowHintLineList)),
    columnHintLineList(std::move(columnHintLineList)) {}

const Board& NonogramBoard::getBoard() const {
	return board;
}

const RowLength& NonogramBoard::getRowCount() const {
	return board.getRowLength();
}

const ColumnLength& NonogramBoard::getColumnCount() const {
	return board.getColumnLength();
}

const RowHintLineList& NonogramBoard::getRowHintLineList() const {
	return rowHintLineList;
}

const ColumnHintLineList& NonogramBoard::getColumnHintLineList() const {
	return columnHintLineList;
}

Row NonogramBoard::getRowLine(RowIndex rowIndex) const {
	return board.getRowLine(rowIndex);
}

Column NonogramBoard::getColumnLine(ColumnIndex columnIndex) const {
	return board.getColumnLine(columnIndex);
}

HintLine NonogramBoard::getRowHintLine(RowIndex rowIndex) const {
	return rowHintLineList[rowIndex];
}

HintLine NonogramBoard::getColumnHintLine(ColumnIndex columnIndex) const {
	return columnHintLineList[columnIndex];
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
