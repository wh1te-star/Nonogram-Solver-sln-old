#ifndef COLUMNHINTLINELIST_H
#define COLUMNHINTLINELIST_H


#include "Hint/HintLineList/HintLineList.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Board/BoardLength/RowLength.h"

class ColumnHintLineList : public HintLineList {
public:
    explicit ColumnHintLineList(std::vector<HintLine> hintLineList);

public:
	HintLine operator[](ColumnIndex columnIndex) const;

public:
	RowLength getMaxHintLineLength() const;
};


#endif
