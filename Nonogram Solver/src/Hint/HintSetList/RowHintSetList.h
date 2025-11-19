#ifndef ROWHINTSETLIST_H
#define ROWHINTSETLIST_H


#include "Board/BoardLength/ColumnLength.h"
#include "Hint/HintSet/HintSet.h"
#include "Hint/HintSetList/HintSetList.h"
#include "Index/CellIndex/RowIndex.h"

class RowHintSetList : public HintSetList {
public:
    explicit RowHintSetList(std::vector<HintSet> hintSetList);

public:
	HintSet operator[](RowIndex rowIndex) const;

public:
	ColumnLength getMaxHintSetLength() const;
};


#endif
