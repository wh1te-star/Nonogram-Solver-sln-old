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
	Row getRowLine(RowIndex rowIndex) const;
	Column getColumnLine(ColumnIndex columnIndex) const;
	HintLine getRowHintLine(RowIndex rowIndex) const;
	HintLine getColumnHintLine(ColumnIndex columnIndex) const;
	bool isSolved() const;

public:
	void applyCell(const Coordinate& coordinate, const Cell& cell);
	void applyRow(const RowIndex& rowIndex, const Row& row);
	void applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement);
	void applyColumn(const ColumnIndex& columnIndex, const Column& column);
	void applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement);
};

#endif
