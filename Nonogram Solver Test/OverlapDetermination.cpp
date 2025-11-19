#include "pch.h"

#include <vector>
#include "Algorithm/OverlapDeterminationAlgorithm/OverlapDeterminationAlgorithm.h"


void leftMostPlacementTest(
    const std::string& lineStr,
    const std::vector<int>& hintNumbers,
    const std::string& expectedStr
) {
    Line line = Line(lineStr);
    HintSet HintSet = HintSet(hintNumbers);
    Placement expected = Placement(expectedStr);
    
    Placement result = OverlapDeterminationAlgorithm::getLeftmostPlacement(line, HintSet);
    EXPECT_EQ(result, expected);
}
TEST(Algorithm_LeftMostPlacement, VerySimpleCase) {
	leftMostPlacementTest("     ", { 1, 2 }, "BWBBW");
}
TEST(Algorithm_LeftMostPlacement, LittleShiftedCase) {
	leftMostPlacementTest("W    ", { 1, 2 }, "WBWBB");
}
TEST(Algorithm_LeftMostPlacement, MiddleWhiteCase) {
	leftMostPlacementTest("  W  ", { 1, 2 }, "BWWBB");
}
TEST(Algorithm_LeftMostPlacement, SomeHintsCase) {
	leftMostPlacementTest("          ", { 1, 2, 3 }, "BWBBWBBBWW");
}
TEST(Algorithm_LeftMostPlacement, SomeHintsMiddleWhiteCase) {
	leftMostPlacementTest("W  W      ", { 1, 2, 3 }, "WBWWBBWBBB");
}
TEST(Algorithm_LeftMostPlacement, ImpossibleCase) {
	leftMostPlacementTest("WW   ", { 1, 2 }, "");
}


void rightMostPlacementTest(
    const std::string& lineStr,
    const std::vector<int>& hintNumbers,
    const std::string& expectedStr
) {
    Line line = Line(lineStr);
    HintSet HintSet = HintSet(hintNumbers);
    Placement expected = Placement(expectedStr);
    
    Placement result = OverlapDeterminationAlgorithm::getRightmostPositions(line, HintSet);
    EXPECT_EQ(result, expected);
}
TEST(Algorithm_RightMostPlacement, VerySimpleCase) {
	rightMostPlacementTest("     ", { 1, 2 }, "WBWBB");
}
TEST(Algorithm_RightMostPlacement, LittleShiftedCase) {
	rightMostPlacementTest("    W", { 1, 2 }, "BWBBW");
}
TEST(Algorithm_RightMostPlacement, MiddleWhiteCase) {
	rightMostPlacementTest(" W   ", { 1, 2 }, "BWWBB");
}
TEST(Algorithm_RightMostPlacement, SomeHintsCase) {
	rightMostPlacementTest("          ", { 1, 2, 3 }, "WWBWBBWBBB");
}
TEST(Algorithm_RightMostPlacement, SomeHintsMiddleWhiteCase) {
	rightMostPlacementTest("    W    W", { 1, 2, 3 }, "BWBBWWBBBW");
}
TEST(Algorithm_RightMostPlacement, ImpossibleCase) {
	rightMostPlacementTest("   WW", { 1, 2 }, "");
}



TEST(Algorithm_OverlapDetermination, VerySimpleCase) {
    Line line = Line("     ");
    HintSet HintSet = HintSet({ 1, 2 });
    Line expected = Line("   B ");

	Line result = OverlapDeterminationAlgorithm::determineByOverlap(line, HintSet);
    EXPECT_EQ(result, expected);
}


TEST(Algorithm_OverlapDetermination, EdgeWhiteCase) {
    Line line = Line(" W   ");
    HintSet HintSet = HintSet({ 2 });
    Line expected = Line("WW B ");

	Line result = OverlapDeterminationAlgorithm::determineByOverlap(line, HintSet);
    EXPECT_EQ(result, expected);
}
