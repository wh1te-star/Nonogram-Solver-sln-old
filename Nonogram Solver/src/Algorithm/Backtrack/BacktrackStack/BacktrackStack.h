#ifndef BACKTRACKSTACK_H
#define BACKTRACKSTACK_H


#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"
#include "Board/Line/Line.h"
#include "Hint/HintSet/HintSet.h"

class BacktrackStack {
private:
	int rowBacktrackDepth;
	int columnBacktrackDepth;
	std::vector<int> rowBacktrackStack;
	std::vector<int> columnBacktrackStack;

public:
    explicit BacktrackStack(
		RowLength rowLength,
		ColumnLength columnLength
    );

	int getDepthAtRowIndex(RowIndex rowIndex) const;
	int getDepthAtColumnIndex(ColumnIndex ColumnIndex) const;
	void pushRowIndex(RowIndex rowIndex);
	void pushColumnIndex(ColumnIndex columnIndex);
	void popDepth();
};


#endif
