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
std::vector<std::vector<int>> columnHintNumbers;
std::vector<std::vector<int>> rowHintNumbers;

int tableRowHeaderCount;
int tableColumnHeaderCount;

int rowPlacementCells = 1;
int columnPlacementCountCells = 1;
std::vector<int> rowPlacementCounts;
std::vector<int> columnPlacementCounts;

Board nonogramGrid;

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

long long countPlacements(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& determinedStates
) {
    int numHints = hintNumbers.size();
    
    std::vector<std::vector<long long>> dp(numHints + 1, std::vector<long long>(totalLength + 1, 0));

    dp[0][0] = 1;
    for (int j = 1; j <= totalLength; ++j) {
        if (canPlace(WHITE, determinedStates[j-1])) {
            dp[0][j] = 1;
        } else {
            break;
        }
    }

    for (int i = 1; i <= numHints; ++i) {
        int currentHintLength = hintNumbers[i-1];
        
        for (int j = 1; j <= totalLength; ++j) {
            if (canPlace(WHITE, determinedStates[j-1])) {
                dp[i][j] = dp[i][j-1];
            }
            
            if (j >= currentHintLength) {
                bool isSeparated = (j == currentHintLength) || (canPlace(WHITE, determinedStates[j - currentHintLength - 1]));

                bool blockFits = true;
                for (int k = 0; k < currentHintLength; ++k) {
                    if (!canPlace(BLACK, determinedStates[j - 1 - k])) {
                        blockFits = false;
                        break;
                    }
                }
                
                if (isSeparated && blockFits) {
                    int prevJ = j - currentHintLength - 1;
                    if (prevJ < 0) {
                        // 最初からブロックを置く場合
                        dp[i][j] += dp[i-1][0];
                    } else {
                        dp[i][j] += dp[i-1][prevJ];
                    }
                }
            }
        }
    }

    return dp[numHints][totalLength];
}

std::vector<std::vector<CellState>> FindPlacementsExhaustive(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& determinedStates
) {
    std::vector<std::vector<CellState>> solutions;
    std::stack<SearchState> stk;
    stk.push({0, 0, {}});

    while (!stk.empty()) {
        SearchState current = stk.top();
        stk.pop();

        // Base Case: All hints have been placed
        if (current.hint_index == hintNumbers.size()) {
            bool allRemainingAreWhite = true;
            for (size_t i = current.current_pos; i < totalLength; ++i) {
                if (determinedStates[i] == BLACK) {
                    allRemainingAreWhite = false;
                    break;
                }
            }
            if (!allRemainingAreWhite) {
                continue;
            }
            
            std::vector<CellState> finalPlacement = current.current_placement;
            finalPlacement.resize(totalLength, WHITE);
            solutions.push_back(finalPlacement);
            continue;
        }

        int currentHintNumber = hintNumbers[current.hint_index];
        int remainingHintsLength = 0;
        for (size_t i = current.hint_index; i < hintNumbers.size(); ++i) {
            remainingHintsLength += hintNumbers[i];
        }
        if (hintNumbers.size() > current.hint_index) {
            remainingHintsLength += (hintNumbers.size() - current.hint_index - 1);
        }

        // Iterate through all possible starting positions for the current hint
        for (int placePosition = current.current_pos; placePosition <= totalLength - remainingHintsLength; ++placePosition) {
            
            // Check for conflicts in the leading whitespace
            bool canProceed = true;
            for (int i = current.current_pos; i < placePosition; ++i) {
                if (!canPlace(WHITE, determinedStates[i])) {
                    canProceed = false;
                    break;
                }
            }
            if (!canProceed) continue;

            // Check for conflicts within the hint block (BLACK cells)
            for (int i = 0; i < currentHintNumber; ++i) {
                if (!canPlace(BLACK, determinedStates[placePosition + i])) {
                    canProceed = false;
                    break;
                }
            }
            if (!canProceed) continue;

            // Check for conflicts with the mandatory whitespace separator
            if (current.hint_index < hintNumbers.size() - 1 && 
                !canPlace(WHITE, determinedStates[placePosition + currentHintNumber])) {
                continue;
            }

            // If valid, create and push the next state
            SearchState nextState;
            nextState.hint_index = current.hint_index + 1;
            
            // Build the new placement from the current one
            nextState.current_placement = current.current_placement;
            for (int i = current.current_pos; i < placePosition; ++i) {
                nextState.current_placement.push_back(WHITE);
            }
            for (int i = 0; i < currentHintNumber; ++i) {
                nextState.current_placement.push_back(BLACK);
            }
            if (nextState.current_placement.size() < totalLength && nextState.hint_index < hintNumbers.size()) {
                nextState.current_placement.push_back(WHITE);
            }

            nextState.current_pos = nextState.current_placement.size();
            stk.push(nextState);
        }
    }
    std::reverse(solutions.begin(), solutions.end());
    return solutions;
}

bool canPlaceBlock(
    const std::vector<CellState>& determinedCells,
    int startPos,
    int hintLength
) {
    // Check if the block fits within the line
    if (startPos + hintLength > determinedCells.size() || startPos < 0) {
        return false;
    }

    // Check for conflicts with WHITE cells in the determined area
    for (int i = 0; i < hintLength; ++i) {
        if (determinedCells[startPos + i] == WHITE) {
            return false;
        }
    }
    return true;
}

std::vector<int> getLeftmostPositions(
    const std::vector<CellState>& determinedCells,
    const std::vector<int>& hints
) {
    std::vector<int> positions;
    int currentPos = 0;
    for (size_t i = 0; i < hints.size(); ++i) {
        int hint = hints[i];
        while (true) {
            if (canPlaceBlock(determinedCells, currentPos, hint)) {
                if (i > 0 && determinedCells[currentPos - 1] == BLACK) {
                    currentPos++;
                    continue;
                }
                break;
            }
            currentPos++;
            if (currentPos > determinedCells.size()) {
                 return {};
            }
        }
        positions.push_back(currentPos);
        currentPos += hint + 1;
    }
    return positions;
}

std::vector<int> getRightmostPositions(
    const std::vector<CellState>& determinedCells,
    const std::vector<int>& hints
) {
    std::vector<int> positions(hints.size());
    int currentPos = determinedCells.size() - 1;
    for (int i = hints.size() - 1; i >= 0; --i) {
        int hint = hints[i];
		int blockStartPos = currentPos - hint + 1;
		int blockEndPos = currentPos;
        while (true) {
            if (canPlaceBlock(determinedCells, blockStartPos, hint)) {
                if (i < hints.size() - 1 && determinedCells[currentPos + 1] == BLACK) {
                    currentPos--;
                    continue;
                }
                break;
            }
            currentPos--;
            if (currentPos < 0) {
                 return {};
            }
        }
        positions[i] = currentPos - hint + 1;
        currentPos -= (hint + 1);
    }
    return positions;
}

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

std::vector<CellState> determineByOverlap(
    int totalLength,
    const std::vector<int>& hintNumbers,
    const std::vector<CellState>& determinedStates
) {
    std::vector<CellState> determined = determinedStates;

    std::vector<int> leftmostPositions = getLeftmostPositions(determinedStates, hintNumbers);
    if (leftmostPositions.empty()) {
        return std::vector<CellState>(totalLength, UNKNOWN);
    }

    std::vector<int> rightmostPositions = getRightmostPositions(determinedStates, hintNumbers);
    if (rightmostPositions.empty()) {
        return std::vector<CellState>(totalLength, UNKNOWN);
    }

    for(int i = 0; i < leftmostPositions.front(); i++) {
        determined[i] = WHITE;
	}
    for(int i = totalLength-1; i > rightmostPositions.back() + hintNumbers.back(); i--) {
        determined[i] = WHITE;
	}
    for(int k = 0; k < hintNumbers.size(); k++) {
        int leftStart = leftmostPositions[k];
        int leftEnd = leftStart + hintNumbers[k] - 1;
        int rightStart = rightmostPositions[k];
        int rightEnd = rightStart + hintNumbers[k] - 1;
        for(int i = leftStart; i <= leftEnd; i++) {
            if (i >= rightStart && i <= rightEnd) {
                determined[i] = BLACK;
            }
        }
	}

    return determined;
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
