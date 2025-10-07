#ifndef NONOGRAMBOARD_H
#define NONOGRAMBOARD_H


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
};

#endif
