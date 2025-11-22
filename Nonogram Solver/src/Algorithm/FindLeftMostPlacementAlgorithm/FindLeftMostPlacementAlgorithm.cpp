#include "Algorithm/FindLeftMostPlacementAlgorithm/FindLeftMostPlacementAlgorithm.h"


Placement FindLeftMostPlacementAlgorithm::run(
	const Line& line,
	const HintSet& HintSet
) {
	return getLeftMostPlacement(
		line,
		HintSet
	);
}

Placement FindLeftMostPlacementAlgorithm::getLeftMostPlacement(
	const Line& line,
	const HintSet& HintSet
) {
	Placement currentPlacement = Placement("");
	return getLeftMostPlacementRecursive(
		line,
		HintSet,
		currentPlacement,
		0
	);
}

Placement FindLeftMostPlacementAlgorithm::getLeftMostPlacementRecursive(
	const Line& line,
	const HintSet& HintSet,
	Placement& currentPlacement,
	int currentHintIndex
) {
	if (currentPlacement.size() > line.size()) {
		return Placement("");
	}
	if (currentHintIndex >= HintSet.size()) {
		Placement foundPlacement = currentPlacement;
		for (CellIndex cellIndex : CellIndex::range(currentPlacement.size(), line.size() - 1)) {
			if (!line[cellIndex].canColor(White)) {
				return Placement("");
			}
			foundPlacement = foundPlacement + Placement("W");
		}
		return foundPlacement;
	}
	
	HintNumber hintNumber = HintSet[currentHintIndex];
	CellIndex currentIndex = CellIndex(currentPlacement.size());
	if (line.canPlaceBlock(currentIndex, hintNumber)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = currentPlacement + Placement(hintNumber);
		if (currentPlacement.size() < line.size()) {
			currentPlacement = currentPlacement + Placement("W");
		}
		Placement foundPlacement = getLeftMostPlacementRecursive(
			line,
			HintSet,
			currentPlacement,
			currentHintIndex + 1
		);
		if (foundPlacement.size() != 0) {
			return foundPlacement;
		}
		currentPlacement = previousPlacement;
	}

	if (currentIndex < line.size() && line[currentIndex].canColor(White)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = currentPlacement + Placement("W");
		Placement foundPlacement = getLeftMostPlacementRecursive(
			line,
			HintSet,
			currentPlacement,
			currentHintIndex + 1
		);
		if (foundPlacement.size() != 0) {
			return foundPlacement;
		}
		currentPlacement = previousPlacement;
	}

	return Placement("");
}