#include "Algorithm/BacktrackAlgorithm/BacktrackAlgorithm.h"

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

PlacementCount BacktrackAlgorithm::countPlacements(
	const Placement& placement,
	const HintLine& hintLine
) {
// Initialize the DP table: Count[HintsUsed][CellsConsidered]
hintsCount = length(HintLine)
totalLength = length(Placement)
Initialize Count[hintsCount + 1][totalLength + 1] to 0

// --- Base Case: Count[0][j] (Placing 0 hints) ---
Count[0][0] = 1

For CellsConsidered = 1 to totalLength:
    // 0 hints valid only if the cell can be White (i.e., not 'Black').
    If Placement[CellsConsidered - 1] is NOT 'Black':
        Count[0][CellsConsidered] = 1
    Else:
        Break // Cannot place 0 hints if a cell is forced Black
    End If
End For

// --- Main DP Loop ---
For HintsUsed = 1 to hintsCount:
    currentHintSize = HintLine[HintsUsed - 1]

    For CellsConsidered = 1 to totalLength:

        // **Option 1: The last cell is White (Separator).**
        // If the cell is not forced to be Black, inherit the count from N[i][j-1].
        If Placement[CellsConsidered - 1] is NOT 'Black':
            Count[HintsUsed][CellsConsidered] = Count[HintsUsed][CellsConsidered - 1]
        End If

        // **Option 2: The last cell ends the current Black block.**
        If CellsConsidered >= currentHintSize:
            
            // The length of the line *before* the required separation cell
            prevCellsConsidered = CellsConsidered - currentHintSize - 1 
            blockStartIndex = CellsConsidered - currentHintSize

            // Check A: The Black block fits in the Placement
            blockFits = True
            For k = blockStartIndex to CellsConsidered - 1:
                // Cell must be placable as 'Black' (i.e., not 'White')
                If Placement[k] is 'White':
                    blockFits = False
                    Break
                End If
            End For
            
            // Check B: Proper separation from the previous hint (required in B&W)
            isSeparated = (prevCellsConsidered < 0) // Block starts at the line beginning
                      OR (Placement[prevCellsConsidered] is NOT 'Black') // Cell before block can be White

            If blockFits AND isSeparated:
                // Add the count from the previous hint placed up to the separation point.
                If prevCellsConsidered < 0:
                    // Block starts at index 0. We add N[i-1][0].
                    Count[HintsUsed][CellsConsidered] = Count[HintsUsed][CellsConsidered] + Count[HintsUsed - 1][0]
                Else:
                    // Block follows a separator cell. We add N[i-1][prevCellsConsidered].
                    Count[HintsUsed][CellsConsidered] = Count[HintsUsed][CellsConsidered] + Count[HintsUsed - 1][prevCellsConsidered]
                End If
            End If
        End If
    End For
End For

// The final answer is the count for all hints placed in the total length.
Return Count[hintsCount][totalLength]

	int hintsCount = hintLine.size();
    int totalLength = placement.size();
    
    std::vector<std::vector<PlacementCount>> partialCount(
        hintsCount + 1,
        std::vector<PlacementCount>(
            totalLength + 1,
            PlacementCount(0)
        )
    );

    partialCount[0][0] = PlacementCount(1);
    for (int index = 1; index <= totalLength; index++) {
		Cell cell = placement[CellIndex(index - 1)];
        if(cell.canColor(White)) {
            partialCount[0][index] = PlacementCount(1);
        } else {
            break;
        }
    }

    for (int hintNumberIndex = 1; hintNumberIndex <= hintsCount; hintNumberIndex++) {
        HintNumber currentHintNumber = hintLine[CellIndex(hintNumberIndex-1)];
        
        for (int boardLength = 1; boardLength <= totalLength; boardLength++) {

			placement[boardLength - 1].canPlace(WHITE);
            if (canPlace(WHITE, determinedStates[boardLength-1])) {
                partialCount[hintNumberIndex][boardLength] = partialCount[hintNumberIndex][boardLength-1];
            }
            
            if (boardLength >= currentHintNumber) {
                bool isSeparated = (boardLength == currentHintNumber) || (canPlace(WHITE, determinedStates[boardLength - currentHintNumber - 1]));

                bool blockFits = true;
                for (int k = 0; k < currentHintNumber; ++k) {
                    if (!canPlace(BLACK, determinedStates[boardLength - 1 - k])) {
                        blockFits = false;
                        break;
                    }
                }
                
                if (isSeparated && blockFits) {
                    int prevJ = boardLength - currentHintNumber - 1;
                    if (prevJ < 0) {
                        partialCount[hintNumberIndex][boardLength] += partialCount[hintNumberIndex-1][0];
                    } else {
                        partialCount[hintNumberIndex][boardLength] += partialCount[hintNumberIndex-1][prevJ];
                    }
                }
            }
        }
    }

    return partialCount[hintsCount][totalLength];
}

/*
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
