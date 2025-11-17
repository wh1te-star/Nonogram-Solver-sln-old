#ifndef EXHAUSTIVEPLACEMENTPATTERNFINDALGORITHM_H
#define EXHAUSTIVEPLACEMENTPATTERNFINDALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Board/Line/Line.h"
#include "Placement/Placement/Placement.h"
#include "Hint/HintLine/HintLine.h"

class ExhaustivePlacementPatternFindAlgorithm {
public:
	static std::vector<Placement> run(
		const Line& line,
		const HintLine& hintLine
	);

	static std::vector<Placement> findPlacementsExhaustive(
		const Line& line,
		const HintLine& hintLine
	);

	static void findPlacementsExhaustiveRecursive(
		const Line& line,
		const HintLine& hintLine,
		std::vector<Placement>& solutions,
		Placement& currentPlacement,
		int currentHintIndex
	);
};


#endif
