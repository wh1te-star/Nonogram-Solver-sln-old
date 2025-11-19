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
	const Row getRowLine(RowIndex rowIndex) const;
	Column getColumnLine(ColumnIndex columnIndex) const;
	HintSet getRowHintSet(RowIndex rowIndex) const;
	HintSet getColumnHintSet(ColumnIndex columnIndex) const;
	bool isSolved() const;
	void applyCell(const Coordinate& coordinate, const Cell& cellColor);
	void applyRow(const RowIndex& rowIndex, const Row& row);
	void applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement);
	void applyColumn(const ColumnIndex& columnIndex, const Column& column);
	void applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement);

public:
	void addRowIndex(const RowIndex& rowIndex);
	void addColumnIndex(const ColumnIndex& columnIndex);
	void deleteRowIndex(const RowIndex& rowIndex);
	void deleteColumnIndex(const ColumnIndex& columnIndex);
	bool findRowIndex(const RowIndex& rowIndex) const;
	bool findColumnIndex(const ColumnIndex& columnIndex) const;
	void clear();
	void clearRowIndexes();
	void clearColumnIndexes();
};


#endif
