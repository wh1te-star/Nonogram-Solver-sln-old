#ifndef ROWPLACEMENT_H
#define ROWPLACEMENT_H


#include <string>
#include <vector>
#include "Hint/HintNumber/HintNumber.h"
#include "Hint/HintLineList/RowHintLineList.h"
#include "Hint/HintLineList/ColumnHintLineList.h"

class TestDataRepository {
public:
    std::string GetEasyRowString();
    std::string GetEasyColumnString();
    std::string GetLambdaRowString();
    std::string GetLambdaColumnString();
    std::string GetLargeRowString();
    std::string GetLargeColumnString();

	std::vector<std::vector<HintNumber>> parseHints(const std::string& hintString);
	RowHintLineList getRowHintLineList();
	ColumnHintLineList getColumnHintLineList();
};


#endif
