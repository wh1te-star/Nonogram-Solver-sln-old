#include "Index/CellIndex/ColumnIndex.h"
#include "Hint/HintSetList/ColumnHintSetList.h"
#include "Hint/HintSet/HintSet.h"
#include "Board/BoardLength/RowLength.h"

ColumnHintSetList::ColumnHintSetList(std::vector<HintSet> hintSetList) :
	HintSetList(hintSetList) {}

HintSet ColumnHintSetList::operator[](ColumnIndex columnIndex) const {
	return hintSetList[columnIndex.getIndex()];
}

RowLength ColumnHintSetList::getMaxHintSetLength() const {
	return RowLength(getMaxItemCount());
}

