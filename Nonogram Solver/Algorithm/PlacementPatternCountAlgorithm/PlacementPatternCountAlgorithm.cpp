#include "Algorithm/PlacementPatternCountAlgorithm/PlacementPatternCountAlgorithm.h"

#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"


PlacementCount PlacementPatternCountAlgorithm::run(
	const Line& line,
	const HintLine& hintLine
) {
	int hintsCount = hintLine.size();
	int totalLength = line.size();

	std::vector<std::vector<PlacementCount>> partialCount(
		hintsCount + 1,
		std::vector<PlacementCount>(
			totalLength + 1,
			PlacementCount(0)
		)
	);

	partialCount[0][0] = PlacementCount(1);
	for (int cellIndexInt = 1; cellIndexInt <= totalLength; cellIndexInt++) {
        CellIndex cellIndex = CellIndex(cellIndexInt - 1);
		Cell cell = line[cellIndex];
		if (cell.canColor(White)) {
			partialCount[0][cellIndexInt] = PlacementCount(1);
		}
		else {
			break;
		}
	}

	for (int hintNumberIndexInt = 1; hintNumberIndexInt <= hintsCount; hintNumberIndexInt++) {
		HintNumber hintNumber = hintLine[hintNumberIndexInt];

		for (int cellIndexInt = 1; cellIndexInt <= totalLength; cellIndexInt++) {
            CellIndex cellIndex = CellIndex(cellIndexInt);

			if (line[cellIndex - 1].canColor(White)) {
				partialCount[hintNumberIndexInt][cellIndexInt] = partialCount[hintNumberIndexInt][cellIndexInt - 1];
			}

			if (cellIndex >= BoardLength(hintNumber.getNumber())) {
                CellIndex prevCellIndex = cellIndex - hintNumber - 1;
                CellIndex blockStart = cellIndex - hintNumber;

                bool isSeparated = (prevCellIndex < 0) || (line[prevCellIndex].canColor(White));

				bool blockFits = true;
				for (int blackCellIndexInt = blockStart.getIndex(); blackCellIndexInt < hintNumber.getNumber(); blackCellIndexInt++) {
					CellIndex blackCellIndex = CellIndex(blackCellIndexInt);

					if (!line[blackCellIndex].canColor(Black)) {
						blockFits = false;
						break;
					}
				}

				if (isSeparated && blockFits) {
					if (prevCellIndex < 0) {
						partialCount[hintNumberIndexInt][cellIndexInt] += partialCount[hintNumberIndexInt - 1][0];
					}
					else {
						partialCount[hintNumberIndexInt][cellIndexInt] += partialCount[hintNumberIndexInt - 1][prevCellIndex.getIndex()];
					}
				}
			}
		}
	}

	return partialCount[hintsCount][totalLength];
}

