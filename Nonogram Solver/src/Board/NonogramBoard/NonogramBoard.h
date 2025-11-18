#ifndef NONOGRAMBOARD_H
#define NONOGRAMBOARD_H


#include "Board/Board/Board.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Hint/HintLineList/ColumnHintLineList.h"
#include "Hint/HintLineList/RowHintLineList.h"
#include "Hint/HintLine/HintLine.h"

class NonogramBoard {
private:
    Board board;
	RowHintLineList rowHintLineList;
	ColumnHintLineList columnHintLineList;

public:
    explicit NonogramBoard(
		Board board,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList
	);

public:
	const Board& getBoard() const;
	const RowLength& getRowCount() const;
	const ColumnLength& getColumnCount() const;
	const RowHintLineList& getRowHintLineList() const;
	const ColumnHintLineList& getColumnHintLineList() const;

public:
	const Row& getRowLine(RowIndex rowIndex) const;
	const Column& getColumnLine(ColumnIndex columnIndex) const;
	const HintLine& getRowHintLine(RowIndex rowIndex) const;
	const HintLine& getColumnHintLine(ColumnIndex columnIndex) const;
	const bool isSolved() const;

public:
	void applyCell(const Coordinate& coordinate, const Cell& cell);
	void applyPlacement(const Coordinate& coordinate, const Placement& placement);
};

#endif
