#include "Algorithm/BacktrackAlgorithm/BacktrackAlgorithm.h"

#include "Board/Line/Line.h"
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"


BacktrackAlgorithm::BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard)
	: sharedBacktrackBoard(sharedBacktrackBoard) {}

void BacktrackAlgorithm::run() {
	RowLength rowLength = sharedBacktrackBoard.getRowLength();
	ColumnLength columnLength = sharedBacktrackBoard.getColumnLength();
	for (RowIndex rowIndex : RowIndex::iterate(0, rowLength.getLength())) {
        Row rowLine = sharedBacktrackBoard.getRowLine(rowIndex);
		RowHintSetList rowHintSetList = sharedBacktrackBoard.getRowHintSetList();
		HintSet rowHintSet = rowHintSetList[rowIndex];
		Row newRowLine = OverlapDeterminationAlgorithm::determineByOverlap(
            rowLine,
			rowHintSet
		).toRow();

		sharedBacktrackBoard.applyRow(rowIndex, newRowLine);

		PlacementCount count = PlacementPatternCountAlgorithm::run(
			rowLine,
			rowHintSet
		);
		sharedBacktrackBoard.setRowPlacementCount(rowIndex, count);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
