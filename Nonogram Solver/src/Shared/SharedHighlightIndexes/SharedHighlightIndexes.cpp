#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedHighlightIndexes::SharedHighlightIndexes(){}

HighlightIndexes SharedHighlightIndexes::getHighlightIndexes() const {
	std::lock_guard<std::mutex> lock(mtx);
	return highlightIndexes;
}

void SharedHighlightIndexes::addRowIndex(RowIndex rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.addRowIndex(rowIndex);
}

void SharedHighlightIndexes::addColumnIndex(ColumnIndex columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.addColumnIndex(columnIndex);
}

void SharedHighlightIndexes::deleteRowIndex(RowIndex rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.deleteRowIndex(rowIndex);
}

void SharedHighlightIndexes::deleteColumnIndex(ColumnIndex columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.deleteColumnIndex(columnIndex);
}

bool SharedHighlightIndexes::findRowIndex(RowIndex rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return highlightIndexes.findRowIndex(rowIndex);
}

bool SharedHighlightIndexes::findColumnIndex(ColumnIndex columnIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return highlightIndexes.findColumnIndex(columnIndex);
}

void SharedHighlightIndexes::clear() {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.clear();
}

void SharedHighlightIndexes::clearRowIndexes() {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.clearRowIndexes();
}

void SharedHighlightIndexes::clearColumnIndexes() {
	std::lock_guard<std::mutex> lock(mtx);
	highlightIndexes.clearColumnIndexes();
}
