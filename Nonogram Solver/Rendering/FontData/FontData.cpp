#include "Rendering/FontData/FontData.h"

#include <ctime>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

ImFont* FontData::fonts[(FontData::maxFontSize - FontData::minFontSize) / FontData::fontSizeStep + 1] = {};

const ImWchar FontData::glyph_ranges_numbers[] = {
	0x0030, 0x0039,
	0,
};

void FontData::initFontData() {
	assert((maxFontSize - minFontSize) % fontSizeStep == 0);
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig font_cfg;
	font_cfg.OversampleH = 1;
	font_cfg.OversampleV = 1;
	font_cfg.PixelSnapH = true;
	for (int fontSize = minFontSize, index = 0; fontSize <= maxFontSize; fontSize += fontSizeStep, index++) {
		fonts[index] = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\consola.ttf", static_cast<float>(fontSize), &font_cfg, glyph_ranges_numbers);
		if (fonts[index] == nullptr) {
			fprintf(stderr, "Failed to load font at size %d\n", fontSize);
		}
	}
}

ImFont* FontData::getFontByCellSize(int cellSize) {
	if (cellSize >= 120.0f) {
		return fonts[10];
	} else if (cellSize >= 110.0f) {
		return fonts[9];
	} else if (cellSize >= 100.0f) {
		return fonts[8];
	} else if (cellSize >= 90.0f) {
		return fonts[7];
	} else if (cellSize >= 80.0f) {
		return fonts[6];
	} else if (cellSize >= 70.0f) {
		return fonts[5];
	} else if (cellSize >= 60.0f) {
		return fonts[4];
	} else if (cellSize >= 50.0f) {
		return fonts[3];
	} else if (cellSize >= 40.0f) {
		return fonts[2];
	} else if (cellSize >= 20.0f) {
		return fonts[1];
	} else {
		return fonts[0];
	}
}
