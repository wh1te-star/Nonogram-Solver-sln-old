#include "Shared/SharedBacktrackBoard.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedBacktrackBoard::SharedBacktrackBoard(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

Row SharedBacktrackBoard::getRowLine(RowIndex rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getRowLine(rowIndex);
}

Column SharedBacktrackBoard::getColumnLine(ColumnIndex columnIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getColumnLine(columnIndex);
}

HintLine SharedBacktrackBoard::getRowHintLine(RowIndex rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getRowHintLine(rowIndex);
}

HintLine SharedBacktrackBoard::getColumnHintLine(ColumnIndex columnIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getColumnHintLine(columnIndex);
}

bool SharedBacktrackBoard::isSolved() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.isSolved();
}

void SharedBacktrackBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackBoard.applyCell(coordinate, cell);
}

void SharedBacktrackBoard::applyRow(const RowIndex& rowIndex, const Row& row) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyRow(rowIndex, row);
}

void SharedBacktrackBoard::applyRow(const RowIndex& rowIndex, const RowPlacement& rowPlacement) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyRow(rowIndex, rowPlacement);
}

void SharedBacktrackBoard::applyColumn(const ColumnIndex& columnIndex, const Column& column) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyColumn(columnIndex, column);
}

void SharedBacktrackBoard::applyColumn(const ColumnIndex& columnIndex, const ColumnPlacement& columnPlacement) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyColumn(columnIndex, columnPlacement);
}

void SharedBacktrackBoard::addRowIndex(const RowIndex& rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.addRowIndex(rowIndex);
}

void SharedBacktrackBoard::addColumnIndex(const ColumnIndex& columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.addColumnIndex(columnIndex);
}

void SharedBacktrackBoard::deleteRowIndex(const RowIndex& rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.deleteRowIndex(rowIndex);
}

void SharedBacktrackBoard::deleteColumnIndex(const ColumnIndex& columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.deleteColumnIndex(columnIndex);
}

bool SharedBacktrackBoard::findRowIndex(const RowIndex& rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return highlightIndexes.findRowIndex(rowIndex);
}

bool SharedBacktrackBoard::findColumnIndex(const ColumnIndex& columnIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return highlightIndexes.findColumnIndex(columnIndex);
}

void SharedBacktrackBoard::clear() {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.clear();
}

void SharedBacktrackBoard::clearRowIndexes() {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.clearRowIndexes();
}

void SharedBacktrackBoard::clearColumnIndexes() {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.clearColumnIndexes();
}
