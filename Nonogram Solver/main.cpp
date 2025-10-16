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
#include "Board/Board/Board.h"
#include "Rendering/RenderingSystem/RenderingSystem.h"

/*
enum PROCESS_STATE {
    PROCESS_NONE,
    PROCESS_ROW_SIDE_INIT,
    PROCESS_ROW_INIT,
    PROCESS_ROW,
    PROCESS_ROW_DEINIT,
    PROCESS_ROW_SIDE_DEINIT,
    PROCESS_COLUMN_SIDE_INIT,
    PROCESS_COLUMN_INIT,
    PROCESS_COLUMN,
    PROCESS_COLUMN_DEINIT,
    PROCESS_COLUMN_SIDE_DEINIT,
};
PROCESS_STATE processState = PROCESS_NONE;
int processingRow = -1;
int processingColumn = -1;


struct SearchState {
    int current_pos;
    int hint_index;
    std::vector<CellState> current_placement;
};

std::vector<CellState> constructPlacement(
    int totalLength,
    const std::vector<int>& hints,
    const std::vector<int>& positions
) {
    std::vector<CellState> placement(totalLength, WHITE);
    for (size_t i = 0; i < hints.size(); ++i) {
        for (int j = 0; j < hints[i]; ++j) {
            placement[positions[i] + j] = BLACK;
        }
    }
    return placement;
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
}

void frameUpdate() {
	std::vector<CellState> determinedCells = std::vector<CellState>();
    switch (processState) {
    case PROCESS_NONE:
        break;

    case PROCESS_ROW_SIDE_INIT:
		processingRow = 0;
		processingColumn = -1;

		processState = PROCESS_ROW_INIT;
        break;

    case PROCESS_ROW_INIT:
        while (processingRow < nonogramGrid.size() && isSolved(nonogramGrid[processingRow]))
            processingRow++;
        if (processingRow == nonogramGrid.size()) {
			processState = PROCESS_ROW_SIDE_DEINIT;
            break;
        }

		processState = PROCESS_ROW;
        break;

    case PROCESS_ROW:
		determinedCells = determineByOverlap(
			nonogramGrid[processingRow].size(),
			rowHintNumbers[processingRow],
			nonogramGrid[processingRow]
		);
        for (int i = 0; i < nonogramGrid[processingRow].size(); i++) {
			nonogramGrid[processingRow][i] = determinedCells[i];
        }

		processState = PROCESS_ROW_DEINIT;
        break;

    case PROCESS_ROW_DEINIT:
        processingRow++;

		processState = PROCESS_ROW_INIT;
        break;

    case PROCESS_ROW_SIDE_DEINIT:

		processState = PROCESS_COLUMN_SIDE_INIT;
        break;

    case PROCESS_COLUMN_SIDE_INIT:
		processingColumn = 0;
		processingRow = -1;

        processState = PROCESS_COLUMN_INIT;
        break;

    case PROCESS_COLUMN_INIT:
        while (processingColumn < nonogramGrid[0].size() && isSolved(extractColumn(nonogramGrid, processingColumn)))
            processingColumn++;
        if (processingColumn == nonogramGrid[0].size()) {
			processState = PROCESS_COLUMN_SIDE_DEINIT;
            break;
        }

		processState = PROCESS_COLUMN;
        break;

    case PROCESS_COLUMN:
        determinedCells = determineByOverlap(
			nonogramGrid.size(),
			columnHintNumbers[processingColumn],
			extractColumn(nonogramGrid, processingColumn)
		);
        for (int i = 0; i < nonogramGrid.size(); i++) {
			nonogramGrid[i][processingColumn] = determinedCells[i];
        }

		processState = PROCESS_COLUMN_DEINIT;
        break;

    case PROCESS_COLUMN_DEINIT:
        processingColumn++;

		processState = PROCESS_COLUMN_INIT;
        break;

    case PROCESS_COLUMN_SIDE_DEINIT:

		processState = PROCESS_ROW_SIDE_INIT;
        break;

    default:
        assert(false);
        break;
    }
}
*/

int main() {
	RenderingSystem renderingSystem = RenderingSystem();
    int initResult = renderingSystem.initialize();
    if (initResult) {
        return initResult;
	}

	renderingSystem.renderingLoop();

	renderingSystem.finalize();

    return 0;
}
