#include "Shared/SharedBacktractBoard.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedBacktrackBoard::SharedBacktrackBoard(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

const BacktrackBoard& SharedBacktrackBoard::getBacktrackBoard() const {
	return backtrackBoard;
}

void SharedBacktrackBoard::applyCell(const Coordinate& coordinate, const Cell& cell) {
	std::lock_guard<std::mutex> lock(mtx);

	backtrackBoard.applyCell(coordinate, cell);
}

void SharedBacktrackBoard::applyPlacement(const Coordinate& coordinate, const Placement& placement) {
	std::lock_guard<std::mutex> lock(mtx);

	backtrackBoard.applyPlacement(coordinate, placement);
}
