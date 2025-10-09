#ifndef ROWHINTLINELIST_H
#define ROWHINTLINELIST_H


#include "Hint/HintLine/HintLine.h"
#include "Hint/HintLineList/HintLineList.h"

class RowHintLineList : public HintLineList {
public:
    explicit RowHintLineList(std::vector<HintLine> hintLineList);

	ColumnLength getMaxHintLineLength() const;
};


#endif
