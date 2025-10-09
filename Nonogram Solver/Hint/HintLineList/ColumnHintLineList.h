#ifndef COLUMNHINTLINELIST_H
#define COLUMNHINTLINELIST_H


#include "Hint/HintLineList/HintLineList.h"

class ColumnHintLineList : public HintLineList {
public:
    explicit ColumnHintLineList(std::vector<HintLine> hintLineList);

	RowLength getMaxHintLineLength() const;
};


#endif
