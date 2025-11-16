#include "pch.h"

#include <vector>
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"
#include "Cell/Cell/Cell.h"


TEST(Algorithm_PlacementPatternCount, VerySimpleCase) {
    Line line = Line("     ");
    HintLine hintLine = HintLine({ 1, 2 });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);
    EXPECT_EQ(result.getCount(), 3);
}

TEST(Algorithm_PlacementPatternCount, DeterministicCase) {
    Line line = Line("    ");
    HintLine hintLine = HintLine({ 1, 2 });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);
    EXPECT_EQ(result.getCount(), 1);
}

TEST(Algorithm_PlacementPatternCount, ImpossibleCase) {
    Line line = Line("   WW");
    HintLine hintLine = HintLine({ 1, 2 });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);
    EXPECT_EQ(result.getCount(), 0);
}
