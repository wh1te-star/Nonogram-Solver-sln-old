#include "pch.h"

#include <vector>
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"
#include "Cell/Cell/Cell.h"

TEST(Algorithm_PlacementCount, VerySimpleCase) {
    Line line = Line(std::vector<Cell>{
        Cell(None),
        Cell(None),
        Cell(None),
        Cell(None),
        Cell(None),
    });

    HintLine hintLine = HintLine(std::vector<HintNumber>{
        HintNumber(1),
        HintNumber(2)
    });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);

    EXPECT_EQ(result.getCount(), 3);
}

TEST(Algorithm_PlacementCount, ImpossibleCase) {
    Line line = Line(std::vector<Cell>{
        Cell(None),
        Cell(None),
        Cell(None),
        Cell(White),
        Cell(White),
    });

    HintLine hintLine = HintLine(std::vector<HintNumber>{
        HintNumber(1),
        HintNumber(2)
    });

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);

    EXPECT_EQ(result.getCount(), 0);
}
