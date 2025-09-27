#ifndef ROWHINTLINELIST_H
#define ROWHINTLINELIST_H


#include "HintLineList.h"

class RowHintLineList : public HintLineList {
public:
    explicit RowHintLineList(std::vector<HintLine> hintLineList);
};


#endif
