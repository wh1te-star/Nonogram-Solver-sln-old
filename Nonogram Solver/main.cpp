#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <vector>
#include <string>

// グリッドのサイズ
const int GRID_FULL_SIZE = 15;
const int HEADER_SIZE = 5;

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void render_nonogram_table() {
    ImVec2 container_size = ImGui::GetContentRegionAvail();
    float min_container_dim = ImMin(container_size.x, container_size.y);
    float cell_size = (min_container_dim / GRID_FULL_SIZE);

    float table_width = cell_size * GRID_FULL_SIZE;
    float table_height = cell_size * GRID_FULL_SIZE;

    float cursor_x = (container_size.x - table_width) * 0.5f;
    float cursor_y = (container_size.y - table_height) * 0.5f;

    if (cursor_x > 0) ImGui::SetCursorPosX(cursor_x);
    if (cursor_y > 0) ImGui::SetCursorPosY(cursor_y);
    
    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0, 0));
    
    // ImGuiTableFlags_BordersInnerV と BordersInnerH を使用
    if (ImGui::BeginTable("NonogramGrid", GRID_FULL_SIZE, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_NoHostExtendX)) {
        
        // カラムの幅を固定で設定
        for (int i = 0; i < GRID_FULL_SIZE; ++i) {
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        // ここがポイント: ヘッダー部分を ImGui に描画させる
        for (int r = 0; r < HEADER_SIZE; ++r) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
            for (int c = 0; c < GRID_FULL_SIZE; ++c) {
                ImGui::TableSetColumnIndex(c);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
                
                if (r < HEADER_SIZE && c < HEADER_SIZE) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    ImGui::Button(" ", button_size);
                    ImGui::PopStyleColor();
                } else if (r < HEADER_SIZE) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    std::string label = std::to_string(c - HEADER_SIZE + 1);
                    ImGui::Button(label.c_str(), button_size);
                    ImGui::PopStyleColor();
                } else {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    std::string label = std::to_string(r - HEADER_SIZE + 1);
                    ImGui::Button(label.c_str(), button_size);
                    ImGui::PopStyleColor();
                }
            }
        }

        // ここからがゲームプレイエリアの描画
        for (int r = HEADER_SIZE; r < GRID_FULL_SIZE; ++r) {
            ImGui::TableNextRow(ImGuiTableRowFlags_None, cell_size);
            for (int c = 0; c < GRID_FULL_SIZE; ++c) {
                ImGui::TableSetColumnIndex(c);
                
                ImVec2 button_size = ImVec2(cell_size, cell_size);
                
                if (c < HEADER_SIZE) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    std::string label = std::to_string(r - HEADER_SIZE + 1);
                    ImGui::Button(label.c_str(), button_size);
                    ImGui::PopStyleColor();
                } else {
                    ImVec4 button_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    const char* text_label = "";
                    if ((r - HEADER_SIZE + c - HEADER_SIZE) % 3 == 0) button_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                    else if ((r - HEADER_SIZE + c - HEADER_SIZE) % 3 == 1) { button_color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f); text_label = "X"; }
                    ImGui::PushStyleColor(ImGuiCol_Button, button_color);
                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
                    ImGui::Button(text_label, button_size);
                    ImGui::PopStyleColor(2);
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
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // ★ ドッキングを有効化

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    static bool first_time = true;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. メインのドックノードを定義
        ImGuiID dockspace_id = ImGui::GetID("MainDockspace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

        // 2. 初回起動時にレイアウトを構築
        if (first_time) {
            first_time = false;
            ImGui::DockBuilderRemoveNode(dockspace_id);
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImVec2(1280, 720));

            ImGuiID left_id, right_id;
            // 左右に分割 (左側に20%のスペースを割り当てる)
            ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.2f, &left_id, &right_id);

            // 各ノードにウィンドウをドッキング
            ImGui::DockBuilderDockWindow("Control Panel", left_id);
            ImGui::DockBuilderDockWindow("Nonogram Board", right_id);
            ImGui::DockBuilderFinish(dockspace_id);
        }

        // 3. 各UIコンポーネントを独立したウィンドウとして描画
        ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_None);
        ImGui::Text("Control Buttons");
        ImGui::Spacing();
        ImGui::Button("Solve", ImVec2(-1, 0));
        ImGui::Button("Reset", ImVec2(-1, 0));
        ImGui::End();

        ImGui::Begin("Nonogram Board", NULL, ImGuiWindowFlags_None);
        render_nonogram_table(); // 表を描画する関数
        ImGui::End();

        ImGui::Render();
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