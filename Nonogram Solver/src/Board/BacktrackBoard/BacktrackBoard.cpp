#include "Board/BacktrackBoard/BacktrackBoard.h"


BacktrackBoard::BacktrackBoard(
		NonogramBoard nonogramBoard,
		RowPlacementCountList rowPlacementCountList,
		ColumnPlacementCountList columnPlacementCountList
) : nonogramBoard(std::move(nonogramBoard)),
    rowPlacementCountList(std::move(rowPlacementCountList)),
    columnPlacementCountList(std::move(columnPlacementCountList)) {}

const NonogramBoard& BacktrackBoard::getNonogramBoard() const {
	return nonogramBoard;
}

const RowPlacementCountList& BacktrackBoard::getRowPlacementCountList() const {
	return rowPlacementCountList;
}

const ColumnPlacementCountList& BacktrackBoard::getColumnPlacementCountList() const {
	return columnPlacementCountList;
}

Row BacktrackBoard::getRowLine(RowIndex rowIndex) const {
	return nonogramBoard.getRowLine(rowIndex);
}

Column BacktrackBoard::getColumnLine(ColumnIndex columnIndex) const {
	return nonogramBoard.getColumnLine(columnIndex);
}

HintLine BacktrackBoard::getRowHintLine(RowIndex rowIndex) const {
	return nonogramBoard.getRowHintLine(rowIndex);
}

HintLine BacktrackBoard::getColumnHintLine(ColumnIndex columnIndex) const {
	return nonogramBoard.getColumnHintLine(columnIndex);
}

bool BacktrackBoard::isSolved() const {
	return nonogramBoard.isSolved();
}

void BacktrackBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	nonogramBoard.applyCell(coordinate, cell);
}

void BacktrackBoard::applyRow(const RowIndex& rowIndex, const Row& row) {
	return nonogramBoard.applyRow(rowIndex, row);
}

void BacktrackBoard::applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement) {
	return nonogramBoard.applyRow(rowIndex, rowPlacement);
}

void BacktrackBoard::applyColumn(const ColumnIndex& columnIndex, const Column& column) {
	return nonogramBoard.applyColumn(columnIndex, column);
}

void BacktrackBoard::applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement) {
	return nonogramBoard.applyColumn(columnIndex, columnPlacement);
}

