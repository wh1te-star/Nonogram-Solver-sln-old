#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <vector>
#include <string>
#include <coroutine>

enum CellState {
    EMPTY,
    FILLED,
    MARKED
};

std::vector<std::vector<CellState> > nonogramGrid;

// グリッドのサイズ
int tableRowHeaderCount = 5;
int tableRowCount = 10;
int tableColumnHeaderCount = 5;
int tableColumnCount = 15;

// グローバルにフォントを保持するポインタ
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

// 数字と記号のグリフ（文字）範囲を指定
const ImWchar glyph_ranges_numbers[] = {
    0x0030, 0x0039, // 0-9
    0x0020, 0x0020, // Space
    0x002D, 0x002D, // Minus
    0,
};

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// A simple solver function that changes one cell's state
void solve_step() {
    // This is a placeholder for your actual solver logic.
    // It finds the first EMPTY cell and changes its state.
    for (int r = 0; r < tableRowCount; ++r) {
        for (int c = 0; c < tableColumnCount; ++c) {
            if (nonogramGrid[r][c] == EMPTY) {
                nonogramGrid[r][c] = FILLED;
                return; // Change one cell per step
            }
        }
    }
}

void render_nonogram_table() {
    const int tableRowTotalCount = tableRowHeaderCount + tableRowCount;
    const int tableColumnTotalCount = tableColumnHeaderCount + tableColumnCount;
    ImVec2 container_size = ImGui::GetContentRegionAvail();
    
    float min_container_dim = ImMin(container_size.x / tableColumnTotalCount, container_size.y / tableRowTotalCount);
    float cell_size = round(min_container_dim);

    float table_width = cell_size * tableColumnTotalCount;
    float table_height = cell_size * tableRowTotalCount;

    float cursor_x = (container_size.x - table_width) * 0.5f;
    float cursor_y = (container_size.y - table_height) * 0.5f;

    if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
    if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));

    if (ImGui::BeginTable("NonogramGrid", tableColumnTotalCount, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoBordersInBody)) {

        for (int i = 0; i < tableColumnTotalCount; ++i) {
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        for (int r = 0; r < tableRowTotalCount; ++r) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
            for (int c = 0; c < tableColumnTotalCount; ++c) {
                ImGui::TableSetColumnIndex(c);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
                
                // Color logic for different grid sections
                if(r < tableRowHeaderCount && c < tableColumnHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f)); // Header intersection
                } else if (r < tableRowHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.9f, 1.0f)); // Column headers
                } else if (c < tableColumnHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.6f, 0.6f, 1.0f)); // Row headers
                } else {
                    // Correctly map CellState to colors
                    if(nonogramGrid[r - tableRowHeaderCount][c - tableColumnHeaderCount] == FILLED) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                    } else if(nonogramGrid[r - tableRowHeaderCount][c - tableColumnHeaderCount] == MARKED) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    } else { // EMPTY
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
                    }
                }
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

                char label[32];
                if (r < tableRowHeaderCount || c < tableColumnHeaderCount) {
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

                    int number_value = ((r + c) * 10) % 1000;
                    sprintf_s(label, "%d##%d,%d", number_value, r, c);
                } else {
                    sprintf_s(label, " ##%d,%d", r, c);
                }

                ImGui::Button(label, button_size);
                
                if (r < tableRowHeaderCount || c < tableColumnHeaderCount) {
                    ImGui::PopFont();
                }
                
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();

                float columnThickness = 1.0f;
                if (c == tableColumnHeaderCount - 1) columnThickness = 6.0f;
                if (c >= tableColumnHeaderCount && (c - tableColumnHeaderCount) % 5 == 4) columnThickness = 3.0f;
                draw_list->AddLine(ImVec2(p_max.x, p_min.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), columnThickness);
                
                float rowThickness = 1.0f;
                if (r == tableRowHeaderCount - 1) rowThickness = 6.0f;
                if (r >= tableRowHeaderCount && (r - tableRowHeaderCount) % 5 == 4) rowThickness = 3.0f;
                draw_list->AddLine(ImVec2(p_min.x, p_max.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), rowThickness);
            }
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();
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

    // REMOVE THIS LINE:
    // io.Fonts->Build();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

	nonogramGrid.resize(tableRowCount, std::vector<CellState>(tableColumnCount, EMPTY));

    bool first_time = true;
    double last_update_time = glfwGetTime();
    const double update_interval = 0.1; // Update every 0.1 seconds

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Timer logic to update the grid state
        double current_time = glfwGetTime();
        if (current_time - last_update_time >= update_interval) {
            solve_step();
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
        ImGui::Button("Solve", ImVec2(-1, 0));
        ImGui::Button("Reset", ImVec2(-1, 0));
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
