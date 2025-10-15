#ifndef NONOGRAMBOARD_H
#define NONOGRAMBOARD_H


#include "Board/Board/Board.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Board/Board/Board.h"
#include "Hint/HintLineList/ColumnHintLineList.h"
#include "Hint/HintLineList/RowHintLineList.h"

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
};

#endif
