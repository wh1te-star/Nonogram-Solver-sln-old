#include "Shared/SharedBacktractBoard.h"

#include <atomic>
#include <thread>
#include <chrono>


SharedBacktrackBoard::SharedBacktrackBoard(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

void SharedBacktrackBoard::applyPlacement(Coordinate coordinate, Placement &placement) {
	std::lock_guard<std::mutex> lock(mtx);

	backtrackBoard.getNonogramBoard().getBoard().applyPlacement(coordinate, placement);
}

void SharedBacktrackBoard::render(const TableRenderer& tableRenderer) const {
	std::lock_guard<std::mutex> lock(mtx);
	
	tableRenderer.render(backtrackBoard);
}
