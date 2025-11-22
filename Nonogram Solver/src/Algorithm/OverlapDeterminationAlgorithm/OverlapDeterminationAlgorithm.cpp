#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"

#include "Algorithm/FindLeftMostPlacementAlgorithm/FindLeftMostPlacementAlgorithm.h"
#include "Algorithm/FindRightMostPlacementAlgorithm/FindRightMostPlacementAlgorithm.h"
#include "Board/Line/Line.h"


Line OverlapDeterminationAlgorithm::run(
    const Line& line,
    const HintSet& HintSet
) {
    return determineByOverlap(
        line,
        HintSet
    );
}

Line OverlapDeterminationAlgorithm::determineByOverlap(
	const Line& line,
	const HintSet& HintSet
) {
	Placement leftmostPlacement = FindLeftMostPlacementAlgorithm::run(line, HintSet);
	Placement rightmostPlacement = FindRightMostPlacementAlgorithm::run(line, HintSet);
    if (leftmostPlacement.size() == 0 || rightmostPlacement.size() == 0) {
        return line;
    }

	std::vector<CellIndex> leftmostHintIndex = leftmostPlacement.getHintIndex();
	std::vector<CellIndex> rightmostHintIndex = rightmostPlacement.getHintIndex();

	Line determined(std::vector<Cell>(line.size(), Cell(CellColor::None)));
    for(int i = 0; i < leftmostHintIndex.front().getIndex(); i++) {
		CellIndex cellIndex = CellIndex(i);
        determined[cellIndex] = Cell(White);
	}
    for (int i = (rightmostHintIndex.back() + HintSet.getNumbers().back()).getIndex(); i < line.size(); i++) {
		CellIndex cellIndex = CellIndex(i);
        determined[cellIndex] = Cell(White);
	}
    for(int hintIndex = 0; hintIndex < HintSet.size(); hintIndex++) {
        CellIndex leftStart = leftmostHintIndex[hintIndex];
        CellIndex leftEnd = leftStart + HintSet[hintIndex] - 1;
        CellIndex rightStart = rightmostHintIndex[hintIndex];
        CellIndex rightEnd = rightStart + HintSet[hintIndex] - 1;
        for(CellIndex cellIndex = leftStart; cellIndex <= leftEnd; cellIndex++) {
            if (rightStart <= cellIndex && cellIndex <= rightEnd) {
				determined[cellIndex] = Cell(Black);
            }
        }
	}

    return determined;
}
