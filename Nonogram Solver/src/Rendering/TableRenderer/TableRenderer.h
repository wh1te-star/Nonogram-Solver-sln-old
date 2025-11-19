#ifndef TABLERENDERER_H
#define TABLERENDERER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include <string>
#include "Board/Board/Board.h"
#include "Index/CellIndex/RowIndex.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include "Hint/HintSetList/RowHintSetList.h"
#include "Hint/HintSetList/ColumnHintSetList.h"
#include "Placement/PlacementCountList/RowPlacementCountList.h"
#include "Placement/PlacementCountList/ColumnPlacementCountList.h"
class SharedBacktrackBoard;

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

public:
	TableRenderer();
	void render(const SharedBacktrackBoard& sharedBacktrackBoard) const;

private:
	CellType determineCellType(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		RowLength boardRowLength,
		ColumnLength boardColumnLength
	) const;

	void setupCellStyle(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		Board board,
		CellType cellType
	) const;

	std::string setLabel(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		CellType cellType,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		RowHintSetList rowHintSetList,
		ColumnHintSetList columnHintSetList,
		RowPlacementCountList rowPlacementCountList,
		ColumnPlacementCountList columnPlacementCountList,
		float cell_size
	) const;

	void drawGridLine(
		RowIndex rowIndex,
		ColumnIndex columnIndex,
		RowLength columnHintLength,
		ColumnLength rowHintLength,
		RowLength columnPlacementCountLength,
		ColumnLength rowPlacementCountLength
	) const;
};


#endif
