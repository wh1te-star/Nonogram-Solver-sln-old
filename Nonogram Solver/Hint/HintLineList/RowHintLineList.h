#ifndef ROWHINTLINELIST_H
#define ROWHINTLINELIST_H


#include "Board/BoardLength/ColumnLength.h"
#include "Hint/HintLine/HintLine.h"
#include "Hint/HintLineList/HintLineList.h"
#include "Index/CellIndex/RowIndex.h"

class RowHintLineList : public HintLineList {
public:
    explicit RowHintLineList(std::vector<HintLine> hintLineList);

public:
	HintLine operator[](RowIndex rowIndex) const;

public:
	ColumnLength getMaxHintLineLength() const;
};


#endif
