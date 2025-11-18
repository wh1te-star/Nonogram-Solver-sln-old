#include "Algorithm/BacktrackAlgorithm/BacktrackAlgorithm.h"

#include "Board/Line/Line.h"
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"
#include <atomic>
#include <thread>
#include <chrono>


BacktrackAlgorithm::BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard)
	: sharedBacktrackBoard(sharedBacktrackBoard) {}

void BacktrackAlgorithm::run() {
	//recursiveSolve(0, 100);

	for (RowIndex rowIndex : RowIndex::iterate(0, 10)) {
        Row rowLine = sharedBacktrackBoard.getRowLine(rowIndex);
		HintLine rowHintLine = sharedBacktrackBoard.getRowHintLine(rowIndex);
		Line newLine = OverlapDeterminationAlgorithm::determineByOverlap(
            rowLine,
			rowHintLine
		);

		sharedBacktrackBoard.applyLine(coordinate, Cell(Black));
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void BacktrackAlgorithm::recursiveSolve(int count, int max) {
    if (terminate) return;
    if (count >= max) return;

    sharedBacktrackBoard.applyCell(
        Coordinate(RowIndex(count / 10), ColumnIndex(count % 10)),
        Cell(Black)
	);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    recursiveSolve(count + 1, max);
}

void BacktrackAlgorithm::request_stop() {
	terminate = true;
}
