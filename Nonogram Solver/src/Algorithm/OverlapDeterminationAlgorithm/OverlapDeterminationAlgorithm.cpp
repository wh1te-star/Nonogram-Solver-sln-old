#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"

#include "Board/Line/Line.h"


Line OverlapDeterminationAlgorithm::determineByOverlap(
	const Line& line,
	const HintLine& hintLine
) {
	Placement leftmostPlacement = getLeftmostPlacement(line, hintLine);
	Placement rightmostPlacement = getRightmostPositions(line, hintLine);
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
    for (int i = (rightmostHintIndex.back() + hintLine.getNumbers().back()).getIndex(); i < line.size(); i++) {
		CellIndex cellIndex = CellIndex(i);
        determined[cellIndex] = Cell(White);
	}
    for(int hintIndex = 0; hintIndex < hintLine.size(); hintIndex++) {
        CellIndex leftStart = leftmostHintIndex[hintIndex];
        CellIndex leftEnd = leftStart + hintLine[hintIndex] - 1;
        CellIndex rightStart = rightmostHintIndex[hintIndex];
        CellIndex rightEnd = rightStart + hintLine[hintIndex] - 1;
        for(CellIndex cellIndex = leftStart; cellIndex <= leftEnd; cellIndex++) {
            if (rightStart <= cellIndex && cellIndex <= rightEnd) {
				determined[cellIndex] = Cell(Black);
            }
        }
	}

    return determined;
}

Placement OverlapDeterminationAlgorithm::getLeftmostPlacement(
	const Line& line,
	const HintLine& hintLine
) {
    Placement placement = Placement(std::vector<Cell>());
	CellIndex currentIndex = CellIndex(0);
    for (int hintIndex = 0; hintIndex < hintLine.size(); hintIndex++) {
        HintNumber hintNumber = hintLine[hintIndex];
        while (true) {
            if (currentIndex >= line.size()) {
				return Placement("");
            }
            if (line.canPlaceBlock(currentIndex, hintNumber)) {
				placement = placement + Placement(hintNumber);
                currentIndex = currentIndex + hintNumber;
                break;
            }
			placement = placement + Placement({ Cell(White) });
            currentIndex++;
        }

        if(hintIndex < hintLine.size() - 1) {
            placement += Placement({ Cell(White) });
            currentIndex = currentIndex + 1;
		}
    }
    for (int i = placement.size(); i < line.size(); i++) {
        placement += Placement({ Cell(White) });
    }
    return placement;
}

Placement OverlapDeterminationAlgorithm::getRightmostPositions(
	const Line& line,
	const HintLine& hintLine
) {
    Placement placement = Placement(std::vector<Cell>());
	CellIndex currentIndex = CellIndex(line.size());

    for (int hintIndex = (int)hintLine.size()-1; hintIndex >= 0; hintIndex--){
        HintNumber hintNumber = hintLine[hintIndex];
        currentIndex = currentIndex - hintNumber;
        while (true) {
            if (currentIndex < 0) {
				return Placement("");
            }
            if (line.canPlaceBlock(currentIndex, hintNumber)) {
				placement = Placement(hintNumber) + placement;
                break;
            }
            placement = Placement({ Cell(White) }) + placement;
            currentIndex--;
        }

        if(hintIndex > 0) {
			placement = Placement({ Cell(White) }) + placement;
            currentIndex = currentIndex - 1;
		}
    }
    for (int i = placement.size(); i < line.size(); i++) {
		placement = Placement({ Cell(White) }) + placement;
    }
    return placement;
}
