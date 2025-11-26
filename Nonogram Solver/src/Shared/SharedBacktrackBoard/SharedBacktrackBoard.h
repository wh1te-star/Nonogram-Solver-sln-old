#ifndef SHAREDBACKTRACKBOARD_H
#define SHAREDBACKTRACKBOARD_H


#include <mutex>
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include "Rendering/TableRenderer/TableRenderer.h"

class SharedBacktrackBoard {
private:
    mutable std::mutex mtx;
    BacktrackBoard backtrackBoard;

public:
	SharedBacktrackBoard(BacktrackBoard backtrackBoard);

public:
	BacktrackBoard getBacktrackBoard() const;
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
	void applyBoard(const Board& board, bool overwriteNone);
	RowHintSetList getRowHintSetList() const;
	ColumnHintSetList getColumnHintSetList() const;
	RowPlacementCountList getRowPlacementCountList() const;
	ColumnPlacementCountList getColumnPlacementCountList() const;
	void setRowPlacementCount(RowIndex rowIndex, PlacementCount placementCount);
	void setColumnPlacementCount(ColumnIndex columnIndex, PlacementCount placementCount);
};


#endif
