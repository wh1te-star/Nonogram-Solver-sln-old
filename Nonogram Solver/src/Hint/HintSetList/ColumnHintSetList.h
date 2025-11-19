#ifndef COLUMNHINTSETLIST_H
#define COLUMNHINTSETLIST_H


#include "Hint/HintSetList/HintSetList.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Board/BoardLength/RowLength.h"

class ColumnHintSetList : public HintSetList {
public:
    explicit ColumnHintSetList(std::vector<HintSet> hintSetList);

public:
	HintSet operator[](ColumnIndex columnIndex) const;

public:
	RowLength getMaxHintSetLength() const;
};


#endif
