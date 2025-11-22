#include "Algorithm/FindRightMostPlacementAlgorithm/FindRightMostPlacementAlgorithm.h"


Placement FindRightMostPlacementAlgorithm::run(
	const Line& line,
	const HintSet& HintSet
) {
	return getRightMostPlacement(
		line,
		HintSet
	);
}

Placement FindRightMostPlacementAlgorithm::getRightMostPlacement(
	const Line& line,
	const HintSet& HintSet
) {
	Placement currentPlacement = Placement("");
	return getRightMostPlacementRecursive(
		line,
		HintSet,
		currentPlacement,
		0
	);
}

Placement FindRightMostPlacementAlgorithm::getRightMostPlacementRecursive(
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
		for (CellIndex cellIndex : CellIndex::range(line.size() - currentPlacement.size() - 1, 0)) {
			if (!line[cellIndex].canColor(White)) {
				return Placement("");
			}
			foundPlacement = Placement("W") + foundPlacement;
		}
		return foundPlacement;
	}
	
	HintNumber hintNumber = HintSet[currentHintIndex];
	CellIndex currentIndex = CellIndex(currentPlacement.size());
	if (line.canPlaceBlock(currentIndex, hintNumber)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = Placement(hintNumber) + currentPlacement;
		if (currentPlacement.size() < line.size()) {
			currentPlacement = Placement("W") + currentPlacement;
		}
		Placement foundPlacement = getRightMostPlacementRecursive(
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
		currentPlacement = Placement("W") + currentPlacement;
		Placement foundPlacement = getRightMostPlacementRecursive(
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