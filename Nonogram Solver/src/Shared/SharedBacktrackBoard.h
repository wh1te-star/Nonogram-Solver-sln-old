#ifndef SHAREDBACKTRACKBOARD_H
#define SHAREDBACKTRACKBOARD_H


#include <mutex>
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include "Rendering/HighlightIndexes/HighlightIndexes.h"
#include "Rendering/TableRenderer/TableRenderer.h"

class SharedBacktrackBoard {
private:
    mutable std::mutex mtx;
    BacktrackBoard backtrackBoard;
	HighlightIndexes highlightIndexes;

public:
	SharedBacktrackBoard(BacktrackBoard backtrackBoard);

public:
	RowLength getRowLength() const;
	ColumnLength getColumnLength() const;
	Board getBoard() const;
	Cell getCell(Coordinate coordinate) const;
	Row getRowLine(RowIndex rowIndex) const;
	Column getColumnLine(ColumnIndex columnIndex) const;
	bool isInRange(Coordinate coordinate) const;
	bool isSolved() const;
	void applyCell(Coordinate coordinate, const Cell& cell);
	void applyRow(RowIndex rowIndex, const Row& row);
	void applyRow(RowIndex rowIndex, const RowPlacement& rowPlacement);
	void applyColumn(ColumnIndex columnIndex, const Column& column);
	void applyColumn(ColumnIndex columnIndex, const ColumnPlacement& columnPlacement);
	RowHintSetList getRowHintSetList() const;
	ColumnHintSetList getColumnHintSetList() const;
	RowPlacementCountList getRowPlacementCountList() const;
	ColumnPlacementCountList getColumnPlacementCountList() const;

public:
	void addRowIndex(RowIndex rowIndex);
	void addColumnIndex(ColumnIndex columnIndex);
	void deleteRowIndex(RowIndex rowIndex);
	void deleteColumnIndex(ColumnIndex columnIndex);
	bool findRowIndex(RowIndex rowIndex) const;
	bool findColumnIndex(ColumnIndex columnIndex) const;
	void clear();
	void clearRowIndexes();
	void clearColumnIndexes();
};


#endif
