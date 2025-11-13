#ifndef OVERLAPPATTERNCOUNTALGORITHM_H
#define OVERLAPPATTERNCOUNTALGORITHM_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Board/Line/Column.h"
#include "Hint/HintLine/HintLine.h"
#include "Placement/Placement/ColumnPlacement.h"

class OverlapDeterminationAlgorithm {
public:
    static Line determineByOverlap(
        const Line& line,
		const HintLine& hintLine
    );

private:
    static Placement getLeftmostPlacement(
        const Line& line,
		const HintLine& hintLine
    );

	static Placement getRightmostPositions(
        const Line& line,
		const HintLine& hintLine
	);
};


#endif
