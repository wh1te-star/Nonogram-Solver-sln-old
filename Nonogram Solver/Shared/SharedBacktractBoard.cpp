#include "Shared/SharedBacktractBoard.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedBacktrackBoard::SharedBacktrackBoard(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

const BacktrackBoard& SharedBacktrackBoard::getBacktrackBoard() const {
	return backtrackBoard;
}

void SharedBacktrackBoard::applyPlacement(Coordinate coordinate, Placement &placement) {
	std::lock_guard<std::mutex> lock(mtx);

	//backtrackBoard.applyPlacement(coordinate, placement);
}
