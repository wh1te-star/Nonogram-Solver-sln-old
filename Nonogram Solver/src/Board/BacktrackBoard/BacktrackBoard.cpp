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

const Row& BacktrackBoard::getRowLine(RowIndex rowIndex) const {
	return nonogramBoard.getRowLine(rowIndex);
}

const Column& BacktrackBoard::getColumnLine(ColumnIndex columnIndex) const {
	return nonogramBoard.getColumnLine(columnIndex);
}

const HintLine& BacktrackBoard::getRowHintLine(RowIndex rowIndex) const {
	return nonogramBoard.getRowHintLine(rowIndex);
}

const HintLine& BacktrackBoard::getColumnHintLine(ColumnIndex columnIndex) const {
	return nonogramBoard.getColumnHintLine(columnIndex);
}

const bool BacktrackBoard::isSolved() const {
	return nonogramBoard.isSolved();
}

void BacktrackBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	nonogramBoard.applyCell(coordinate, cell);
}

void BacktrackBoard::applyPlacement(const Coordinate& coordinate, const Placement& placement) {
	nonogramBoard.applyPlacement(coordinate, placement);
}
