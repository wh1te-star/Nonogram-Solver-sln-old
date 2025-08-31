#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <vector>
#include <string>

// グリッドのサイズ
int tableRowHeaderCount = 8;
int tableRowCount = 17;
int tableColumnHeaderCount = 6;
int tableColumnCount = 21;

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void render_nonogram_table() {
    const int tableRowCellCount = tableRowHeaderCount + tableRowCount;
    const int tableColumnCellCount = tableColumnHeaderCount + tableColumnCount;
    ImVec2 container_size = ImGui::GetContentRegionAvail();
    
    // セルのサイズを動的に計算し、整数に丸める
    float min_container_dim = ImMin(container_size.x / tableColumnCellCount, container_size.y / tableRowCellCount);
    float cell_size = round(min_container_dim); // ここでセルのサイズを整数に丸める

    float table_width = cell_size * tableColumnCellCount;
    float table_height = cell_size * tableRowCellCount;

    float cursor_x = (container_size.x - table_width) * 0.5f;
    float cursor_y = (container_size.y - table_height) * 0.5f;

    if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
    if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));

    if (ImGui::BeginTable("NonogramGrid", tableColumnCellCount, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoBordersInBody)) {

        for (int i = 0; i < tableColumnCellCount; ++i) {
            // カラムの幅を固定された整数値のセルサイズに設定
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        for (int r = 0; r < tableRowCellCount; ++r) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
            for (int c = 0; c < tableColumnCellCount; ++c) {
                ImGui::TableSetColumnIndex(c);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
                
                if(r < tableRowHeaderCount && c < tableColumnHeaderCount) {
                    // Top-left corner (header intersection)
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
                } else if (r < tableRowHeaderCount) {
                    // Row headers
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.9f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.5f, 0.5f, 0.8f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.4f, 0.4f, 0.7f, 1.0f));
                } else if (c < tableColumnHeaderCount) {
                    // Column headers
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.5f, 0.5f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.7f, 0.4f, 0.4f, 1.0f));
				}
                else {
					if ((r + c) % 2 == 0) {
						// Gray for even positions
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.6f, 0.6f, 0.6f, 1.0f));
					} else {
						// White for odd positions
						ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.8f, 0.8f, 1.0f));
					}
                }
                
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);

                char label[32];
                if (r < tableRowHeaderCount || c < tableColumnHeaderCount) {
                    sprintf_s(label, "H##%d,%d", r, c);
                } else {
                    sprintf_s(label, " ##%d,%d", r, c);
                }

                ImGui::Button(label, button_size);
                
                ImGui::PopStyleVar();
                ImGui::PopStyleColor(3);

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImVec2 p_min = ImGui::GetItemRectMin();
                ImVec2 p_max = ImGui::GetItemRectMax();

                // 線の座標はImGuiが計算したピクセル単位の座標なので、そのまま使う
                // もしくは ImGui::GetCursorScreenPos() を使って計算することも可能
                
                // 垂直の罫線 (右辺)
                float columnThickness = 3.0f;
				if (c == tableColumnHeaderCount - 1) columnThickness = 9.0f;
				if (c >= tableColumnHeaderCount && (c - tableColumnHeaderCount) % 5 == 4) columnThickness = 6.0f;
                draw_list->AddLine(ImVec2(p_max.x, p_min.y), ImVec2(p_max.x, p_max.y), IM_COL32(0, 0, 0, 255), columnThickness);
                
                // 水平の罫線 (下辺)
                float rowThickness = 3.0f;
				if (r == tableRowHeaderCount - 1) rowThickness = 9.0f;
				if (r >= tableRowHeaderCount && (r - tableRowHeaderCount) % 5 == 4) rowThickness = 6.0f;
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

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    bool first_time = true;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

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
