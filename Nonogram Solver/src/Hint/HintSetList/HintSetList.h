#ifndef HINTSETLIST_H
#define HINTSETLIST_H


#include <vector>
#include "Board/BoardLength/BoardLength.h"
#include "Hint/HintSet/HintSet.h"

class HintSetList {
private:

protected:
	std::vector<HintSet> hintSetList;

public:
    explicit HintSetList(std::vector<HintSet> HintSetList);
    virtual ~HintSetList() = default;

public:
    const std::vector<HintSet>& getHintSetList() const;

public:
    bool operator==(const HintSetList& other) const;
    bool operator!=(const HintSetList& other) const;
	const HintSet& operator[](const CellIndex& index) const;

public:
	int getMaxItemCount() const;
};

#endif
