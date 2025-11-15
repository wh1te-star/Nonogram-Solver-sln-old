#include "pch.h"

#include <vector>
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"


TEST(Algorithm_OverlapDetermination, VerySimpleCase) {
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

    Line expected = Line(std::vector<Cell>{
        Cell(None),
        Cell(None),
        Cell(None),
        Cell(Black),
        Cell(None)
	});

	Line result = OverlapDeterminationAlgorithm::determineByOverlap(line, hintLine);

    EXPECT_EQ(result, expected);
}

TEST(Algorithm_OverlapDetermination, EdgeWhiteCase) {
    Line line = Line(std::vector<Cell>{
        Cell(None),
        Cell(White),
        Cell(None),
        Cell(None),
        Cell(None),
    });

    HintLine hintLine = HintLine(std::vector<HintNumber>{
        HintNumber(2)
    });

    Line expected = Line(std::vector<Cell>{
        Cell(White),
        Cell(White),
        Cell(None),
        Cell(Black),
        Cell(None)
	});

	Line result = OverlapDeterminationAlgorithm::determineByOverlap(line, hintLine);

    EXPECT_EQ(result, expected);
}
