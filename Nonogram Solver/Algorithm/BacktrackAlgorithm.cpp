#include "Algorithm/BacktrackAlgorithm.h"

#include <atomic>
#include <thread>
#include <chrono>


BacktrackAlgorithm::BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard)
	: sharedBacktrackBoard(sharedBacktrackBoard) {}

void BacktrackAlgorithm::run() {
	int i = 0;
	while (!should_terminate) {
		sharedBacktrackBoard.applyCell(
			Coordinate(
				RowIndex(i % 5),
				ColumnIndex(i % 5)
			),
			Cell(CellColor::Black)
		);
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));

		i++;
	}
}

void BacktrackAlgorithm::request_stop() {
	should_terminate = true;
}
