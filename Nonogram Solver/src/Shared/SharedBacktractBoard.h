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
    const BacktrackBoard& getBacktrackBoard() const;

public:
	Row getRowLine(RowIndex rowIndex) const ;
	Column getColumnLine(ColumnIndex columnIndex) const;
	HintLine getRowHintLine(RowIndex rowIndex) const;
	HintLine getColumnHintLine(ColumnIndex columnIndex) const;
	bool isSolved() const;

public:
	void applyCell(const Coordinate& coordinate, const Cell& cellColor);
	void applyRow(const RowIndex& rowIndex, const Row& row);
	void applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement);
	void applyColumn(const ColumnIndex& columnIndex, const Column& column);
	void applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement);
};


#endif
