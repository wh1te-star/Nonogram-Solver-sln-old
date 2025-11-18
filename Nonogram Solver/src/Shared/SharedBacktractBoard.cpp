#include "Shared/SharedBacktractBoard.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedBacktrackBoard::SharedBacktrackBoard(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

const BacktrackBoard& SharedBacktrackBoard::getBacktrackBoard() const {
	return backtrackBoard;
}

Row SharedBacktrackBoard::getRowLine(RowIndex rowIndex) const {
	return backtrackBoard.getRowLine(rowIndex);
}

Column SharedBacktrackBoard::getColumnLine(ColumnIndex columnIndex) const {
	return backtrackBoard.getColumnLine(columnIndex);
}

HintLine SharedBacktrackBoard::getRowHintLine(RowIndex rowIndex) const {
	return backtrackBoard.getRowHintLine(rowIndex);
}

HintLine SharedBacktrackBoard::getColumnHintLine(ColumnIndex columnIndex) const {
	return backtrackBoard.getColumnHintLine(columnIndex);
}

bool SharedBacktrackBoard::isSolved() const {
	return backtrackBoard.isSolved();
}

void SharedBacktrackBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	std::lock_guard<std::mutex> lock(mtx);

	backtrackBoard.applyCell(coordinate, cell);
}

void SharedBacktrackBoard::applyRow(const RowIndex& rowIndex, const Row& row) {
	return backtrackBoard.applyRow(rowIndex, row);
}

void SharedBacktrackBoard::applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement) {
	return backtrackBoard.applyRow(rowIndex, rowPlacement);
}

void SharedBacktrackBoard::applyColumn(const ColumnIndex& columnIndex, const Column& column) {
	return backtrackBoard.applyColumn(columnIndex, column);
}

void SharedBacktrackBoard::applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement) {
	return backtrackBoard.applyColumn(columnIndex, columnPlacement);
}
