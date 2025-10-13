#include "Board/NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList
) : board(std::move(board)),
    rowHintLineList(std::move(rowHintLineList)),
    columnHintLineList(std::move(columnHintLineList)) {}

const Board& NonogramBoard::getBoard() const {
	return board;
}

const RowLength& NonogramBoard::getRowCount() const {
	return board.getRowLength();
}

const ColumnLength& NonogramBoard::getColumnCount() const {
	return board.getColumnLength();
}

const RowHintLineList& NonogramBoard::getRowHintLineList() const {
	return rowHintLineList;
}

const ColumnHintLineList& NonogramBoard::getColumnHintLineList() const {
	return columnHintLineList;
}

