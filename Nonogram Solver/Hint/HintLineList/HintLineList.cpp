#include "Hint/HintLineList/HintLineList.h"
#include "Hint/HintLine/HintLine.h"


HintLineList::HintLineList(std::vector<HintLine> hintLineList) :
	hintLineList(hintLineList) {}

bool HintLineList::operator==(const HintLineList& other) const {
    return hintLineList == other.hintLineList;
}

bool HintLineList::operator!=(const HintLineList& other) const {
    return !(*this == other);
}

std::vector<HintLine> HintLineList::getHintLineList() const {
	return hintLineList;
}
