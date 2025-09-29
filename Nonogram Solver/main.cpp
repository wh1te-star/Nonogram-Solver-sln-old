#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <vector>
#include <stack>
#include <string>
#include <optional>
#include <coroutine>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <sstream>
#include "Board.h"

/*
std::string columnHintNumbersString = R"###(
  ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,  1,   ,   ,   ,   ,   ,   ,   ,   ,   
  ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,   ,  2,   ,  2,   ,   ,   ,   ,   ,   ,   ,   ,   
  ,   ,   ,   ,   ,   ,   ,   ,  2,  2,   ,   ,  2,   ,  2,   ,   ,  2,  2,  2,  1,  2,  1,   ,   ,   ,   ,   ,   ,   
  ,   ,   ,   ,   ,   ,  2,   ,  1,  1,  2,  2,  1,  2,  1,  2,  1,  2,  2,  1,  1,  1,  1,  1,  2,  1,   ,   ,   ,   
  ,   ,   ,   ,   ,  2,  2,  2,  1,  2,  1,  1,  1,  1,  1,  1,  5,  2,  1,  1,  1,  2,  2,  2,  1,  1,  2,   ,   ,   
  ,   ,   ,   ,  3,  2,  1,  1,  1,  1,  1,  2,  1,  1,  1,  2,  1,  1,  1,  2,  1,  1,  2,  1,  2,  1,  1,  2,   ,   
  ,   ,  4,  4,  6,  2,  1,  2,  1,  1,  3,  1,  2,  2,  2,  1,  3,  1,  1,  2,  1,  2,  3,  1,  2,  1,  1,  1,  2,   
12, 14,  4,  3,  2,  2,  2,  4,  2,  1,  2,  1,  1,  1,  1,  1,  2,  1,  2,  4,  2,  2,  2,  3,  4,  7,  7,  2,  2,  5
)###";
std::string rowHintNumbersString = R"###(
  ,   ,   ,   ,   ,   ,   ,   ,   ,  8
  ,   ,   ,   ,   , 14,  2,  1,  1,  2
  ,   ,   ,   , 14,  2,  1,  1,  1,  2
  ,   ,   ,   ,   ,  4,  2,  2,  2,  2
  ,   ,   ,   ,  4,  1,  1,  2,  2,  1
  ,   ,   ,  3, 11,  2,  2,  1,  1,  1
  ,   ,   ,   ,  2,  2,  1,  2,  2,  1
  ,   ,   ,  2,  2,  2,  1,  1,  1,  2
  ,   ,   ,   ,  2,  1,  2,  1,  2,  2
  ,   ,   ,   ,   ,  2,  1,  2,  1,  2
  ,   ,   ,   ,   ,   ,   ,  2,  1,  8
  ,   ,   ,   ,   ,   ,  2,  1,  1,  2
  ,   ,   ,   ,   ,   ,   ,  2, 19,  2
 2,  1,  1,  1,  1,  1,  1,  1,  1,  2
  ,  3,  1,  1,  1,  3,  1,  1,  1,  3
  ,   ,   ,  4,  1,  3,  1,  3,  1,  4
  ,   ,   ,   ,  8,  1,  1,  1,  1,  8
  ,   ,   ,   ,  6,  1,  1,  1,  1,  6
  ,   ,   ,   ,   ,  2,  2,  1,  2,  2
  ,   ,   ,   ,   ,   ,  3,  1,  1,  3
)###";
std::vector<std::vector<int>> columnHintNumbers;
std::vector<std::vector<int>> rowHintNumbers;

int tableRowHeaderCount;
int tableColumnHeaderCount;

int rowPlacementCells = 1;
int columnPlacementCountCells = 1;
std::vector<int> rowPlacementCounts;
std::vector<int> columnPlacementCounts;

Board nonogramGrid;

enum PROCESS_STATE {
    PROCESS_NONE,
    PROCESS_ROW_SIDE_INIT,
    PROCESS_ROW_INIT,
    PROCESS_ROW,
    PROCESS_ROW_DEINIT,
    PROCESS_ROW_SIDE_DEINIT,
    PROCESS_COLUMN_SIDE_INIT,
    PROCESS_COLUMN_INIT,
    PROCESS_COLUMN,
    PROCESS_COLUMN_DEINIT,
    PROCESS_COLUMN_SIDE_DEINIT,
};
PROCESS_STATE processState = PROCESS_NONE;
int processingRow = -1;
int processingColumn = -1;

ImFont* fontSize10 = nullptr;
ImFont* fontSize15 = nullptr;
ImFont* fontSize20 = nullptr;
ImFont* fontSize25 = nullptr;
ImFont* fontSize30 = nullptr;
ImFont* fontSize35 = nullptr;
ImFont* fontSize40 = nullptr;
ImFont* fontSize45 = nullptr;
ImFont* fontSize50 = nullptr;
ImFont* fontSize55 = nullptr;
ImFont* fontSize60 = nullptr;
ImFont* fontSize65 = nullptr;
ImFont* fontSize70 = nullptr;

const ImWchar glyph_ranges_numbers[] = {
    0x0030, 0x0039, // 0-9
    0x0020, 0x0020, // Space
    0x002D, 0x002D, // Minus
    0,
};

std::vector<std::vector<int>> parseHints(const std::string& hintString) {
    std::vector<std::vector<int>> hintMatrix;
    std::stringstream ss(hintString);
    std::string line;

    while (std::getline(ss, line)) {
        line.erase(0, line.find_first_not_of(" \t\n\r\f\v"));
        line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1);

        if (line.empty()) {
            continue;
        }

        std::vector<int> row;
        std::stringstream line_ss(line);
        std::string cell;

        while (std::getline(line_ss, cell, ',')) {
            cell.erase(0, cell.find_first_not_of(" \t\n\r\f\v"));
            cell.erase(cell.find_last_not_of(" \t\n\r\f\v") + 1);

            if (cell.empty()) {
                row.push_back(0); 
            } else {
                row.push_back(std::stoi(cell));
            }
        }
        hintMatrix.push_back(row);
    }
    return hintMatrix;
}

void initializeHints() {
	std::vector<std::vector<int>> tempColumnHintNumbers = parseHints(columnHintNumbersString);
    columnHintNumbers.resize(tempColumnHintNumbers.back().size(), std::vector<int>());
    for(int k = 0; k < tempColumnHintNumbers.size(); k++) {
        for(int i = 0; i < tempColumnHintNumbers[k].size(); i++) {
			if (tempColumnHintNumbers[k][i] == 0) continue;
			columnHintNumbers[i].push_back(tempColumnHintNumbers[k][i]);
		}
        if (tempColumnHintNumbers[k].size() > columnHintNumbers.size()) {
        }
	}

    tableColumnHeaderCount = -1;
    for (int i = 0; i < columnHintNumbers.size(); i++) {
        if ((int)columnHintNumbers[i].size() > tableColumnHeaderCount) {
            tableColumnHeaderCount = columnHintNumbers[i].size();
        }
    }

    std::vector<std::vector<int>> tempRowHintNumbers = parseHints(rowHintNumbersString);
	rowHintNumbers.resize(tempRowHintNumbers.size(), std::vector<int>());

    tableRowHeaderCount = -1;
    for(int k = 0; k < tempRowHintNumbers.size(); k++) {
        for(int i = 0; i < tempRowHintNumbers[k].size(); i++) {
			if (tempRowHintNumbers[k][i] == 0) continue;
			rowHintNumbers[k].push_back(tempRowHintNumbers[k][i]);
		}
        if ((int)tempRowHintNumbers[k].size() > tableRowHeaderCount) {
            tableRowHeaderCount = tempRowHintNumbers[k].size();
        }
	}

    rowPlacementCounts.resize(nonogramGrid.size());
    columnPlacementCounts.resize(nonogramGrid[0].size());
}

struct SearchState {
    int current_pos;
    int hint_index;
    std::vector<CellState> current_placement;
};

long long countPlacements(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& determinedStates
) {
    int numHints = hintNumbers.size();
    
    std::vector<std::vector<long long>> dp(numHints + 1, std::vector<long long>(totalLength + 1, 0));

    dp[0][0] = 1;
    for (int j = 1; j <= totalLength; ++j) {
        if (canPlace(WHITE, determinedStates[j-1])) {
            dp[0][j] = 1;
        } else {
            break;
        }
    }

    for (int i = 1; i <= numHints; ++i) {
        int currentHintLength = hintNumbers[i-1];
        
        for (int j = 1; j <= totalLength; ++j) {
            if (canPlace(WHITE, determinedStates[j-1])) {
                dp[i][j] = dp[i][j-1];
            }
            
            if (j >= currentHintLength) {
                bool isSeparated = (j == currentHintLength) || (canPlace(WHITE, determinedStates[j - currentHintLength - 1]));

                bool blockFits = true;
                for (int k = 0; k < currentHintLength; ++k) {
                    if (!canPlace(BLACK, determinedStates[j - 1 - k])) {
                        blockFits = false;
                        break;
                    }
                }
                
                if (isSeparated && blockFits) {
                    int prevJ = j - currentHintLength - 1;
                    if (prevJ < 0) {
                        // 最初からブロックを置く場合
                        dp[i][j] += dp[i-1][0];
                    } else {
                        dp[i][j] += dp[i-1][prevJ];
                    }
                }
            }
        }
    }

    return dp[numHints][totalLength];
}

std::vector<std::vector<CellState>> FindPlacementsExhaustive(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& determinedStates
) {
    std::vector<std::vector<CellState>> solutions;
    std::stack<SearchState> stk;
    stk.push({0, 0, {}});

    while (!stk.empty()) {
        SearchState current = stk.top();
        stk.pop();

        // Base Case: All hints have been placed
        if (current.hint_index == hintNumbers.size()) {
            bool allRemainingAreWhite = true;
            for (size_t i = current.current_pos; i < totalLength; ++i) {
                if (determinedStates[i] == BLACK) {
                    allRemainingAreWhite = false;
                    break;
                }
            }
            if (!allRemainingAreWhite) {
                continue;
            }
            
            std::vector<CellState> finalPlacement = current.current_placement;
            finalPlacement.resize(totalLength, WHITE);
            solutions.push_back(finalPlacement);
            continue;
        }

        int currentHintNumber = hintNumbers[current.hint_index];
        int remainingHintsLength = 0;
        for (size_t i = current.hint_index; i < hintNumbers.size(); ++i) {
            remainingHintsLength += hintNumbers[i];
        }
        if (hintNumbers.size() > current.hint_index) {
            remainingHintsLength += (hintNumbers.size() - current.hint_index - 1);
        }

        // Iterate through all possible starting positions for the current hint
        for (int placePosition = current.current_pos; placePosition <= totalLength - remainingHintsLength; ++placePosition) {
            
            // Check for conflicts in the leading whitespace
            bool canProceed = true;
            for (int i = current.current_pos; i < placePosition; ++i) {
                if (!canPlace(WHITE, determinedStates[i])) {
                    canProceed = false;
                    break;
                }
            }
            if (!canProceed) continue;

            // Check for conflicts within the hint block (BLACK cells)
            for (int i = 0; i < currentHintNumber; ++i) {
                if (!canPlace(BLACK, determinedStates[placePosition + i])) {
                    canProceed = false;
                    break;
                }
            }
            if (!canProceed) continue;

            // Check for conflicts with the mandatory whitespace separator
            if (current.hint_index < hintNumbers.size() - 1 && 
                !canPlace(WHITE, determinedStates[placePosition + currentHintNumber])) {
                continue;
            }

            // If valid, create and push the next state
            SearchState nextState;
            nextState.hint_index = current.hint_index + 1;
            
            // Build the new placement from the current one
            nextState.current_placement = current.current_placement;
            for (int i = current.current_pos; i < placePosition; ++i) {
                nextState.current_placement.push_back(WHITE);
            }
            for (int i = 0; i < currentHintNumber; ++i) {
                nextState.current_placement.push_back(BLACK);
            }
            if (nextState.current_placement.size() < totalLength && nextState.hint_index < hintNumbers.size()) {
                nextState.current_placement.push_back(WHITE);
            }

            nextState.current_pos = nextState.current_placement.size();
            stk.push(nextState);
        }
    }
    std::reverse(solutions.begin(), solutions.end());
    return solutions;
}

bool canPlaceBlock(
    const std::vector<CellState>& determinedCells,
    int startPos,
    int hintLength
) {
    // Check if the block fits within the line
    if (startPos + hintLength > determinedCells.size() || startPos < 0) {
        return false;
    }

    // Check for conflicts with WHITE cells in the determined area
    for (int i = 0; i < hintLength; ++i) {
        if (determinedCells[startPos + i] == WHITE) {
            return false;
        }
    }
    return true;
}

std::vector<int> getLeftmostPositions(
    const std::vector<CellState>& determinedCells,
    const std::vector<int>& hints
) {
    std::vector<int> positions;
    int currentPos = 0;
    for (size_t i = 0; i < hints.size(); ++i) {
        int hint = hints[i];
        while (true) {
            if (canPlaceBlock(determinedCells, currentPos, hint)) {
                if (i > 0 && determinedCells[currentPos - 1] == BLACK) {
                    currentPos++;
                    continue;
                }
                break;
            }
            currentPos++;
            if (currentPos > determinedCells.size()) {
                 return {};
            }
        }
        positions.push_back(currentPos);
        currentPos += hint + 1;
    }
    return positions;
}

std::vector<int> getRightmostPositions(
    const std::vector<CellState>& determinedCells,
    const std::vector<int>& hints
) {
    std::vector<int> positions(hints.size());
    int currentPos = determinedCells.size() - 1;
    for (int i = hints.size() - 1; i >= 0; --i) {
        int hint = hints[i];
		int blockStartPos = currentPos - hint + 1;
		int blockEndPos = currentPos;
        while (true) {
            if (canPlaceBlock(determinedCells, blockStartPos, hint)) {
                if (i < hints.size() - 1 && determinedCells[currentPos + 1] == BLACK) {
                    currentPos--;
                    continue;
                }
                break;
            }
            currentPos--;
            if (currentPos < 0) {
                 return {};
            }
        }
        positions[i] = currentPos - hint + 1;
        currentPos -= (hint + 1);
    }
    return positions;
}

std::vector<CellState> constructPlacement(
    int totalLength,
    const std::vector<int>& hints,
    const std::vector<int>& positions
) {
    std::vector<CellState> placement(totalLength, WHITE);
    for (size_t i = 0; i < hints.size(); ++i) {
        for (int j = 0; j < hints[i]; ++j) {
            placement[positions[i] + j] = BLACK;
        }
    }
    return placement;
}

std::vector<CellState> determineByOverlap(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& determinedStates
) {
    std::vector<CellState> determined = determinedStates;

    std::vector<int> leftmostPositions = getLeftmostPositions(determinedStates, hintNumbers);
    if (leftmostPositions.empty()) {
        return std::vector<CellState>(totalLength, UNKNOWN);
    }

    std::vector<int> rightmostPositions = getRightmostPositions(determinedStates, hintNumbers);
    if (rightmostPositions.empty()) {
        return std::vector<CellState>(totalLength, UNKNOWN);
    }

    for(int i = 0; i < leftmostPositions.front(); i++) {
        determined[i] = WHITE;
	}
    for(int i = totalLength-1; i > rightmostPositions.back() + hintNumbers.back(); i--) {
        determined[i] = WHITE;
	}
    for(int k = 0; k < hintNumbers.size(); k++) {
        int leftStart = leftmostPositions[k];
        int leftEnd = leftStart + hintNumbers[k] - 1;
        int rightStart = rightmostPositions[k];
        int rightEnd = rightStart + hintNumbers[k] - 1;
        for(int i = leftStart; i <= leftEnd; i++) {
            if (i >= rightStart && i <= rightEnd) {
                determined[i] = BLACK;
            }
        }
	}

    return determined;
}

std::vector<CellState> determineCellStates(
    const std::vector<std::vector<CellState>> placements
) {
    int length = placements[0].size();
    std::vector<CellState> result(length, UNKNOWN);
    if (placements.empty()) return result;

    for (int i = 0; i < length; ++i) {
        CellState firstState = placements[0][i];
        bool allSame = true;
        for (const auto& placement : placements) {
            if (placement[i] != firstState) {
                allSame = false;
                break;
            }
        }
        if (allSame) {
            result[i] = firstState;
        }
    }
    return result;
}

bool isSolved(std::vector<CellState> states) {
	for (const auto& cell : states) {
		if (cell == UNKNOWN) {
			return false;
		}
    }
    return true;
}

void render_nonogram_table() {
	const int boardRowCount = nonogramGrid.size();
	const int boardColumnCount = nonogramGrid[0].size();
    const int rowTotalCount = tableRowHeaderCount + boardRowCount + rowPlacementCells;
    const int columnTotalCount = tableColumnHeaderCount + boardColumnCount + columnPlacementCountCells;
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
                    if (columnIndex - tableColumnHeaderCount == processingColumn) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
                    }
                    else {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.9f, 1.0f));
                    }
                } else if (columnIndex < tableColumnHeaderCount) {
                    if (rowIndex - tableRowHeaderCount == processingRow) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
                    }
                    else {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
                    }
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
                    if (cell_size >= 120.0f) {
                        ImGui::PushFont(fontSize60);
                    } else if (cell_size >= 110.0f) {
                        ImGui::PushFont(fontSize55);
                    } else if (cell_size >= 100.0f) {
                        ImGui::PushFont(fontSize50);
                    } else if (cell_size >= 90.0f) {
                        ImGui::PushFont(fontSize45);
                    } else if (cell_size >= 80.0f) {
                        ImGui::PushFont(fontSize40);
                    } else if(cell_size >= 70.0f) {
                        ImGui::PushFont(fontSize35);
                    } else if(cell_size >= 60.0f) {
                        ImGui::PushFont(fontSize30);
                    } else if(cell_size >= 50.0f) {
                        ImGui::PushFont(fontSize25);
                    } else if(cell_size >= 40.0f) {
                        ImGui::PushFont(fontSize20);
                    } else if(cell_size >= 20.0f) {
                        ImGui::PushFont(fontSize15);
                    } else {
                        ImGui::PushFont(fontSize10);
                    }

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
}

void frameUpdate() {
	std::vector<CellState> determinedCells = std::vector<CellState>();
    switch (processState) {
    case PROCESS_NONE:
        break;

    case PROCESS_ROW_SIDE_INIT:
		processingRow = 0;
		processingColumn = -1;

		processState = PROCESS_ROW_INIT;
        break;

    case PROCESS_ROW_INIT:
        while (processingRow < nonogramGrid.size() && isSolved(nonogramGrid[processingRow]))
            processingRow++;
        if (processingRow == nonogramGrid.size()) {
			processState = PROCESS_ROW_SIDE_DEINIT;
            break;
        }

		processState = PROCESS_ROW;
        break;

    case PROCESS_ROW:
		determinedCells = determineByOverlap(
			nonogramGrid[processingRow].size(),
			rowHintNumbers[processingRow],
			nonogramGrid[processingRow]
		);
        for (int i = 0; i < nonogramGrid[processingRow].size(); i++) {
			nonogramGrid[processingRow][i] = determinedCells[i];
        }

		processState = PROCESS_ROW_DEINIT;
        break;

    case PROCESS_ROW_DEINIT:
        processingRow++;

		processState = PROCESS_ROW_INIT;
        break;

    case PROCESS_ROW_SIDE_DEINIT:

		processState = PROCESS_COLUMN_SIDE_INIT;
        break;

    case PROCESS_COLUMN_SIDE_INIT:
		processingColumn = 0;
		processingRow = -1;

        processState = PROCESS_COLUMN_INIT;
        break;

    case PROCESS_COLUMN_INIT:
        while (processingColumn < nonogramGrid[0].size() && isSolved(extractColumn(nonogramGrid, processingColumn)))
            processingColumn++;
        if (processingColumn == nonogramGrid[0].size()) {
			processState = PROCESS_COLUMN_SIDE_DEINIT;
            break;
        }

		processState = PROCESS_COLUMN;
        break;

    case PROCESS_COLUMN:
        determinedCells = determineByOverlap(
			nonogramGrid.size(),
			columnHintNumbers[processingColumn],
			extractColumn(nonogramGrid, processingColumn)
		);
        for (int i = 0; i < nonogramGrid.size(); i++) {
			nonogramGrid[i][processingColumn] = determinedCells[i];
        }

		processState = PROCESS_COLUMN_DEINIT;
        break;

    case PROCESS_COLUMN_DEINIT:
        processingColumn++;

		processState = PROCESS_COLUMN_INIT;
        break;

    case PROCESS_COLUMN_SIDE_DEINIT:

		processState = PROCESS_ROW_SIDE_INIT;
        break;

    default:
        assert(false);
        break;
    }
}
*/
void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Docking UI Example", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;    
    
    ImFontConfig font_cfg;
    font_cfg.OversampleH = 1;
    font_cfg.OversampleV = 1;
    font_cfg.PixelSnapH = true;

    /*
    fontSize10 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 10.0f, &font_cfg, glyph_ranges_numbers);
    fontSize15 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 15.0f, &font_cfg, glyph_ranges_numbers);
    fontSize20 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 20.0f, &font_cfg, glyph_ranges_numbers);
    fontSize25 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 25.0f, &font_cfg, glyph_ranges_numbers);
    fontSize30 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 30.0f, &font_cfg, glyph_ranges_numbers);
    fontSize35 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 35.0f, &font_cfg, glyph_ranges_numbers);
    fontSize40 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 40.0f, &font_cfg, glyph_ranges_numbers);
    fontSize45 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 45.0f, &font_cfg, glyph_ranges_numbers);
    fontSize50 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 50.0f, &font_cfg, glyph_ranges_numbers);
    fontSize55 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 55.0f, &font_cfg, glyph_ranges_numbers);
    fontSize60 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 60.0f, &font_cfg, glyph_ranges_numbers);
    fontSize65 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 65.0f, &font_cfg, glyph_ranges_numbers);
    fontSize70 = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/Arial.ttf", 70.0f, &font_cfg, glyph_ranges_numbers);
    */

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

	//initializeHints();

    //nonogramGrid.resize(rowHintNumbers.size(), std::vector<CellState>(columnHintNumbers.size(), UNKNOWN));
    srand(static_cast<unsigned int>(time(0)));

    bool first_time = true;
    double last_update_time = glfwGetTime();
    const double update_interval = 0.1;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

    double current_time = glfwGetTime();
    if (current_time - last_update_time >= update_interval) {
        //frameUpdate();
        last_update_time = current_time;
    }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                         ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
                                         ImGuiWindowFlags_NoNavFocus;
                                         
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        ImGui::PopStyleVar(3);
        
        ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        
        if (first_time) {
            first_time = false;
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->WorkSize);

            ImGuiID left_id, right_id;
            ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, &left_id, &right_id);

            ImGui::DockBuilderDockWindow("Control Panel", left_id);
            ImGui::DockBuilderDockWindow("Nonogram Board", right_id);
            ImGui::DockBuilderFinish(dockspace_id);
        }
        
        ImGui::End();

        ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_None);
        ImGui::Text("Control Buttons");
        ImGui::Spacing();
        if(ImGui::Button("Solve", ImVec2(-1, 0))) {
			//processState = PROCESS_ROW_SIDE_INIT;
        }
        ImGui::Spacing();
        if (ImGui::Button("Stop", ImVec2(-1, 0))) {
            //processState = PROCESS_NONE;
        }
        ImGui::End();

        ImGui::Begin("Nonogram Board", NULL, ImGuiWindowFlags_None);
        //render_nonogram_table();
        ImGui::End();

        ImGui::Render();
        ImGui::EndFrame();    
        
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
        
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
