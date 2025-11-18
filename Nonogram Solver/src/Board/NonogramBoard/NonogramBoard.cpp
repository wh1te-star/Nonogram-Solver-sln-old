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

const Row& NonogramBoard::getRowLine(RowIndex rowIndex) const {
	return board.getRowLine(rowIndex);
}
const Column& NonogramBoard::getColumnLine(ColumnIndex columnIndex) const {
	return board.getColumnLine(columnIndex);
}

const HintLine& NonogramBoard::getRowHintLine(RowIndex rowIndex) const {
	return rowHintLineList[rowIndex];
}

const HintLine& NonogramBoard::getColumnHintLine(ColumnIndex columnIndex) const {
	return columnHintLineList[columnIndex];
}

const bool NonogramBoard::isSolved() const {
	return board.isSolved();
}

void NonogramBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	board.applyCell(coordinate, cell);
}

void NonogramBoard::applyPlacement(const Coordinate& coordinate, const Placement& placement) {
	board.applyPlacement(coordinate, placement);
}
