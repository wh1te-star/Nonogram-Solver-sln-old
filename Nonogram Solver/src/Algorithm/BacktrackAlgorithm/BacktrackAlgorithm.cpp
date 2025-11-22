#include "Algorithm/BacktrackAlgorithm/BacktrackAlgorithm.h"

#include "Board/Line/Line.h"
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"


BacktrackAlgorithm::BacktrackAlgorithm(
    SharedBacktrackBoard& sharedBacktrackBoard,
	SharedHighlightIndexes& sharedHighlightIndexes
) :
    sharedBacktrackBoard(sharedBacktrackBoard),
	sharedHighlightIndexes(sharedHighlightIndexes) {}

void BacktrackAlgorithm::run() {
	RowLength rowLength = sharedBacktrackBoard.getRowLength();
	ColumnLength columnLength = sharedBacktrackBoard.getColumnLength();
    while (true) {
		bool proceed = false;
        for (RowIndex rowIndex : RowIndex::range(0, rowLength.getLength() - 1)) {
			sharedHighlightIndexes.addRowIndex(rowIndex);

            Row rowLine = sharedBacktrackBoard.getRowLine(rowIndex);
            RowHintSetList rowHintSetList = sharedBacktrackBoard.getRowHintSetList();
            HintSet rowHintSet = rowHintSetList[rowIndex];
            Row newRowLine = OverlapDeterminationAlgorithm::run(
                rowLine,
                rowHintSet
            ).toRow();
			Row currentRowLine = sharedBacktrackBoard.getRowLine(rowIndex);
			sharedBacktrackBoard.applyRow(rowIndex, newRowLine);
            if (currentRowLine != sharedBacktrackBoard.getRowLine(rowIndex)) {
                proceed = true;
            }

            PlacementCount count = PlacementPatternCountAlgorithm::run(
                rowLine,
                rowHintSet
            );
            sharedBacktrackBoard.setRowPlacementCount(rowIndex, count);

            if (waitAndCheckTermination(10)) return;

			sharedHighlightIndexes.deleteRowIndex(rowIndex);
        }

        for (ColumnIndex columnIndex : ColumnIndex::range(0, columnLength.getLength() - 1)) {
			sharedHighlightIndexes.addColumnIndex(columnIndex);

            Column columnLine = sharedBacktrackBoard.getColumnLine(columnIndex);
            ColumnHintSetList columnHintSetList = sharedBacktrackBoard.getColumnHintSetList();
            HintSet columnHintSet = columnHintSetList[columnIndex];
            Column newColumnLine = OverlapDeterminationAlgorithm::run(
                columnLine,
                columnHintSet
            ).toColumn();
			Column currentColumnLine = sharedBacktrackBoard.getColumnLine(columnIndex);
			sharedBacktrackBoard.applyColumn(columnIndex, newColumnLine);
            if (currentColumnLine != sharedBacktrackBoard.getColumnLine(columnIndex)) {
				proceed = true;
            }

            PlacementCount count = PlacementPatternCountAlgorithm::run(
                columnLine,
                columnHintSet
            );
            sharedBacktrackBoard.setColumnPlacementCount(columnIndex, count);

            if (waitAndCheckTermination(10)) return;

			sharedHighlightIndexes.deleteColumnIndex(columnIndex);
        }

		if(proceed == false || sharedBacktrackBoard.isSolved()) {
			return;
		}
    }
}

bool BacktrackAlgorithm::waitAndCheckTermination(const int waitMillis) const {
    if (waitMillis <= 0) {
        return terminate.load();
    }

    const int checkIntervalMillis = 100; 
    int checks = waitMillis / checkIntervalMillis;
    int remainingMillis = waitMillis % checkIntervalMillis;
    for (int i = 0; i < checks; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(checkIntervalMillis));
        if (terminate.load()) {
            return true;
        }
    }
    if (remainingMillis > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(remainingMillis));
    }
    return terminate.load();
}

void BacktrackAlgorithm::request_stop() {
	terminate = true;
}
