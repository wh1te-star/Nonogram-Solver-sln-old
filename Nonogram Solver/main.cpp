#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <vector>
#include <string>
#include <optional>
#include <coroutine>
#include <cstdio>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>

enum CellState {
    UNKNOWN,
    EMPTY,
    FILLED,
};

std::vector<std::vector<CellState>> nonogramGrid;

int tableRowHeaderCount = 5;
int tableRowCount = 10;
int tableColumnHeaderCount = 5;
int tableColumnCount = 15;

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

void findPlacementsInternal(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& cellStates,
    int hintIndex,
    int currentPos,
    std::vector<int>& currentPlacement,
    std::vector<std::vector<int>>& solutions
) {
    for (int x = 0; x < 10; x++) {
		nonogramGrid[rand() % tableRowCount][rand() % tableColumnCount] = FILLED;
    }

    /*
    if (hintIndex == hintNumbers.size()) {
        std::vector<int> finalPlacement = currentPlacement;
        finalPlacement.resize(totalLength, 0);

        bool isValid = true;
        for (int i = 0; i < totalLength; ++i) {
            if (cellStates[i] == CellState::EMPTY && finalPlacement[i] == 1) {
                isValid = false;
                break;
            }
            if (cellStates[i] == CellState::FILLED && finalPlacement[i] == 0) {
                isValid = false;
                break;
            }
        }
        
        if (isValid) {
            solutions.push_back(finalPlacement);
        }
        return;
    }

    int remainingHintsSize = std::accumulate(hintNumbers.begin() + hintIndex, hintNumbers.end(), 0);
    int remainingSpace = (int)hintNumbers.size() - hintIndex - 1;
    
    // 現在の位置から最後まで、ヒントを配置できる最大の場所を計算
    for (int i = currentPos; i <= totalLength - (remainingHintsSize + remainingSpace); ++i) {
        
        // 1. ブロックの前に連続したFILLEDセルがないかチェック
        if (i > currentPos && cellStates[i-1] == CellState::FILLED) {
            continue;
        }

        // 2. ブロック内にEMPTYセルがないかチェック
        bool hasConflict = false;
        for (int j = 0; j < hintNumbers[hintIndex]; ++j) {
            if (cellStates[i + j] == CellState::EMPTY) {
                hasConflict = true;
                break;
            }
        }
        if (hasConflict) {
            continue;
        }

        if (hintIndex < hintNumbers.size() - 1 && cellStates[i + hintNumbers[hintIndex]] == CellState::FILLED) {
            continue;
        }

        // 配置の生成
        std::vector<int> nextPlacement = currentPlacement;
        // ブロックの前の空白を追加
        nextPlacement.insert(nextPlacement.end(), i - currentPos, 0);
        // ブロックを追加
        nextPlacement.insert(nextPlacement.end(), hintNumbers[hintIndex], 1);
        // ブロックの後の空白を追加（最後のヒントでない場合）
        if (hintIndex < hintNumbers.size() - 1) {
            nextPlacement.push_back(0);
        }
        
        // 次の再帰呼び出し
        findPlacementsInternal(
            totalLength, 
            hintNumbers, 
            cellStates, 
            hintIndex + 1, 
            i + hintNumbers[hintIndex] + 1, 
            nextPlacement, 
            solutions
        );
    }
    */
}

// ユーザー向けの公開関数
std::vector<std::vector<int>> findPlacements(
    int length, 
    std::vector<int>& hintNumbers, 
    std::vector<CellState> cellStates
) {
    std::vector<std::vector<int>> solutions;
    std::vector<int> currentPlacement;
    findPlacementsInternal(length, hintNumbers, cellStates, 0, 0, currentPlacement, solutions);
    return solutions;
}

// ユーティリティ関数（テスト用）
std::vector<CellState> toCellStateVector(const std::string& s) {
    std::vector<CellState> result;
    for (char c : s) {
        if (c == '?') result.push_back(CellState::EMPTY);
        else if (c == '0') result.push_back(CellState::EMPTY);
        else if (c == '1') result.push_back(CellState::FILLED);
    }
    return result;
}

void printSolutions(const std::vector<std::vector<int>>& solutions) {
    for (const auto& solution : solutions) {
        for (int cell : solution) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
}

// non-void generator
template<typename T>
struct generator {
    struct promise_type {
        T value_;
        std::suspend_always yield_value(T value) {
            value_ = std::move(value);
            return {};
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { throw; }
        generator get_return_object() { return generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        void return_void() {}
    };

    generator(std::coroutine_handle<promise_type> handle) : handle_(handle) {}
    
    generator(generator&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}
    
    generator& operator=(generator&& other) noexcept {
        if (this != &other) {
            if (handle_) {
                handle_.destroy();
            }
            handle_ = std::exchange(other.handle_, nullptr);
        }
        return *this;
    }
    
    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;
    
    ~generator() {
        if (handle_) {
            handle_.destroy();
        }
    }
    
    bool next() {
        if (!handle_ || handle_.done()) {
            return false;
        }
        handle_.resume();
        return !handle_.done();
    }
    
    T value() const {
        return handle_.promise().value_;
    }

private:
    std::coroutine_handle<promise_type> handle_ = nullptr;
};

// void generator specialization
template<>
struct generator<void> {
    struct promise_type {
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() { throw; }
        generator get_return_object() { return generator{std::coroutine_handle<promise_type>::from_promise(*this)}; }
        void return_void() {}
    };

    generator(std::coroutine_handle<promise_type> handle) : handle_(handle) {}
    
    generator(generator&& other) noexcept : handle_(std::exchange(other.handle_, nullptr)) {}
    
    generator& operator=(generator&& other) noexcept {
        if (this != &other) {
            if (handle_) {
                handle_.destroy();
            }
            handle_ = std::exchange(other.handle_, nullptr);
        }
        return *this;
    }
    
    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;
    
    ~generator() {
        if (handle_) {
            handle_.destroy();
        }
    }
    
    bool next() {
        if (!handle_ || handle_.done()) {
            return false;
        }
        handle_.resume();
        return !handle_.done();
    }
    
private:
    std::coroutine_handle<promise_type> handle_ = nullptr;
};

generator<void> nonogram_solver() {
    std::vector<int> hints = { 1, 2, 3 };
	findPlacements(10, hints, toCellStateVector("?????"));
}

std::optional<generator<void>> solve() {
    return nonogram_solver();
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
                
                if(r < tableRowHeaderCount && c < tableColumnHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));
                } else if (r < tableRowHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.6f, 0.9f, 1.0f));
                } else if (c < tableColumnHeaderCount) {
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.9f, 0.6f, 0.6f, 1.0f));
                } else {
                    if(nonogramGrid[r - tableRowHeaderCount][c - tableColumnHeaderCount] == FILLED) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                    } else if(nonogramGrid[r - tableRowHeaderCount][c - tableColumnHeaderCount] == EMPTY) {
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                    } else {
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

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    nonogramGrid.resize(tableRowCount, std::vector<CellState>(tableColumnCount, EMPTY));
    srand(static_cast<unsigned int>(time(0)));

    bool first_time = true;
    double last_update_time = glfwGetTime();
    const double update_interval = 0.1;

    std::optional<generator<void>> solver_gen;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        double current_time = glfwGetTime();
        if (solver_gen.has_value() && current_time - last_update_time >= update_interval) {
            solver_gen->next();
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
            if (!solver_gen.has_value()) {
                solver_gen.emplace(nonogram_solver());
            }
        }
        ImGui::Spacing();
        if (ImGui::Button("Stop", ImVec2(-1, 0))) {
            solver_gen.reset();
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
