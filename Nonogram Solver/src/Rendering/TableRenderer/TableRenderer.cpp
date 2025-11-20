#include "Rendering/TableRenderer/TableRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include "Rendering/FontData/FontData.h"
#include "Index/CellIndex/RowIndex.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"
#include <string>
#include "Shared/SharedBacktrackBoard.h"


TableRenderer::TableRenderer(){}

void TableRenderer::render(const SharedBacktrackBoard& sharedBacktrackBoard) const {
	ImGui::Begin("Nonogram Board", NULL, ImGuiWindowFlags_None);

	const Board board = sharedBacktrackBoard.getBoard();
	const RowHintSetList rowHintSetList = sharedBacktrackBoard.getRowHintSetList();
	const ColumnHintSetList columnHintSetList = sharedBacktrackBoard.getColumnHintSetList();
	const RowPlacementCountList rowPlacementCountList = sharedBacktrackBoard.getRowPlacementCountList();
	const ColumnPlacementCountList columnPlacementCountList = sharedBacktrackBoard.getColumnPlacementCountList();

	const RowLength boardRowLength = board.getRowLength();
	const ColumnLength boardColumnLength = board.getColumnLength();
	const RowLength columnHintLength = columnHintSetList.getMaxHintSetLength();
	const ColumnLength rowHintLength = rowHintSetList.getMaxHintSetLength();
	const RowLength columnPlacementCountLength = RowLength(1);
	const ColumnLength rowPlacementCountLength = ColumnLength(1);
	const RowLength totalRowLength = columnHintLength + boardRowLength + columnPlacementCountLength;
	const ColumnLength totalColumnLength = rowHintLength + boardColumnLength + rowPlacementCountLength;

	ImVec2 container_size = ImGui::GetContentRegionAvail();

	float min_container_dim = ImMin(container_size.x / totalColumnLength.getLength(), container_size.y / totalRowLength.getLength());
	float cell_size = round(min_container_dim);

	float table_width = cell_size * totalColumnLength.getLength();
	float table_height = cell_size * totalRowLength.getLength();

	float cursor_x = (container_size.x - table_width) * 0.5f;
	float cursor_y = (container_size.y - table_height) * 0.5f;

	if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
	if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);

	ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));

	if (ImGui::BeginTable("NonogramGrid", totalColumnLength.getLength(), ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoBordersInBody)) {

		for (int i = 0; i < totalColumnLength.getLength(); ++i) {
			ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
		}

		for (int rowIndexInt = 0; rowIndexInt < totalRowLength.getLength(); rowIndexInt++) {
			RowIndex rowIndex = RowIndex(rowIndexInt);
			ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
			for (int columnIndexInt = 0; columnIndexInt < totalColumnLength.getLength(); columnIndexInt++) {
				ColumnIndex columnIndex = ColumnIndex(columnIndexInt);
				ImGui::TableSetColumnIndex(columnIndexInt);

				ImVec2 button_size = ImVec2(cell_size, cell_size);

				CellType cellType = determineCellType(rowIndex, columnIndex, columnHintLength, rowHintLength, boardRowLength, boardColumnLength);

				setupCellStyle(
					rowIndex,
					columnIndex,
					columnHintLength,
					rowHintLength,
					board,
					cellType
				);

				std::string label = setLabel(
					rowIndex,
					columnIndex,
					cellType,
					columnHintLength,
					rowHintLength,
					rowHintSetList,
					columnHintSetList,
					rowPlacementCountList,
					columnPlacementCountList,
					cell_size
				);
				std::string unique_label = label + "##Cell" + std::to_string(rowIndexInt) + "_" + std::to_string(columnIndexInt);
				ImGui::Button(unique_label.c_str(), button_size);

				if (cellType == ROW_PLACEMENT_COUNT || cellType == ROW_HINT || cellType == COLUMN_PLACEMENT_COUNT || cellType == COLUMN_HINT) {
					ImGui::PopFont();
					ImGui::PopStyleColor(1);
				}
				ImGui::PopStyleVar();
				ImGui::PopStyleColor(3);

				drawGridLine(rowIndex, columnIndex, columnHintLength, rowHintLength, boardRowLength, boardColumnLength);
			}
		}
		ImGui::PopStyleVar();

		ImGui::EndTable();

		ImGui::End();
	}
}

TableRenderer::CellType TableRenderer::determineCellType(
	RowIndex rowIndex,
	ColumnIndex columnIndex,
	RowLength columnHintLength,
	ColumnLength rowHintLength,
	RowLength boardRowLength,
	ColumnLength boardColumnLength
) const { 
	if (rowHintLength <= columnIndex && columnIndex < rowHintLength + boardColumnLength) {
		if (rowIndex < columnHintLength) {
			return COLUMN_HINT;
		}
		else if (rowIndex < columnHintLength + boardRowLength) {
			return BOARD_CELL;
		}
		else {
			return COLUMN_PLACEMENT_COUNT;
		}
	}
	if (columnHintLength <= rowIndex && rowIndex < columnHintLength + boardRowLength) {
		if (columnIndex < rowHintLength) {
			return ROW_HINT;
		}
		else if (columnIndex < rowHintLength + boardColumnLength) {
			return BOARD_CELL;
		}
		else {
			return ROW_PLACEMENT_COUNT;
		}
	}
	return OUT_OF_BOARD;
}

void TableRenderer::setupCellStyle(
	RowIndex rowIndex,
	ColumnIndex columnIndex,
	RowLength columnHintLength,
	ColumnLength rowHintLength,
	Board board,
	CellType cellType
) const {
	const ImVec4 outOfBoardVec4 = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
	const ImVec4 rowHintColorVec4 = ImVec4(0.8f, 0.8f, 0.9f, 1.0f);
	const ImVec4 columnHintColorVec4 = ImVec4(0.8f, 0.9f, 0.8f, 1.0f);
	const ImVec4 blackVec4 = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	const ImVec4 whiteVec4 = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	const ImVec4 emptyVec4 = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);

	if (cellType == OUT_OF_BOARD) {
		ImGui::PushStyleColor(ImGuiCol_Button, outOfBoardVec4);
	}
	else if (cellType == ROW_PLACEMENT_COUNT || cellType == ROW_HINT) {
		ImGui::PushStyleColor(ImGuiCol_Button, rowHintColorVec4);
	}
	else if (cellType == COLUMN_PLACEMENT_COUNT || cellType == COLUMN_HINT) {
		ImGui::PushStyleColor(ImGuiCol_Button, columnHintColorVec4);
	}
	else {
		Coordinate coordinate = Coordinate(rowIndex - columnHintLength, columnIndex - rowHintLength);
		CellColor cellColor = board.getCell(coordinate).getColor();
		if (cellColor == Black) {
			ImGui::PushStyleColor(ImGuiCol_Button, blackVec4);
		}
		else if (cellColor == White) {
			ImGui::PushStyleColor(ImGuiCol_Button, whiteVec4);
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Button, emptyVec4);
		}
	}
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
}

std::string TableRenderer::setLabel(
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
) const {
	ImVec4 fontColorVec4 = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
	if (cellType == ROW_PLACEMENT_COUNT || cellType == ROW_HINT || cellType == COLUMN_PLACEMENT_COUNT || cellType == COLUMN_HINT) {
		ImGui::PushStyleColor(ImGuiCol_Text, fontColorVec4);
		ImGui::PushFont(FontData::getFontByCellSize(cell_size));

		if (cellType == ROW_HINT) {
			RowIndex HintSetIndex = rowIndex - columnHintLength;
			HintSet HintSet = rowHintSetList[HintSetIndex];

			ColumnIndex HintNumberIndex = ColumnIndex(columnIndex.getIndex() + HintSet.size() - rowHintLength.getLength());
			if (HintNumberIndex >= ColumnIndex(0)) {
				assert(HintNumberIndex < ColumnLength((int)HintSet.size()));
				return std::to_string(HintSet[HintNumberIndex.getIndex()].getNumber());
			}
		}

		if (cellType == COLUMN_HINT) {
			ColumnIndex HintSetIndex = columnIndex - rowHintLength;
			HintSet HintSet = columnHintSetList[HintSetIndex];

			RowIndex HintNumberIndex = RowIndex(rowIndex.getIndex() + HintSet.size() - columnHintLength.getLength());
			if (HintNumberIndex >= RowIndex(0)) {
				assert(HintNumberIndex < RowLength((int)HintSet.size()));
				return std::to_string(HintSet[HintNumberIndex.getIndex()].getNumber());
			}
		}

		if (cellType == ROW_PLACEMENT_COUNT) {
			RowIndex placementCountIndex = rowIndex - columnHintLength;
			PlacementCount placementCount = rowPlacementCountList[placementCountIndex];
			return std::to_string(placementCount.getCount());
		}

		if (cellType == COLUMN_PLACEMENT_COUNT) {
			ColumnIndex placementCountIndex = columnIndex - rowHintLength;
			PlacementCount placementCount = columnPlacementCountList[placementCountIndex];
			return std::to_string(placementCount.getCount());
		}
	}

	return "";
}

void TableRenderer::drawGridLine(
	RowIndex rowIndex,
	ColumnIndex columnIndex,
	RowLength columnHintLength,
	ColumnLength rowHintLength,
	RowLength boardRowLength,
	ColumnLength boardColumnLength
) const {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec2 p_min = ImGui::GetItemRectMin();
	ImVec2 p_max = ImGui::GetItemRectMax();

	float columnThickness = 1.0f;
	if (columnIndex.getIndex() >= rowHintLength.getLength() && (columnIndex.getIndex() - rowHintLength.getLength()) % 5 == 4) {
		columnThickness = 3.0f;
	}
	if (columnIndex.getIndex() == rowHintLength.getLength() - 1) {
		columnThickness = 6.0f;
	}
	if (columnIndex.getIndex() == rowHintLength.getLength() + boardColumnLength.getLength() - 1) {
		columnThickness = 6.0f;
	}
	draw_list->AddLine(ImVec2(p_max.x, p_min.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), columnThickness);


	float rowThickness = 1.0f;
	if (rowIndex.getIndex() >= columnHintLength.getLength() && (rowIndex.getIndex() - columnHintLength.getLength()) % 5 == 4) {
		rowThickness = 3.0f;
	}
	if (rowIndex.getIndex() == columnHintLength.getLength() - 1) {
		rowThickness = 6.0f;
	}
	if (rowIndex.getIndex() == columnHintLength.getLength() + boardRowLength.getLength() - 1) {
		rowThickness = 6.0f;
	}
	draw_list->AddLine(ImVec2(p_min.x, p_max.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), rowThickness);

}
