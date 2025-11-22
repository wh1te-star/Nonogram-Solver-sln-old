#ifndef FINDLEFTMOSTPLACEMENTALGORITHM_H
#define FINDLEFTMOSTPLACEMENTALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Board/Line/Column.h"
#include "Hint/HintSet/HintSet.h"
#include "Placement/Placement/ColumnPlacement.h"

class FindLeftMostPlacementAlgorithm {
public:
	static Placement run(
		const Line& line,
		const HintSet& HintSet
	);

    static Placement getLeftMostPlacement(
        const Line& line,
		const HintSet& HintSet
    );

    static Placement getLeftMostPlacementRecursive(
		const Line& line,
		const HintSet& HintSet,
		Placement& currentPlacement,
		int currentHintIndex
	);
};


#endif
