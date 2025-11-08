#include "pch.h"
#include <catch2/catch.hpp>

#include <vector>
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"
#include "Cell/Cell/Cell.h"

TEST_CASE("PlacementPatternCountAlgorithm calculates patterns for 5 cells with {1, 2} hints", "[PlacementPatternCount]") {
    std::vector<Cell> cells = {
        Cell(White), 
        Cell(White), 
        Cell(White), 
        Cell(White), 
        Cell(White) 
    };
    Line line(cells); 

    std::vector<HintNumber> hintNumbers = { 
        HintNumber(1), 
        HintNumber(2) 
    };
    HintLine hintLine(hintNumbers);

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);

    REQUIRE(result.getCount() == 6); 
}

/*
TEST_CASE("PlacementPatternCountAlgorithm handles single hint {3} on 5 cells", "[PlacementPatternCount]") {
    
    Line line(std::vector<Cell>{Cell(White),Cell(White),Cell(White),Cell(White),Cell(White)}); 
    HintLine hintLine(std::vector<HintNumber>{HintNumber(3)}); 

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);
    
    REQUIRE(result.getCount() == 3); 
}
*/
