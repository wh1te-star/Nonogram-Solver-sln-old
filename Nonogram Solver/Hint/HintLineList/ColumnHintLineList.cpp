#include "Index/CellIndex/ColumnIndex.h"
#include "Hint/HintLineList/ColumnHintLineList.h"
#include "Hint/HintLine/HintLine.h"
#include "Board/BoardLength/RowLength.h"

ColumnHintLineList::ColumnHintLineList(std::vector<HintLine> hintLineList) :
	HintLineList(hintLineList) {}

RowLength ColumnHintLineList::getMaxHintLineLength() const {
	return RowLength(getMaxItemCount());
}

HintLine ColumnHintLineList::operator[](ColumnIndex columnIndex) const {
	return hintLineList[columnIndex.getIndex()];
}
