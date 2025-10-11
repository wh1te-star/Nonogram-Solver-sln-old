#include "Board/BacktrackBoard/BacktrackBoard.h"


BacktrackBoard::BacktrackBoard(
		NonogramBoard nonogramBoard,
		RowPlacementCountList rowPlacementCountList,
		ColumnPlacementCountList columnPlacementCountList
) : nonogramBoard(std::move(nonogramBoard)),
    rowPlacementCountList(std::move(rowPlacementCountList)),
    columnPlacementCountList(std::move(columnPlacementCountList)) {}

NonogramBoard& BacktrackBoard::getNonogramBoard(){
	return nonogramBoard;
}

RowPlacementCountList BacktrackBoard::getRowPlacementCountList() const {
	return rowPlacementCountList;
}

ColumnPlacementCountList BacktrackBoard::getColumnPlacementCountList() const {
	return columnPlacementCountList;
}


