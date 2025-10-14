#include "Hint/HintLineList/RowHintLineList.h"

#include "Hint/HintLineList/HintLineList.h"
#include "Board/BoardLength/ColumnLength.h"

RowHintLineList::RowHintLineList(std::vector<HintLine> hintLineList) :
	HintLineList(hintLineList) {}

HintLine RowHintLineList::operator[](RowIndex rowIndex) const {
	return hintLineList[rowIndex.getIndex()];
}

ColumnLength RowHintLineList::getMaxHintLineLength() const {
	return ColumnLength(getMaxItemCount());
}

