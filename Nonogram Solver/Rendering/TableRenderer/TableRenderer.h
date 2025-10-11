#ifndef TABLERENDERER_H
#define TABLERENDERER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include <string>

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
	CellType determineCellType(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		RowLength boardRowLength,
		ColumnLength boardColumnLength
	);

	void setupCellStyle(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		Board board,
		CellType cellType
	);

	std::string setLabel(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		CellType cellType,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		RowHintLineList rowHintLineList,
		ColumnHintLineList columnHintLineList,
		RowPlacementCountList rowPlacementCountList,
		ColumnPlacementCountList columnPlacementCountList,
		float cell_size
	);

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
