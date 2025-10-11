#ifndef BACKTRACKBOARD_H
#define BACKTRACKBOARD_H


#include "Board/NonogramBoard/NonogramBoard.h"
#include "Placement/PlacementCountList/RowPlacementCountList.h"
#include "Placement/PlacementCountList/ColumnPlacementCountList.h"

class BacktrackBoard {
private:
	NonogramBoard nonogramBoard;
	RowPlacementCountList rowPlacementCountList;
	ColumnPlacementCountList columnPlacementCountList;

public:
    explicit BacktrackBoard(
		NonogramBoard nonogramBoard,
		RowPlacementCountList rowPlacementCountList,
		ColumnPlacementCountList columnPlacementCountList
	);

	NonogramBoard& getNonogramBoard();
	RowPlacementCountList getRowPlacementCountList() const;
	ColumnPlacementCountList getColumnPlacementCountList() const;
};

#endif
