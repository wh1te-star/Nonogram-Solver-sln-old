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

public:
	const NonogramBoard& getNonogramBoard() const;
	const RowPlacementCountList& getRowPlacementCountList() const;
	const ColumnPlacementCountList& getColumnPlacementCountList() const;

public:
	void applyCell(const Coordinate& coordinate, const Cell& cell);
	void applyPlacement(const Coordinate& coordinate, const Placement& placement);
};

#endif
