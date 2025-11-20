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

RowLength BacktrackBoard::getRowLength() const {
	return nonogramBoard.getRowLength();
}

ColumnLength BacktrackBoard::getColumnLength() const {
	return nonogramBoard.getColumnLength();
}

Board BacktrackBoard::getBoard() const {
	return nonogramBoard.getBoard();
}

Cell BacktrackBoard::getCell(Coordinate coordinate) const {
	return nonogramBoard.getCell(coordinate);
}

Row BacktrackBoard::getRowLine(RowIndex rowIndex) const {
	return nonogramBoard.getRowLine(rowIndex);
}

Column BacktrackBoard::getColumnLine(ColumnIndex columnIndex) const {
	return nonogramBoard.getColumnLine(columnIndex);
}

bool BacktrackBoard::isInRange(Coordinate coordinate) const {
	return nonogramBoard.isInRange(coordinate);
}

bool BacktrackBoard::isSolved() const {
	return nonogramBoard.isSolved();
}

void BacktrackBoard::applyCell(Coordinate coordinate, const Cell& cell) {
	nonogramBoard.applyCell(coordinate, cell);
}

void BacktrackBoard::applyRow(RowIndex rowIndex, const Row& row) {
	return nonogramBoard.applyRow(rowIndex, row);
}

void BacktrackBoard::applyRow(RowIndex rowIndex, const RowPlacement& rowPlacement) {
	return nonogramBoard.applyRow(rowIndex, rowPlacement);
}

void BacktrackBoard::applyColumn(ColumnIndex columnIndex, const Column& column) {
	return nonogramBoard.applyColumn(columnIndex, column);
}

void BacktrackBoard::applyColumn(ColumnIndex columnIndex, const ColumnPlacement& columnPlacement) {
	return nonogramBoard.applyColumn(columnIndex, columnPlacement);
}

RowHintSetList BacktrackBoard::getRowHintSetList() const {
	return nonogramBoard.getRowHintSetList();
}

ColumnHintSetList BacktrackBoard::getColumnHintSetList() const {
	return nonogramBoard.getColumnHintSetList();
}

RowPlacementCountList BacktrackBoard::getRowPlacementCountList() const {
	return rowPlacementCountList;
}

ColumnPlacementCountList BacktrackBoard::getColumnPlacementCountList() const {
	return columnPlacementCountList;
}

