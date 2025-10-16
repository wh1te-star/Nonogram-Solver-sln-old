#include "Algorithm/BacktrackAlgorithm.h"

#include <atomic>
#include <thread>
#include <chrono>


BacktrackAlgorithm::BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard)
	: sharedBacktrackBoard(sharedBacktrackBoard) {}

void BacktrackAlgorithm::run() {
	recursiveSolve(0, 100);
}

void BacktrackAlgorithm::recursiveSolve(int count, int max) {
    if (terminate) return;
    if (count >= max) return;

    sharedBacktrackBoard.applyCell(
        Coordinate(RowIndex(count / 10), ColumnIndex(count % 10)),
        Cell(Black)
	);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    recursiveSolve(count + 1, max);
}

/*
long long countPlacements(
	const Placement& placement,
	const HintLine& hintLine
) {
	int numHints = hintLine.size();
    
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

std::vector<Placement> BacktrackAlgorithm::FindPlacementsExhaustive(
	const Placement& placement,
	const HintLine& hintLine
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
*/

void BacktrackAlgorithm::request_stop() {
	terminate = true;
}
