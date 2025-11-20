#include "Shared/SharedBacktrackBoard.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedBacktrackBoard::SharedBacktrackBoard(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

RowLength SharedBacktrackBoard::getRowLength() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getRowLength();
}

ColumnLength SharedBacktrackBoard::getColumnLength() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getColumnLength();
}

Board SharedBacktrackBoard::getBoard() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getBoard();
}

Cell SharedBacktrackBoard::getCell(Coordinate coordinate) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getCell(coordinate);
}

Row SharedBacktrackBoard::getRowLine(RowIndex rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getRowLine(rowIndex);
}

Column SharedBacktrackBoard::getColumnLine(ColumnIndex columnIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getColumnLine(columnIndex);
}

bool SharedBacktrackBoard::isInRange(Coordinate coordinate) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.isInRange(coordinate);
}

bool SharedBacktrackBoard::isSolved() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.isSolved();
}

void SharedBacktrackBoard::applyCell(Coordinate coordinate, const Cell& cell) {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackBoard.applyCell(coordinate, cell);
}

void SharedBacktrackBoard::applyRow(RowIndex rowIndex, const Row& row) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyRow(rowIndex, row);
}

void SharedBacktrackBoard::applyRow(RowIndex rowIndex, const RowPlacement& rowPlacement) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyRow(rowIndex, rowPlacement);
}

void SharedBacktrackBoard::applyColumn(ColumnIndex columnIndex, const Column& column) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyColumn(columnIndex, column);
}

void SharedBacktrackBoard::applyColumn(ColumnIndex columnIndex, const ColumnPlacement& columnPlacement) {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.applyColumn(columnIndex, columnPlacement);
}

RowHintSetList SharedBacktrackBoard::getRowHintSetList() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getRowHintSetList();
}

ColumnHintSetList SharedBacktrackBoard::getColumnHintSetList() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getColumnHintSetList();
}

RowPlacementCountList SharedBacktrackBoard::getRowPlacementCountList() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getRowPlacementCountList();
}

ColumnPlacementCountList SharedBacktrackBoard::getColumnPlacementCountList() const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackBoard.getColumnPlacementCountList();
}


void SharedBacktrackBoard::addRowIndex(RowIndex rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.addRowIndex(rowIndex);
}

void SharedBacktrackBoard::addColumnIndex(ColumnIndex columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.addColumnIndex(columnIndex);
}

void SharedBacktrackBoard::deleteRowIndex(RowIndex rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.deleteRowIndex(rowIndex);
}

void SharedBacktrackBoard::deleteColumnIndex(ColumnIndex columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.deleteColumnIndex(columnIndex);
}

bool SharedBacktrackBoard::findRowIndex(RowIndex rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return highlightIndexes.findRowIndex(rowIndex);
}

bool SharedBacktrackBoard::findColumnIndex(ColumnIndex columnIndex) const {
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
