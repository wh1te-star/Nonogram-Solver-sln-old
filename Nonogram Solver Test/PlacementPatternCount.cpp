#include "pch.h"

#include <vector>
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Board/Line/Line.h"
#include "Hint/HintSet/HintSet.h"
#include "Cell/Cell/Cell.h"


TEST(Algorithm_PlacementPatternCount, VerySimpleCase) {
    Line line = Line("     ");
    HintSet hintSet = HintSet({ 1, 2 });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintSet);
    EXPECT_EQ(result.getCount(), 3);
}

TEST(Algorithm_PlacementPatternCount, DeterministicCase) {
    Line line = Line("    ");
    HintSet hintSet = HintSet({ 1, 2 });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintSet);
    EXPECT_EQ(result.getCount(), 1);
}

TEST(Algorithm_PlacementPatternCount, ImpossibleCase) {
    Line line = Line("   WW");
    HintSet hintSet = HintSet({ 1, 2 });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintSet);
    EXPECT_EQ(result.getCount(), 0);
}
