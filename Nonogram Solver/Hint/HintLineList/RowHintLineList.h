#ifndef ROWHINTLINELIST_H
#define ROWHINTLINELIST_H


#include "Board/BoardLength/ColumnLength.h"
#include "Hint/HintLine/HintLine.h"
#include "Hint/HintLineList/HintLineList.h"
#include "Index/CellIndex/RowIndex.h"

class RowHintLineList : public HintLineList {
public:
    explicit RowHintLineList(std::vector<HintLine> hintLineList);

	ColumnLength getMaxHintLineLength() const;

	HintLine operator[](RowIndex rowIndex) const;
};


#endif
