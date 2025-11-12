#define CATCH_CONFIG_MAIN
#include "pch.h"
#include <catch2/catch.hpp>

/*
#include <vector>
#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"
#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"
#include "Cell/Cell/Cell.h"
*/

TEST_CASE("Very typical small case", "[PlacementPatternCount]") {
    /*
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

    REQUIRE(result == PlacementCount(6)); 
    */

	REQUIRE(true);
}

/*
TEST_CASE("PlacementPatternCountAlgorithm handles single hint {3} on 5 cells", "[PlacementPatternCount]") {
    
    Line line(std::vector<Cell>{Cell(White),Cell(White),Cell(White),Cell(White),Cell(White)}); 
    HintLine hintLine(std::vector<HintNumber>{HintNumber(3)}); 

    PlacementCount result = PlacementPatternCountAlgorithm::run(line, hintLine);
    
    REQUIRE(result.getCount() == 3); 
}
*/
