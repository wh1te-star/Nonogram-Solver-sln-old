#include "pch.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Algorithm/ExhaustivePlacementPatternFindAlgorithm/ExhaustivePlacementPatternFindAlgorithm.h"


void findPlacementPatternExhaustiveTest(
    const std::string& lineStr,
    const std::vector<int>& hintNumbers,
    const std::vector<std::string>& expectedList
) {
    Line line = Line(lineStr);
    HintLine hintLine = HintLine(hintNumbers);
    std::vector<Placement> expected;
    expected.reserve(expectedList.size()); 
    std::transform(
        expectedList.begin(),
        expectedList.end(),
        std::back_inserter(expected),
        [](const std::string& str) {
            return Placement(str);
        }
    );
    
    std::vector<Placement> result = ExhaustivePlacementPatternFindAlgorithm::run(line, hintLine);
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
TEST(Algorithm_FindPlacementPatternExhaustive, ManyHintsCase) {
    const std::string filePath = "..\\..\\Nonogram Solver Test\\Algorithm_FindPlacementPatternExhaustive_ManyHintsCase.txt";
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
