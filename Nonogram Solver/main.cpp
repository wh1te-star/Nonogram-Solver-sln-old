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

enum CellState {
    UNKNOWN,
    WHITE,
    BLACK,
};

std::string columnHintNumbersString = R"###(
	 ,  ,  ,  , 3, 5, 6,  ,  ,  ,  ,  ,  ,  ,  
	2,  , 7, 7, 5, 3, 1, 6, 6, 5, 3,  ,  ,  , 2
	2, 7, 2, 2, 1, 2, 2, 4, 1, 3, 5, 7, 7, 7, 2
)###";
std::string rowHintNumbersString = R"###(
	 , 2, 2
	 ,  , 7
	 ,  , 7
	 ,  , 7
	3, 5, 3
	5, 3, 5
	6, 1, 6
	 , 6, 6
	6, 1, 6
	5, 1, 5
	3, 1, 3
	 ,  , 2
	 ,  , 2
	 ,  , 4
	 ,  , 2
)###";
std::vector<std::vector<int>> columnHintNumbers;
std::vector<std::vector<int>> rowHintNumbers;

int tableRowHeaderCount;
int tableColumnHeaderCount;

std::vector<std::vector<CellState>> all_solutions;


std::vector<std::vector<CellState>> nonogramGrid;

int processingRow = -1;
int processingColumn = -1;
int solution_index = -1;

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

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

std::vector<CellState> extractColumn(const std::vector<std::vector<CellState>>& vec2d, size_t columnIndex) {
    std::vector<CellState> result;
    if (vec2d.empty() || columnIndex >= vec2d[0].size()) {
        return result;
    }
    for (const auto& row : vec2d) {
        result.push_back(row[columnIndex]);
    }
    return result;
}

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
	tableColumnHeaderCount = tempColumnHintNumbers.size();
    columnHintNumbers.resize(tempColumnHintNumbers.back().size(), std::vector<int>());
    for(int k = 0; k < tempColumnHintNumbers.size(); k++) {
        for(int i = 0; i < tempColumnHintNumbers[k].size(); i++) {
			if (tempColumnHintNumbers[k][i] == 0) continue;
			columnHintNumbers[i].push_back(tempColumnHintNumbers[k][i]);
		}
	}

    std::vector<std::vector<int>> tempRowHintNumbers = parseHints(rowHintNumbersString);
	tableRowHeaderCount = tempRowHintNumbers[0].size();
	rowHintNumbers.resize(tempRowHintNumbers.size(), std::vector<int>());
    for(int k = 0; k < tempRowHintNumbers.size(); k++) {
        for(int i = 0; i < tempRowHintNumbers[k].size(); i++) {
			if (tempRowHintNumbers[k][i] == 0) continue;
			rowHintNumbers[k].push_back(tempRowHintNumbers[k][i]);
		}
	}
}

bool canPlace(CellState placeState, CellState determinedState) {
    if (determinedState == UNKNOWN) {
        return true;
    }
    
    if (placeState == WHITE) {
        return determinedState == WHITE;
    }
    
    if (placeState == BLACK) {
        return determinedState == BLACK;
    }
    
    assert(false);
    return false;
}

struct SearchState {
    int current_pos;
    int hint_index;
    std::vector<CellState> current_placement;
};

std::vector<std::vector<CellState>> findPlacements(
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
    const int rowTotalCount = tableRowHeaderCount + boardRowCount;
    const int columnTotalCount = tableColumnHeaderCount + boardColumnCount;
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
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
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

void gotoColumnProcess() {
    processingColumn = 0;
	processingRow = -1;
	solution_index = -1;
}

void gotoRowProcess() {
    processingRow = 0;
    processingColumn = -1;
    solution_index = -1;
}

void frameUpdate() {
    if (processingRow == nonogramGrid.size()) {
		gotoColumnProcess();
    } else if (processingRow != -1) {
        if (solution_index == -1) {
			all_solutions = findPlacements(
				nonogramGrid[0].size(),
				rowHintNumbers[processingRow],
				nonogramGrid[processingRow]
			);
			solution_index = 0;
        }
        else if (solution_index == all_solutions.size()) {
			std::vector<CellState> determinedStates = determineCellStates(all_solutions);
            for (int i = 0; i < nonogramGrid[processingRow].size(); i++) {
				nonogramGrid[processingRow][i] = determinedStates[i];
            }

            processingRow++;
			solution_index = -1;
        } else {
            for (int i = 0; i < nonogramGrid[processingRow].size();i++) {
				nonogramGrid[processingRow][i] = all_solutions[solution_index][i];
			}
			solution_index++;
		}
    }
    else if (processingColumn == nonogramGrid[0].size()) {
		gotoRowProcess();
    } else if (processingColumn != -1) {
        if (solution_index == -1) {
			all_solutions = findPlacements(
				nonogramGrid.size(),
				columnHintNumbers[processingColumn],
				extractColumn(nonogramGrid, processingColumn)
			);
			solution_index = 0;
        }
        else if (solution_index == all_solutions.size()) {
			std::vector<CellState> determinedStates = determineCellStates(all_solutions);
            for (int i = 0; i < nonogramGrid.size(); i++) {
				nonogramGrid[i][processingColumn] = determinedStates[i];
            }

            processingColumn++;
			solution_index = -1;
        } else {
            for (int i = 0; i < nonogramGrid.size();i++) {
				nonogramGrid[i][processingColumn] = all_solutions[solution_index][i];
			}
			solution_index++;
		}
    }
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

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

	initializeHints();

    nonogramGrid.resize(rowHintNumbers.size(), std::vector<CellState>(columnHintNumbers.size(), UNKNOWN));
    srand(static_cast<unsigned int>(time(0)));

    bool first_time = true;
    double last_update_time = glfwGetTime();
    const double update_interval = 0.1;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

    double current_time = glfwGetTime();
    if (current_time - last_update_time >= update_interval) {
        frameUpdate();
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
			processingRow = 0;
        }
        ImGui::Spacing();
        if (ImGui::Button("Stop", ImVec2(-1, 0))) {
			processingColumn = -1;
			processingRow = -1;
			solution_index = -1;
        }
        ImGui::End();

        ImGui::Begin("Nonogram Board", NULL, ImGuiWindowFlags_None);
        render_nonogram_table();
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
