#ifndef TEstDATAREPOSITORY_H
#define TEstDATAREPOSITORY_H

#include <string>
#include <vector>
#include "Hint/HintNumber/HintNumber.h"
#include "Hint/HintSetList/RowHintSetList.h"
#include "Hint/HintSetList/ColumnHintSetList.h"

class TestDataRepository {
public:
    enum TestDataType { EASY, LAMBDA, LARGE };

private:
    TestDataRepository() = delete;

    static std::string GetColumnHintString(TestDataType type);
    static std::string GetRowHintString(TestDataType type);
    static std::string GetEasyRowHintString();
    static std::string GetEasyColumnHintString();
    static std::string GetLambdaRowHintString();
    static std::string GetLambdaColumnHintString();
    static std::string GetLargeRowHintString();
    static std::string GetLargeColumnHintString();
    
    static std::vector<std::vector<HintNumber>> parseHints(const std::string& hintString);

public:
    static RowHintSetList getRowHintSetList(TestDataType type);
    static ColumnHintSetList getColumnHintSetList(TestDataType type);
};

#endif
