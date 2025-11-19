#ifndef NONOGRAMBOARD_H
#define NONOGRAMBOARD_H


#include "Board/Board/Board.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Hint/HintSetList/ColumnHintSetList.h"
#include "Hint/HintSetList/RowHintSetList.h"
#include "Hint/HintSet/HintSet.h"

class NonogramBoard {
private:
    Board board;
	RowHintSetList rowHintSetList;
	ColumnHintSetList columnHintSetList;

public:
    explicit NonogramBoard(
		Board board,
		RowHintSetList rowHintSetList,
		ColumnHintSetList columnHintSetList
	);

public:
	const Board& getBoard() const;
	const RowLength& getRowCount() const;
	const ColumnLength& getColumnCount() const;
	const RowHintSetList& getRowHintSetList() const;
	const ColumnHintSetList& getColumnHintSetList() const;

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
