#include "Algorithm/Backtrack/BacktrackAlgorithm/BacktrackAlgorithm.h"

#include <algorithm>
#include "Board/Line/Line.h"
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Algorithm/ExhaustivePlacementPatternFindAlgorithm/ExhaustivePlacementPatternFindAlgorithm.h"
#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"


BacktrackAlgorithm::BacktrackAlgorithm(
    SharedBacktrackBoard& sharedBacktrackBoard,
    SharedBacktrackStack& sharedBacktrackStack,
	SharedHighlightIndexes& sharedHighlightIndexes
) :
    sharedBacktrackBoard(sharedBacktrackBoard),
    sharedBacktrackStack(sharedBacktrackStack),
	sharedHighlightIndexes(sharedHighlightIndexes) {}

void BacktrackAlgorithm::run() {
    backtrackSolve();
}

void BacktrackAlgorithm::backtrackSolve() {
    deterministicSolve(10);

    backtrackSolveRecursive(0);
}

void BacktrackAlgorithm::backtrackSolveRecursive(int depth) {
	if (terminate.load()) return;

	RowIndex targetRowIndex = RowIndex(0);
    if(depth == 0) {
		targetRowIndex = RowIndex(34);
    } else if(depth == 1){
		targetRowIndex = RowIndex(49);
	}
    else if (depth == 2) {
        return;
		targetRowIndex = RowIndex(64);
    }
    else {
        return;
    }
	std::vector<Placement> exhaustivePlacements = ExhaustivePlacementPatternFindAlgorithm::run(
        sharedBacktrackBoard.getRowLine(targetRowIndex),
        sharedBacktrackBoard.getRowHintSetList()[targetRowIndex]
	);
    BacktrackBoard previousBacktrackBoard = sharedBacktrackBoard.getBacktrackBoard();
    for (Placement placement : exhaustivePlacements) {
		sharedBacktrackBoard.applyRow(targetRowIndex, placement.toRowPlacement());
		if (waitAndCheckTermination(1000)) return;
        bool more = deterministicSolve(0);
        if (sharedBacktrackBoard.isSolved()) {
			solutions.push_back(sharedBacktrackBoard.getBoard());
        }
		if(more) {
            backtrackSolveRecursive(depth + 1);
        }
		sharedBacktrackBoard.applyBoard(previousBacktrackBoard.getBoard(), true);
        for (RowIndex rowIndex : RowIndex::range(0, previousBacktrackBoard.getBoard().getRowLength().getLength() - 1)) {
            PlacementCount placementCount = previousBacktrackBoard.getRowPlacementCountList()[rowIndex];
            sharedBacktrackBoard.setRowPlacementCount(rowIndex, placementCount);
        }
        for (ColumnIndex columnIndex : ColumnIndex::range(0, previousBacktrackBoard.getBoard().getColumnLength().getLength() - 1)) {
            PlacementCount placementCount = previousBacktrackBoard.getColumnPlacementCountList()[columnIndex];
            sharedBacktrackBoard.setColumnPlacementCount(columnIndex, placementCount);
        }
		if (waitAndCheckTermination(50)) return;
    }

    if(solutions.size() > 0){
        sharedBacktrackBoard.applyBoard(solutions[0], true);
	}
}

bool BacktrackAlgorithm::deterministicSolve(int waitMillis) {
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
            if(newRowLine.size() == 0) {
                return false;
			}
			Row currentRowLine = sharedBacktrackBoard.getRowLine(rowIndex);
			sharedBacktrackBoard.applyRow(rowIndex, newRowLine, false);
            if (currentRowLine != sharedBacktrackBoard.getRowLine(rowIndex)) {
                proceed = true;
            }

            PlacementCount count = PlacementPatternCountAlgorithm::run(
                rowLine,
                rowHintSet
            );
            sharedBacktrackBoard.setRowPlacementCount(rowIndex, count);
            if (count == PlacementCount(0)) {
                return false;
            }
			if (count == PlacementCount(1)) {
                RowPlacement finalPlacement = ExhaustivePlacementPatternFindAlgorithm::run(
                    rowLine,
                    rowHintSet
                )[0].toRowPlacement();
				sharedBacktrackBoard.applyRow(rowIndex, finalPlacement);
            }

            if (waitAndCheckTermination(waitMillis)) return false;

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
            if(newColumnLine.size() == 0) {
                return false;
			}
			Column currentColumnLine = sharedBacktrackBoard.getColumnLine(columnIndex);
			sharedBacktrackBoard.applyColumn(columnIndex, newColumnLine, false);
            if (currentColumnLine != sharedBacktrackBoard.getColumnLine(columnIndex)) {
				proceed = true;
            }

            PlacementCount count = PlacementPatternCountAlgorithm::run(
                columnLine,
                columnHintSet
            );
            sharedBacktrackBoard.setColumnPlacementCount(columnIndex, count);
            if (count == PlacementCount(0)) return false;
			if (count == PlacementCount(1)) {
                ColumnPlacement finalPlacement = ExhaustivePlacementPatternFindAlgorithm::run(
                    columnLine,
                    columnHintSet
                )[0].toColumnPlacement();
				sharedBacktrackBoard.applyColumn(columnIndex, finalPlacement);
            }

            if (waitAndCheckTermination(waitMillis)) return false;

			sharedHighlightIndexes.deleteColumnIndex(columnIndex);
        }

		if(proceed == false) {
            return true;
		}
		if(sharedBacktrackBoard.isSolved()) {
            return false;
		}
    }
    return true;
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
