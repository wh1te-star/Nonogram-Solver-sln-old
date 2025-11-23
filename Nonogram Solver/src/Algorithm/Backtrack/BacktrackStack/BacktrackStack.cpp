#include "Algorithm/Backtrack/BacktrackStack/BacktrackStack.h"

#include <cassert>
#include "Board/Line/Line.h"
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Algorithm/ExhaustivePlacementPatternFindAlgorithm/ExhaustivePlacementPatternFindAlgorithm.h"
#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"


BacktrackStack::BacktrackStack(
		RowLength rowLength,
		ColumnLength columnLength
){
	rowBacktrackDepth = 0;
	columnBacktrackDepth = 0;
	rowBacktrackStack.resize(rowLength.getLength(), 0);
	columnBacktrackStack.resize(columnLength.getLength(), 0);
}

int BacktrackStack::getDepthAtRowIndex(RowIndex rowIndex) const {
	return rowBacktrackStack[rowIndex.getIndex()];
}

int BacktrackStack::getDepthAtColumnIndex(ColumnIndex ColumnIndex) const {
	return rowBacktrackStack[ColumnIndex.getIndex()];
}

void BacktrackStack::pushRowIndex(RowIndex rowIndex) {
	int nextIndex = rowBacktrackDepth + columnBacktrackDepth + 1;
	rowBacktrackStack[rowIndex.getIndex()] = nextIndex;
	rowBacktrackDepth++;
}

void BacktrackStack::pushColumnIndex(ColumnIndex columnIndex) {
	int nextIndex = rowBacktrackDepth + columnBacktrackDepth + 1;
	columnBacktrackStack[columnIndex.getIndex()] = nextIndex;
	columnBacktrackDepth++;
}

void BacktrackStack::popDepth() {
	int deleteIndex = rowBacktrackDepth + columnBacktrackDepth;
	for (int i = 0; i < rowBacktrackStack.size(); i++) {
		if(rowBacktrackStack[i] == deleteIndex) {
			rowBacktrackStack[i] = -1;
			rowBacktrackDepth--;
			return;
		}
	}
	for (int i = 0; i < columnBacktrackStack.size(); i++) {
		if(columnBacktrackStack[i] == deleteIndex) {
			columnBacktrackStack[i] = -1;
			columnBacktrackDepth--;
			return;
		}
	}
}

