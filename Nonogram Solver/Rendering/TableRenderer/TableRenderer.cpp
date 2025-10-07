#include "Rendering/TableRenderer/TableRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include <string>


TableRenderer::TableRenderer(
	BacktrackBoard backtrackBoard
) : backtrackBoard(std::move(backtrackBoard)) {}

void TableRenderer::render() {
	ImGui::Begin("Nonogram Board", NULL, ImGuiWindowFlags_None);

    /*
	const NonogramBoard& nonogramBoard = backtrackBoard.getNonogramBoard();

	const Board& nonogramGrid = nonogramBoard.getBoard();
	const RowHintLineList& rowHintLines = nonogramBoard.getRowHintLineList();
	const ColumnHintLineList& columnHintLines = nonogramBoard.getColumnHintLineList();
	const RowPlacementCountList& rowPlacementCountList = backtrackBoard.getRowPlacementCountList();
	const ColumnPlacementCountList& columnPlacementCountList = backtrackBoard.getColumnPlacementCountList();

	const RowLength boardRowLength = nonogramBoard.getRowLength();

    ImVec2 container_size = ImGui::GetContentRegionAvail();
    
    float min_container_dim = ImMin(container_size.x / columnTotalCount, container_size.y / rowTotalCount);
    float cell_size = round(min_container_dim);

    float table_width = cell_size * columnTotalCount;
    float table_height = cell_size * rowTotalCount;

    float cursor_x = (container_size.x - table_width) * 0.5f;
    float cursor_y = (container_size.y - table_height) * 0.5f;

    if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
    if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));

    if (ImGui::BeginTable("NonogramGrid", columnTotalCount, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoBordersInBody)) {

        for (int i = 0; i < columnTotalCount; ++i) {
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        for (int rowIndex = 0; rowIndex < rowTotalCount; rowIndex++) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
            for (int columnIndex = 0; columnIndex < columnTotalCount; columnIndex++) {
                ImGui::TableSetColumnIndex(columnIndex);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
                
                if(rowIndex < tableRowHeaderCount && columnIndex < tableColumnHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
                } else if (rowIndex < tableRowHeaderCount) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.9f, 1.0f));
                } else if (columnIndex < tableColumnHeaderCount) {
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
                } else {
                    if(nonogramGrid[rowIndex - tableRowHeaderCount][columnIndex - tableColumnHeaderCount] == BLACK) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                    } else if(nonogramGrid[rowIndex - tableRowHeaderCount][columnIndex - tableColumnHeaderCount] == WHITE) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    } else {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
                    }
                }
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

                std::string label = "";
                if (rowIndex < tableRowHeaderCount || columnIndex < tableColumnHeaderCount) {
					ImGui::PushFont(FontData.getFontByCellSize(cell_size));

                    if (rowIndex >= tableRowHeaderCount) {
						int rowHintIndex = rowIndex - tableRowHeaderCount;
						int columnHintIndex = tableColumnHeaderCount - columnIndex - 1;
                        if(columnHintIndex < rowHintNumbers[rowHintIndex].size()) {
                            label = std::to_string(rowHintNumbers[rowHintIndex][columnHintIndex]);
						}
                    }

                    if (columnIndex >= tableColumnHeaderCount) {
						int columnHintIndex = columnIndex - tableColumnHeaderCount;
                        int rowHintIndex = columnHintNumbers[columnHintIndex].size() - (tableRowHeaderCount - rowIndex - 1) - 1;
                        if(rowHintIndex < columnHintNumbers[columnHintIndex].size()) {
                            label = std::to_string(columnHintNumbers[columnHintIndex][rowHintIndex]);
						}
                    }
                }
                ImGui::Button(label.c_str(), button_size);
                
                if (rowIndex < tableRowHeaderCount || columnIndex < tableColumnHeaderCount) {
                    ImGui::PopFont();
                }
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();

                float columnThickness = 1.0f;
                if (columnIndex == tableColumnHeaderCount - 1) columnThickness = 6.0f;
                if (columnIndex >= tableColumnHeaderCount && (columnIndex - tableColumnHeaderCount) % 5 == 4) columnThickness = 3.0f;
                draw_list->AddLine(ImVec2(p_max.x, p_min.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), columnThickness);
                
                float rowThickness = 1.0f;
                if (rowIndex == tableRowHeaderCount - 1) rowThickness = 6.0f;
                if (rowIndex >= tableRowHeaderCount && (rowIndex - tableRowHeaderCount) % 5 == 4) rowThickness = 3.0f;
                draw_list->AddLine(ImVec2(p_min.x, p_max.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), rowThickness);
            }
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
    */

    ImVec2 container_size = ImGui::GetContentRegionAvail();
    
    float min_container_dim = ImMin(container_size.x / 15, container_size.y / 15);
    float cell_size = round(min_container_dim);

    float table_width = cell_size * 15;
    float table_height = cell_size * 15;

    float cursor_x = (container_size.x - table_width) * 0.5f;
    float cursor_y = (container_size.y - table_height) * 0.5f;

    if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
    if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));

    if (ImGui::BeginTable("NonogramGrid", 15, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoBordersInBody)) {

        for (int i = 0; i < 15; ++i) {
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        for (int rowIndex = 0; rowIndex < 15; rowIndex++) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
            for (int columnIndex = 0; columnIndex < 15; columnIndex++) {
                ImGui::TableSetColumnIndex(columnIndex);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));

                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

                std::string label = "10";
                ImGui::Button(label.c_str(), button_size);
                
                /*
                if (rowIndex < tableRowHeaderCount || columnIndex < tableColumnHeaderCount) {
                    ImGui::PopFont();
                }
                */
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();

                float columnThickness = 1.0f;
                float rowThickness = 1.0f;

                /*
                if (columnIndex == tableColumnHeaderCount - 1) columnThickness = 6.0f;
                if (columnIndex >= tableColumnHeaderCount && (columnIndex - tableColumnHeaderCount) % 5 == 4) columnThickness = 3.0f;
                
                if (rowIndex == tableRowHeaderCount - 1) rowThickness = 6.0f;
                if (rowIndex >= tableRowHeaderCount && (rowIndex - tableRowHeaderCount) % 5 == 4) rowThickness = 3.0f;
                */

                draw_list->AddLine(ImVec2(p_max.x, p_min.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), columnThickness);
                draw_list->AddLine(ImVec2(p_min.x, p_max.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), rowThickness);
            }
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();

	ImGui::End();
}

