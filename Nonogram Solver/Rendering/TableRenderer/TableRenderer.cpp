#include "Rendering/TableRenderer/TableRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include "Rendering/FontData/FontData.h"
#include <string>


TableRenderer::TableRenderer(
	BacktrackBoard backtrackBoard
) : backtrackBoard(std::move(backtrackBoard)) {}

void TableRenderer::render() {
	ImGui::Begin("Nonogram Board", NULL, ImGuiWindowFlags_None);


	const NonogramBoard& nonogramBoard = backtrackBoard.getNonogramBoard();

	const Board& board = nonogramBoard.getBoard();
	const RowHintLineList& rowHintLineList = nonogramBoard.getRowHintLineList();
	const ColumnHintLineList& columnHintLineList = nonogramBoard.getColumnHintLineList();
	const RowPlacementCountList& rowPlacementCountList = backtrackBoard.getRowPlacementCountList();
	const ColumnPlacementCountList& columnPlacementCountList = backtrackBoard.getColumnPlacementCountList();

    const RowLength boardRowLength = board.getRowLength();
    const ColumnLength boardColumnLength = board.getColumnLength();
    const RowLength columnHintLength = columnHintLineList.getMaxHintLineLength();
    const ColumnLength rowHintLength = rowHintLineList.getMaxHintLineLength();
    const RowLength rowPlacementCountLength = RowLength(1);
    const ColumnLength columnPlacementCountLength = ColumnLength(1);
	//const RowLength totalRowLength = boardRowLength + columnHintLength + rowPlacementCountLength;
	//const ColumnLength totalColumnLength = boardColumnLength + rowHintLength + columnPlacementCountLength;
    const RowLength totalRowLength = boardRowLength + columnHintLength;
    const ColumnLength totalColumnLength = boardColumnLength + rowHintLength;

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

                bool isColumnHintArea = rowIndex < columnHintLength;
                bool isRowHintArea = columnIndex < rowHintLength;
                if(isRowHintArea && isColumnHintArea) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
                } else if (isRowHintArea) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.9f, 1.0f));
                } else if (isColumnHintArea) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
                } else {
					Coordinate coordinate = Coordinate(rowIndex - columnHintLength, columnIndex - rowHintLength);
					CellColor cellColor = board.getCell(coordinate).getColor();
                    if(cellColor == Black) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                    } else if(cellColor == White) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    } else {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
                    }
                }
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

                std::string label = "";
                if (isRowHintArea || isColumnHintArea) {
					ImGui::PushFont(FontData::getFontByCellSize(cell_size));

                    if (isRowHintArea && !isColumnHintArea) {
                        RowIndex HintLineIndex = rowIndex - columnHintLength;
						HintLine hintLine = rowHintLineList[HintLineIndex];

                        ColumnIndex HintNumberIndex = ColumnIndex(columnIndex.getIndex() + hintLine.size() - rowHintLength.getLength());
                        if(HintNumberIndex >= ColumnIndex(0)) {
                            assert(HintNumberIndex < ColumnLength((int)hintLine.size()));
                            label = std::to_string(hintLine[HintNumberIndex].getNumber());
						}
                    }

                    if (isColumnHintArea && !isRowHintArea) {
                        ColumnIndex HintLineIndex = columnIndex - rowHintLength;
						HintLine hintLine = columnHintLineList[HintLineIndex];

                        RowIndex HintNumberIndex = RowIndex(rowIndex.getIndex() + hintLine.size() - columnHintLength.getLength());
                        if(HintNumberIndex >= RowIndex(0)) {
                            assert(HintNumberIndex < RowLength((int)hintLine.size()));
                            label = std::to_string(hintLine[HintNumberIndex].getNumber());
						}
                    }
                }
                ImGui::Button(label.c_str(), button_size);
                
                if (isRowHintArea || isColumnHintArea) {
                    ImGui::PopFont();
                }
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();

                /*
                float columnThickness = 1.0f;
                if (columnIndex == tableColumnHeaderCount - 1) columnThickness = 6.0f;
                if (columnIndex >= tableColumnHeaderCount && (columnIndex - tableColumnHeaderCount) % 5 == 4) columnThickness = 3.0f;
                draw_list->AddLine(ImVec2(p_max.x, p_min.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), columnThickness);
                
                float rowThickness = 1.0f;
                if (rowIndex == tableRowHeaderCount - 1) rowThickness = 6.0f;
                if (rowIndex >= tableRowHeaderCount && (rowIndex - tableRowHeaderCount) % 5 == 4) rowThickness = 3.0f;
                draw_list->AddLine(ImVec2(p_min.x, p_max.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), rowThickness);
                */
            }
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();


	ImGui::End();
}

