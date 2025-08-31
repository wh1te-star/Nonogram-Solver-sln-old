#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <vector>
#include <string>

// グリッドのサイズ
int tableRowHeaderCount = 5;
int tableRowCount = 10;
int tableColumnHeaderCount = 5;
int tableColumnCount = 15;

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void render_nonogram_table() {
	const int tableRowCellCount = tableRowHeaderCount + tableRowCount;
	const int tableColumnCellCount = tableColumnHeaderCount + tableColumnCount;
    ImVec2 container_size = ImGui::GetContentRegionAvail();
    float min_container_dim = ImMin(container_size.x / tableColumnCellCount, container_size.y / tableRowCellCount);
    float cell_size = (min_container_dim);

    float table_width = cell_size * tableColumnCellCount;
    float table_height = cell_size * tableRowCellCount;

    float cursor_x = (container_size.x - table_width) * 0.5f;
    float cursor_y = (container_size.y - table_height) * 0.5f;

    if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
    if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));

    // ImGuiTableFlags_Borders を使用して全ての罫線を描画
    if (ImGui::BeginTable("NonogramGrid", tableColumnCellCount, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInner | ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX) | ImGuiTableFlags_NoHostExtendY) {

        // カラムの幅を固定で設定
        for (int i = 0; i < tableColumnCellCount; ++i) {
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        // 単一のループで全てのセルを描画
        for (int r = 0; r < tableRowCellCount; ++r) {
            ImGui::TableNextRow(); // ここで高さを指定しない
            for (int c = 0; c < tableColumnCellCount; ++c) {
                ImGui::TableSetColumnIndex(c);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
                
                // ヘッダー部分とゲーム盤部分で表示内容を分ける
                if (r < tableRowHeaderCount || c < tableColumnHeaderCount) {
                    // ヘッダー部分
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    // 実際にはここに数字を描画するロジックが入る
                    ImGui::Button("H", button_size); 
                    ImGui::PopStyleColor();
                } else {
                    // ゲーム盤部分
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    ImGui::Button(" ", button_size);
                    ImGui::PopStyleColor();
                }
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
