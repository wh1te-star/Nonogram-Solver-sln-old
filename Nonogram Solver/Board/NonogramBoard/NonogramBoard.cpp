#include "Board/NonogramBoard/NonogramBoard.h"


NonogramBoard::NonogramBoard(
		Board board,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList
) : board(std::move(board)),
    rowHintLineList(std::move(rowHintLineList)),
    columnHintLineList(std::move(columnHintLineList)) {}

Board& NonogramBoard::getBoard() {
	return board;
}

RowLength NonogramBoard::getRowCount() const {
	return board.getRowLength();
}

ColumnLength NonogramBoard::getColumnCount() const {
	return board.getColumnLength();
}

RowHintLineList NonogramBoard::getRowHintLineList() const {
	return rowHintLineList;
}

ColumnHintLineList NonogramBoard::getColumnHintLineList() const {
	return columnHintLineList;
}

