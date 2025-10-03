#include "NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList,
		RowPlacementCountList rowPlacementCountList,
		ColumnPlacementCountList columnPlacementCountList
) : board(std::move(board)),
    rowHintLineList(std::move(rowHintLineList)),
    columnHintLineList(std::move(columnHintLineList)),
    rowPlacementCountList(std::move(rowPlacementCountList)),
    columnPlacementCountList(std::move(columnPlacementCountList)) {}

