#include "Algorithm/FindRightMostPlacementAlgorithm/FindRightMostPlacementAlgorithm.h"


Placement FindRightMostPlacementAlgorithm::run(
	const Line& line,
	const HintSet& hintSet
) {
	return getRightMostPlacement(
		line,
		hintSet
	);
}

Placement FindRightMostPlacementAlgorithm::getRightMostPlacement(
	const Line& line,
	const HintSet& hintSet
) {
	Placement currentPlacement = Placement("");
	return getRightMostPlacementRecursive(
		line,
		hintSet,
		currentPlacement,
		hintSet.size() - 1
	);
}

Placement FindRightMostPlacementAlgorithm::getRightMostPlacementRecursive(
	const Line& line,
	const HintSet& hintSet,
	Placement& currentPlacement,
	int currentHintIndex
) {
	if (currentPlacement.size() > line.size()) {
		return Placement("");
	}
	if (currentHintIndex < 0) {
		Placement foundPlacement = currentPlacement;
		if (currentPlacement.size() < line.size()) {
		for (CellIndex cellIndex : CellIndex::range(line.size() - currentPlacement.size() - 1, 0)) {
				if (!line[cellIndex].canColor(White)) {
					return Placement("");
				}
				foundPlacement = Placement("W") + foundPlacement;
			}
		}
		return foundPlacement;
	}
	
	HintNumber hintNumber = hintSet[currentHintIndex];
	CellIndex currentIndex = CellIndex(line.size() - currentPlacement.size() - hintNumber.getNumber());
	if (line.canPlaceBlock(currentIndex, hintNumber)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = Placement(hintNumber) + currentPlacement;
		if (currentPlacement.size() < line.size()) {
			currentPlacement = Placement("W") + currentPlacement;
		}
		Placement foundPlacement = getRightMostPlacementRecursive(
			line,
			hintSet,
			currentPlacement,
			currentHintIndex - 1
		);
		if (foundPlacement.size() != 0) {
			return foundPlacement;
		}
		currentPlacement = previousPlacement;
	}

	if (currentIndex >= 0 && line[currentIndex].canColor(White)) {
		Placement previousPlacement = currentPlacement;
		currentPlacement = Placement("W") + currentPlacement;
		Placement foundPlacement = getRightMostPlacementRecursive(
			line,
			hintSet,
			currentPlacement,
			currentHintIndex
		);
		if (foundPlacement.size() != 0) {
			return foundPlacement;
		}
		currentPlacement = previousPlacement;
	}

	return Placement("");
}