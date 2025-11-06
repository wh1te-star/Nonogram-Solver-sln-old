#include "TestData/Repository/TestDataRepository.h"
#include "Hint/HintNumber/HintNumber.h"
#include <sstream>
#include <cassert>


std::vector<std::vector<HintNumber>> TestDataRepository::parseHints(const std::string& hintString) {
    std::vector<std::vector<HintNumber>> hintMatrix;
    std::stringstream ss(hintString);
    std::string line;

    const char* whitespace = " \t\n\r\f\v";

    while (std::getline(ss, line)) {
        line.erase(0, line.find_first_not_of(whitespace));
        line.erase(line.find_last_not_of(whitespace) + 1);

        if (line.empty()) {
            continue;
        }

        std::vector<HintNumber> row;
        std::stringstream line_ss(line + ',');
        std::string cell;

        while (std::getline(line_ss, cell, ',')) {
            cell.erase(0, cell.find_first_not_of(whitespace));
            cell.erase(cell.find_last_not_of(whitespace) + 1);

            if (cell.empty()) {
                row.emplace_back(0); 
            } else {
                row.emplace_back(std::stoi(cell));
            }
        }
        hintMatrix.push_back(row);
    }
    return hintMatrix;
}

RowHintLineList TestDataRepository::getRowHintLineList(TestDataType type) {
	std::string rowHintNumbersString = GetRowHintString(type);
    std::vector<std::vector<HintNumber>> tempRowHintNumbers = parseHints(rowHintNumbersString);

    std::vector<HintLine> hintLineListVector;
    for(int k = 0; k < tempRowHintNumbers.size(); k++) {
		std::vector<HintNumber> hintLineVector;
        for(int i = 0; i < tempRowHintNumbers[k].size(); i++) {
			if (tempRowHintNumbers[k][i] == HintNumber(0)) continue;
			hintLineVector.push_back(tempRowHintNumbers[k][i]);
		}
		hintLineListVector.emplace_back(hintLineVector);
	}

	RowHintLineList rowHintLineList(hintLineListVector);
	return rowHintLineList;
}

ColumnHintLineList TestDataRepository::getColumnHintLineList(TestDataType type) {
	std::string columnHintNumbersString = GetColumnHintString(type);
	std::vector<std::vector<HintNumber>> tempColumnHintNumbers = parseHints(columnHintNumbersString);

    std::vector<HintLine> hintLineListVector;
    for(int k = 0; k < tempColumnHintNumbers[0].size(); k++) {
		std::vector<HintNumber> hintLineVector;
        for(int i = 0; i < tempColumnHintNumbers.size(); i++) {
			if (tempColumnHintNumbers[i][k] == HintNumber(0)) continue;
			hintLineVector.push_back(tempColumnHintNumbers[i][k]);
		}
		hintLineListVector.emplace_back(hintLineVector);
	}

	ColumnHintLineList columnHintLineList(hintLineListVector);
	return columnHintLineList;
}

std::string TestDataRepository::GetRowHintString(TestDataType type) {
    switch (type) {
    case EASY:
        return GetEasyRowHintString();
        break;
    case LAMBDA:
        return GetLambdaRowHintString();
        break;
    case LARGE:
        return GetLargeRowHintString();
        break;
    default:
        assert(false);
        break;
    }
    return "";
}

std::string TestDataRepository::GetColumnHintString(TestDataType type) {
    switch (type) {
    case EASY:
        return GetEasyColumnHintString();
        break;
    case LAMBDA:
        return GetLambdaColumnHintString();
        break;
    case LARGE:
        return GetLargeColumnHintString();
        break;
    default:
        assert(false);
        break;
    }
    return "";
}

