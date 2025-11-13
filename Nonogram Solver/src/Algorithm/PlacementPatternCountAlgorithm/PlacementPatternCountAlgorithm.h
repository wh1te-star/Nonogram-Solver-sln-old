#ifndef PLACEMENTPATTERNCOUNTALGORITHM_H
#define PLACEMENTPATTERNCOUNTALGORITHM_H


#include "Placement/PlacementCount/PlacementCount.h"
#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"

class PlacementPatternCountAlgorithm {
public:
	static PlacementCount run(
		const Line& line,
		const HintLine& hintLine
	);

private:
	static PlacementCount CountPlacement(
		const Line& line,
		const HintLine& hintLine
	);

	static bool isSeparated(
		const Line& line,
		const CellIndex& prevCellIndex
	);

	static bool isBlockFits(
		const Line& line,
		const CellIndex& blockStart,
		const HintNumber& hintNumber
	);
};


#endif
