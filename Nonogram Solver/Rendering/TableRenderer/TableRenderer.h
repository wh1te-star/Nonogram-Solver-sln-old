#ifndef TABLERENDERER_H
#define TABLERENDERER_H


#include "Board/BacktrackBoard/BacktrackBoard.h"

class TableRenderer {
private:
	enum CellType {
		BOARD_CELL,
		ROW_HINT,
		ROW_PLACEMENT_COUNT,
		COLUMN_HINT,
		COLUMN_PLACEMENT_COUNT,
		OUT_OF_BOARD
	};

	BacktrackBoard backtrackBoard;

public:
	TableRenderer(BacktrackBoard backtrackBoard);
	void render();

private:
	void drawGridLine(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		RowLength columnPlacementCountLength,
		ColumnLength rowPlacementCountLength
	);
};


#endif
