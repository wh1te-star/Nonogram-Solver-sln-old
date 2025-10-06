#ifndef ROWPLACEMENT_H
#define ROWPLACEMENT_H

#include <string>
#include <vector>
#include "Hint/HintNumber/HintNumber.h"
#include "Hint/HintLineList/RowHintLineList.h"
#include "Hint/HintLineList/ColumnHintLineList.h"

class TestDataRepository {
public:
    enum TestDataType { EASY, LAMBDA, LARGE };

private:
    TestDataRepository() = delete;

    static std::string GetRowString(TestDataType type);
    static std::string GetColumnString(TestDataType type);
    static std::string GetEasyRowString();
    static std::string GetEasyColumnString();
    static std::string GetLambdaRowString();
    static std::string GetLambdaColumnString();
    static std::string GetLargeRowString();
    static std::string GetLargeColumnString();
    
    static std::vector<std::vector<HintNumber>> parseHints(const std::string& hintString);

public:
    static RowHintLineList getRowHintLineList(TestDataType type);
    static ColumnHintLineList getColumnHintLineList(TestDataType type);
};

#endif
