#ifndef HINTLINELIST_H
#define HINTLINELIST_H


#include <vector>
#include "Board/BoardLength/BoardLength.h"

class HintLineList {
private:

protected:
	std::vector<HintLine> hintLineList;

    explicit HintLineList(std::vector<HintLine> hintLineList);
	int getMaxItemCount() const;

public:
    virtual ~HintLineList() = default;
    bool operator==(const HintLineList& other) const;
    bool operator!=(const HintLineList& other) const;

    std::vector<HintLine> getHintLineList() const;
};

#endif
