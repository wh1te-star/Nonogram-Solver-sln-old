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


