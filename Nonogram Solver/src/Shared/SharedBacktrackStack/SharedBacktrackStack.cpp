#include "Shared/SharedBacktrackStack/SharedBacktrackStack.h"

#include "Algorithm/Backtrack/BacktrackStack/BacktrackStack.h"


SharedBacktrackStack::SharedBacktrackStack(BacktrackStack backtrackStack)
	: backtrackStack(backtrackStack) {}

int SharedBacktrackStack::getDepthAtRowIndex(RowIndex rowIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackStack.getDepthAtRowIndex(rowIndex);
}

int SharedBacktrackStack::getDepthAtColumnIndex(ColumnIndex columnIndex) const {
	std::lock_guard<std::mutex> lock(mtx);
	return backtrackStack.getDepthAtColumnIndex(columnIndex);
}

void SharedBacktrackStack::pushRowIndex(RowIndex rowIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackStack.pushRowIndex(rowIndex);
}

void SharedBacktrackStack::pushColumnIndex(ColumnIndex columnIndex) {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackStack.pushColumnIndex(columnIndex);
}

void SharedBacktrackStack::popDepth() {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackStack.popDepth();
}

