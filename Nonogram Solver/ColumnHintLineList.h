#ifndef COLUMNHINTLINELIST_H
#define COLUMNHINTLINELIST_H


#include "HintLineList.h"

class ColumnHintLineList : public HintLineList {
public:
    explicit ColumnHintLineList(std::vector<HintLine> hintLineList);
};


#endif
