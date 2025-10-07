#include "Board/NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList
) : board(std::move(board)),
    rowHintLineList(std::move(rowHintLineList)),
    columnHintLineList(std::move(columnHintLineList)) {}

