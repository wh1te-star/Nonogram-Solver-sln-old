#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

// グリッドのサイズ
const int GRID_FULL_SIZE = 15; // ヘッダー含む全体のグリッドサイズ
const int HEADER_SIZE = 5;     // ヘッダーの行/列数

// セルの状態を定義
enum class CellState {
    Unknown,
    Filled,
    Marked,
    Empty
};

/// GLFWのエラーコールバック
void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void RenderNonogramUI() {
    // 1. メインのビューポートのサイズを取得
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    // 2. 次に描画するウィンドウの位置とサイズを設定
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    // 3. ウィンドウの装飾を非表示にするフラグ
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    // 4. ウィンドウの描画を開始
    ImGui::Begin("Nonogram UI", NULL, window_flags);

    // ウィンドウの利用可能な描画領域を取得
    ImVec2 window_size = ImGui::GetContentRegionAvail();

    // ウィンドウの縦横の短い方に合わせてマスのサイズを計算
    float min_size = ImMin(window_size.x, window_size.y);
    float cell_size = (min_size / GRID_FULL_SIZE) - 9.0f;

    // グリッドをテーブルとして描画
    if (ImGui::BeginTable("NonogramGrid", GRID_FULL_SIZE, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders)) {

        // カラムの幅を設定
        for (int i = 0; i < GRID_FULL_SIZE; ++i) {
            ImGui::TableSetupColumn("##", ImGuiTableColumnFlags_WidthFixed, cell_size);
        }

        // テーブルのセルを描画
        for (int r = 0; r < GRID_FULL_SIZE; ++r) {
            ImGui::TableNextRow();
            for (int c = 0; c < GRID_FULL_SIZE; ++c) {
                ImGui::TableSetColumnIndex(c);

                // Corrected logic for header cells
                if (r < HEADER_SIZE || c < HEADER_SIZE) {
                    // Header Part
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.9f, 0.9f, 0.9f, 1.0f));

                    // Use a button with the text as its label, ensuring a consistent size.
                    std::string header_id = "header_" + std::to_string(r) + "_" + std::to_string(c);
                    if (r < HEADER_SIZE && c < HEADER_SIZE) {
                        ImGui::Button(" ", ImVec2(cell_size, cell_size)); // Use space as a label
                    }
                    else if (r < HEADER_SIZE) {
                        ImGui::Button(std::to_string(c - HEADER_SIZE + 1).c_str(), ImVec2(cell_size, cell_size));
                    }
                    else {
                        ImGui::Button(std::to_string(r - HEADER_SIZE + 1).c_str(), ImVec2(cell_size, cell_size));
                    }
                    ImGui::PopStyleColor(3);
                }
                else {
                    // ゲームプレイエリア
                    int grid_r = r - HEADER_SIZE;
                    int grid_c = c - HEADER_SIZE;

                    // ご指定のロジックに基づいて色とテキストを決定
                    int mod_val = (grid_r + grid_c) % 3;

                    ImVec4 button_color;
                    const char* text_label = "";

                    if (mod_val == 0) {
                        button_color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
                    }
                    else if (mod_val == 1) {
                        button_color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
                        text_label = "X";
                    }
                    else {
                        button_color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
                    }

                    ImGui::PushStyleColor(ImGuiCol_Button, button_color);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));

                    std::string id = "cell_" + std::to_string(grid_r) + "_" + std::to_string(grid_c);
                    if (ImGui::Button(text_label, ImVec2(cell_size, cell_size))) {
                        // クリック時の動作をここに記述
                    }
                    ImGui::PopStyleColor(3);
                }
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}
int main() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // GLFWとOpenGLのバージョンヒント
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ウィンドウ作成
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Nonogram UI", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // GLADの初期化
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD\n");
        return 1;
    }

    // Dear ImGuiコンテキストの作成と初期化
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // メインループ
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // ImGuiの新しいフレームを開始
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // UIの描画関数を呼び出し
        RenderNonogramUI();

        // 描画と表示
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f); // 背景色
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // クリーンアップ
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}