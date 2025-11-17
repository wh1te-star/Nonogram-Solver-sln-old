#include "Algorithm/ExhaustivePlacementPatternFindAlgorithm/ExhaustivePlacementPatternFindAlgorithm.h"

#include "Board/Line/Line.h"


std::vector<Placement> ExhaustivePlacementPatternFindAlgorithm::run(
	const Line& line,
	const HintLine& hintLine
) {
	return findPlacementsExhaustive(
		line,
		hintLine
	);
}

std::vector<Placement> ExhaustivePlacementPatternFindAlgorithm::findPlacementsExhaustive(
	const Line& line,
	const HintLine& hintLine
) {
    std::vector<Placement> solutions;
	Placement currentPlacement = Placement("");
	findPlacementsExhaustiveRecursive(
		line,
		hintLine,
		solutions,
		currentPlacement,
		0
	);
    return solutions;
}

void ExhaustivePlacementPatternFindAlgorithm::findPlacementsExhaustiveRecursive(
	const Line& line,
	const HintLine& hintLine,
	std::vector<Placement>& solutions,
	Placement& currentPlacement,
	int currentHintIndex
) {
	if (currentPlacement.size() > line.size()) {
		return;
	}
	if (currentHintIndex >= hintLine.size()) {
		Placement foundPlacement = currentPlacement;
		for (CellIndex i = CellIndex(currentPlacement.size()); i < line.size(); i = i + 1) {
			if (!line[i].canColor(White)) {
				return;
			}
			foundPlacement = foundPlacement + Placement("W");
		}
		solutions.push_back(foundPlacement);
		return;
	}
	
	HintNumber hintNumber = hintLine[currentHintIndex];
	CellIndex currentIndex = CellIndex(currentPlacement.size());
	if (line.canPlaceBlock(currentIndex, hintNumber)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = currentPlacement + Placement(hintNumber);
		if (currentPlacement.size() < line.size()) {
			currentPlacement = currentPlacement + Placement("W");
		}
		findPlacementsExhaustiveRecursive(
			line,
			hintLine,
			solutions,
			currentPlacement,
			currentHintIndex + 1
		);
		currentPlacement = previousPlacement;
	}

	if (currentIndex < line.size() && line[currentIndex].canColor(White)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = currentPlacement + Placement("W");
		findPlacementsExhaustiveRecursive(
			line,
			hintLine,
			solutions,
			currentPlacement,
			currentHintIndex
		);
		currentPlacement = previousPlacement;
	}
}
