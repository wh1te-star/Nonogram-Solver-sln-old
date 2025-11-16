#include "pch.h"

#include <vector>
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"


TEST(Algorithm_OverlapDetermination, VerySimpleCase) {
    Line line = Line("     ");
    HintLine hintLine = HintLine({ 1, 2 });
    Line expected = Line("   B ");


	Line result = OverlapDeterminationAlgorithm::determineByOverlap(line, hintLine);
    EXPECT_EQ(result, expected);
}


TEST(Algorithm_OverlapDetermination, EdgeWhiteCase) {
    Line line = Line(" W   ");
    HintLine hintLine = HintLine({ 2 });
    Line expected = Line("WW B ");

	Line result = OverlapDeterminationAlgorithm::determineByOverlap(line, hintLine);
    EXPECT_EQ(result, expected);
}
