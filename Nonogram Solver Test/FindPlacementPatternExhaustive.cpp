#include "pch.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Algorithm/ExhaustivePlacementPatternFindAlgorithm/ExhaustivePlacementPatternFindAlgorithm.h"


const std::string projectName = "Nonogram Solver Test";

void findPlacementPatternExhaustiveTest(
    const std::string& lineStr,
    const std::vector<int>& hintNumbers,
    const std::vector<std::string>& expectedList
) {
    Line line = Line(lineStr);
    HintSet HintSet = HintSet(hintNumbers);
    std::vector<Placement> expected;
	for (std::string str : expectedList) {
		expected.emplace_back(Placement(str));
    }
    
    std::vector<Placement> result = ExhaustivePlacementPatternFindAlgorithm::run(line, HintSet);
    EXPECT_EQ(result, expected);
}
std::vector<std::string> readLinesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            break;
        }
		lines.push_back(line);
    }
    return lines;
}


TEST(Algorithm_FindPlacementPatternExhaustive, VerySimpleCase) {
    findPlacementPatternExhaustiveTest(
        "      ",
        {3},
        {
			"BBBWWW",
			"WBBBWW",
			"WWBBBW",
			"WWWBBB",
        }
	);
}
TEST(Algorithm_FindPlacementPatternExhaustive, ConditionedVerySimpleCase) {
    findPlacementPatternExhaustiveTest(
        " B    ",
        {3},
        {
			"BBBWWW",
			"WBBBWW",
        }
	);
}


TEST(Algorithm_FindPlacementPatternExhaustive, SomeHintsCase) {
    findPlacementPatternExhaustiveTest(
        "      ",
        {1, 3},
        {
			"BWBBBW",
			"BWWBBB",
			"WBWBBB",
        }
	);
}
TEST(Algorithm_FindPlacementPatternExhaustive, ConditionedSomeHintsCase) {
    findPlacementPatternExhaustiveTest(
        " B    ",
        {1, 3},
        {
			"WBWBBB",
        }
	);
}


TEST(Algorithm_FindPlacementPatternExhaustive, ManyHintsCase) {
	const std::string fileName = "Algorithm_FindPlacementPatternExhaustive_ManyHintsCase.txt";
	const std::string filePath = "..\\..\\" + projectName + "\\" + fileName;
    std::vector<std::string> expectedLines;
    try {
        expectedLines = readLinesFromFile(filePath);
    } catch (const std::runtime_error& e) {
        FAIL() << "Test Setup Failed: " << e.what();
        return;
    }
    findPlacementPatternExhaustiveTest(
        "                         ",
        {1, 3, 4, 2, 3},
        expectedLines
    );
}


TEST(Algorithm_FindPlacementPatternExhaustive, ImpossibleCase) {
    findPlacementPatternExhaustiveTest(
        "      ",
        {7},
        {}
	);
}
TEST(Algorithm_FindPlacementPatternExhaustive, ConditionedImpossibleCase) {
    findPlacementPatternExhaustiveTest(
        " W W W",
        {2},
        {}
	);
}
