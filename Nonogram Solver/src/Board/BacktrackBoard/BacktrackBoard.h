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
	Row getRowLine(RowIndex rowIndex) const;
	Column getColumnLine(ColumnIndex columnIndex) const;
	HintSet getRowHintSet(RowIndex rowIndex) const;
	HintSet getColumnHintSet(ColumnIndex columnIndex) const;
	bool isSolved() const;

public:
	void applyCell(const Coordinate& coordinate, const Cell& cell);
	void applyRow(const RowIndex& rowIndex, const Row& row);
	void applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement);
	void applyColumn(const ColumnIndex& columnIndex, const Column& column);
	void applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement);
};

#endif
