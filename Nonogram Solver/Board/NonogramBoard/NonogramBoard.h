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

	Board& getBoard() const;
	RowLength& getRowCount() const;
	ColumnLength& getColumnCount() const;
	RowHintLineList& getRowHintLineList() const;
	ColumnHintLineList& getColumnHintLineList() const;
};

#endif
