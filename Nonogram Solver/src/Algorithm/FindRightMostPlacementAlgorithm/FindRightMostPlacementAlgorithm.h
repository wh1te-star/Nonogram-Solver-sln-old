#ifndef FINDRIGHTMOSTPLACEMENTALGORITHM_H
#define FINDRIGHTMOSTPLACEMENTALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Board/Line/Column.h"
#include "Hint/HintSet/HintSet.h"
#include "Placement/Placement/ColumnPlacement.h"

class FindRightMostPlacementAlgorithm {
public:
	static Placement run(
		const Line& line,
		const HintSet& HintSet
	);

    static Placement getRightMostPlacement(
        const Line& line,
		const HintSet& HintSet
    );

    static Placement getRightMostPlacementRecursive(
		const Line& line,
		const HintSet& HintSet,
		Placement& currentPlacement,
		int currentHintIndex
	);
};


#endif
