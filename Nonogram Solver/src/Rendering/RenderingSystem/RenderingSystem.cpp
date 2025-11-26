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
#include "Algorithm/Backtrack/BacktrackAlgorithm/BacktrackAlgorithm.h"
#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedBacktrackStack/SharedBacktrackStack.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"


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

	TestDataRepository::TestDataType dataType = TestDataRepository::Difficult;
	RowHintSetList rowHintSetList = TestDataRepository::getRowHintSetList(dataType);
	ColumnHintSetList columnHintSetList = TestDataRepository::getColumnHintSetList(dataType);
	BacktrackBoard backtrackBoard = BacktrackBoard(
		NonogramBoard(
			Board(
				RowLength(rowHintSetList.size()),
				ColumnLength(columnHintSetList.size())),
			rowHintSetList,
			columnHintSetList
		),
		RowPlacementCountList(std::vector<PlacementCount>(rowHintSetList.size(), PlacementCount(0))),
		ColumnPlacementCountList(std::vector<PlacementCount>(columnHintSetList.size(), PlacementCount(0)))
	);
	SharedBacktrackBoard sharedBacktrackBoard = SharedBacktrackBoard(backtrackBoard);
	SharedBacktrackStack sharedBacktrackStack = SharedBacktrackStack(
		BacktrackStack(
			backtrackBoard.getRowLength(),
			backtrackBoard.getColumnLength()
		)
	);

	SharedHighlightIndexes sharedHighlightIndexes = SharedHighlightIndexes();
	TableRenderer tableRenderer = TableRenderer();

	BacktrackAlgorithm algorithm = BacktrackAlgorithm(
		sharedBacktrackBoard,
		sharedBacktrackStack,
		sharedHighlightIndexes
	);
	std::thread worker_thread(&BacktrackAlgorithm::run, &algorithm);

	int count = 0;

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

		tableRenderer.render(
			sharedBacktrackBoard,
			sharedBacktrackStack,
			sharedHighlightIndexes
		);

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
