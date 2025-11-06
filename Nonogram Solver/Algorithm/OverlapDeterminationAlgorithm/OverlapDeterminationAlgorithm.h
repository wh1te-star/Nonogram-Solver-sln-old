#ifndef OVERLAPPATTERNCOUNTALGORITHM_H
#define OVERLAPPATTERNCOUNTALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"

class PlacementPatternCountAlgorithm {
public:
    static std::vector<Cell> determineByOverlap(
        int totalLength,
        const std::vector<int>& hintNumbers,
        const std::vector<Cell>& determinedStates
    );

private:
    static std::vector<int> getLeftmostPlacement(
        const std::vector<Cell>& determinedCells,
        const std::vector<int>& hints
    );

	static std::vector<int> getRightmostPositions(
		const std::vector<Cell>& determinedCells,
		const std::vector<int>& hints
	);
};


#endif
