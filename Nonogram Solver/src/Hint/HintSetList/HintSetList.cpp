#include "Hint/HintSetList/HintSetList.h"

#include <algorithm>
#include "Hint/HintSet/HintSet.h"


HintSetList::HintSetList(std::vector<HintSet> hintSetList) :
	hintSetList(hintSetList) {}

const std::vector<HintSet>& HintSetList::getHintSetList() const {
	return hintSetList;
}

bool HintSetList::operator==(const HintSetList& other) const {
    return hintSetList == other.hintSetList;
}

bool HintSetList::operator!=(const HintSetList& other) const {
    return !(*this == other);
}

const HintSet& HintSetList::operator[](const CellIndex& index) const {
    return hintSetList[index.getIndex()];
}

int HintSetList::getMaxItemCount() const {
    int maxSize = 0;
    for (const auto& HintSet : hintSetList) {
        maxSize = std::max(maxSize, (int)HintSet.size());
    }
    return maxSize;
}

