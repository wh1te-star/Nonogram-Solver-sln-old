#include "Rendering/RenderingSystem/RenderingSystem.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include <thread>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Rendering/FontData/FontData.h"
#include "Rendering/TableRenderer/TableRenderer.h"
#include "TestData/Repository/TestDataRepository.h"
#include "Algorithm/BacktrackAlgorithm.h"


RenderingSystem::RenderingSystem() :
	window(nullptr), 
	io(nullptr) 
{}

void RenderingSystem::glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int RenderingSystem::initialize() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "Docking UI Example", NULL, NULL);
    if (window == NULL) return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return 1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

	FontData::initFontData();

	return 0;
}

void RenderingSystem::renderingLoop() {
	bool first_time = true;

	RowHintLineList rowHintLineList = TestDataRepository::getRowHintLineList(TestDataRepository::LARGE);
	ColumnHintLineList columnHintLineList = TestDataRepository::getColumnHintLineList(TestDataRepository::LARGE);
	BacktrackBoard backtrackBoard = BacktrackBoard(
		NonogramBoard(Board(RowLength(20), ColumnLength(30)), rowHintLineList, columnHintLineList),
		RowPlacementCountList({
			PlacementCount(1), PlacementCount(2), PlacementCount(3), PlacementCount(4), PlacementCount(5),
			PlacementCount(6), PlacementCount(7), PlacementCount(8), PlacementCount(9), PlacementCount(10),
			PlacementCount(11), PlacementCount(12), PlacementCount(13), PlacementCount(14), PlacementCount(15),
			PlacementCount(16), PlacementCount(17), PlacementCount(18), PlacementCount(19), PlacementCount(20),
			}),
		ColumnPlacementCountList({
			PlacementCount(1), PlacementCount(2), PlacementCount(3), PlacementCount(4), PlacementCount(5),
			PlacementCount(6), PlacementCount(7), PlacementCount(8), PlacementCount(9), PlacementCount(10),
			PlacementCount(11), PlacementCount(12), PlacementCount(13), PlacementCount(14), PlacementCount(15),
			PlacementCount(16), PlacementCount(17), PlacementCount(18), PlacementCount(19), PlacementCount(20),
			PlacementCount(21), PlacementCount(22), PlacementCount(23), PlacementCount(24), PlacementCount(25),
			PlacementCount(26), PlacementCount(27), PlacementCount(28), PlacementCount(29), PlacementCount(30),
		})
	);
	TableRenderer tableRenderer = TableRenderer(backtrackBoard);

	BacktrackAlgorithm algorithm(backtrackBoard);
	std::thread worker_thread(&BacktrackAlgorithm::run, &algorithm);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking |
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus |
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
		if (ImGui::Button("Solve", ImVec2(-1, 0))) {
			//processState = PROCESS_ROW_SIDE_INIT;
		}
		ImGui::Spacing();
		if (ImGui::Button("Stop", ImVec2(-1, 0))) {
			//processState = PROCESS_NONE;
		}
		ImGui::End();

		tableRenderer.render();

		ImGui::Render();
		ImGui::EndFrame();

		if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
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

		printf("loop");
	}

	algorithm.request_stop();
	worker_thread.join();
}

void RenderingSystem::finalize() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
