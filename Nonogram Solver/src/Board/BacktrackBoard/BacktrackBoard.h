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
	RowLength getRowLength() const;
	ColumnLength getColumnLength() const;
	Board getBoard() const;
	Cell getCell(Coordinate coordinate) const;
	Row getRowLine(RowIndex rowIndex) const;
	Column getColumnLine(ColumnIndex columnIndex) const;
	bool isInRange(Coordinate coordinate) const;
	bool isSolved() const;
	void applyCell(Coordinate coordinate, const Cell& cell, bool overrideNone = false);
	void applyRow(RowIndex rowIndex, const Row& row, bool overwriteNone);
	void applyRow(RowIndex rowIndex, const RowPlacement& rowPlacement);
	void applyColumn(ColumnIndex columnIndex, const Column& column, bool overwriteNone);
	void applyColumn(ColumnIndex columnIndex, const ColumnPlacement& columnPlacement);

public:
	RowHintSetList getRowHintSetList() const;
	ColumnHintSetList getColumnHintSetList() const;

public:
	RowPlacementCountList getRowPlacementCountList() const;
	ColumnPlacementCountList getColumnPlacementCountList() const;
	void setRowPlacementCount(RowIndex rowIndex, PlacementCount placementCount);
	void setColumnPlacementCount(ColumnIndex columnIndex, PlacementCount placementCount);
};

#endif
