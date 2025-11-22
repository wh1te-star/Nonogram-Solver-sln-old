#ifndef OVERLAPPATTERNCOUNTALGORITHM_H
#define OVERLAPPATTERNCOUNTALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Board/Line/Column.h"
#include "Hint/HintSet/HintSet.h"
#include "Placement/Placement/ColumnPlacement.h"

class OverlapDeterminationAlgorithm {
public:
    static Line run(
        const Line& line,
		const HintSet& HintSet
    );

    static Line determineByOverlap(
        const Line& line,
		const HintSet& HintSet
    );
};


#endif
