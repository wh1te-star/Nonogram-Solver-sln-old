#ifndef EXHAUSTIVEPLACEMENTPATTERNFINDALGORITHM_H
#define EXHAUSTIVEPLACEMENTPATTERNFINDALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Placement/Placement/Placement.h"
#include "Hint/HintLine/HintLine.h"

class ExhaustivePlacementPatternFindAlgorithm {
public:
	static std::vector<Placement> findPlacementsExhaustive(
		const Placement& placement,
		const HintLine& hintLine
		// todo: callback argument
	);
};


#endif
