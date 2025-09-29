#ifndef ROWPLACEMENT_H
#define ROWPLACEMENT_H


#include <string>

class TestDataRepository {
public:
    static std::string GetEasyRowString();
    static std::string GetEasyColumnString();
    static std::string GetLambdaRowString();
    static std::string GetLambdaColumnString();
    static std::string GetLargeRowString();
    static std::string GetLargeColumnString();
};


#endif
