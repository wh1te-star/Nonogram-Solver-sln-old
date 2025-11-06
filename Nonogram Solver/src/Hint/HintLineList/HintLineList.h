#ifndef HINTLINELIST_H
#define HINTLINELIST_H


#include <vector>
#include "Board/BoardLength/BoardLength.h"
#include "Hint/HintLine/HintLine.h"

class HintLineList {
private:

protected:
	std::vector<HintLine> hintLineList;

public:
    explicit HintLineList(std::vector<HintLine> hintLineList);
    virtual ~HintLineList() = default;

public:
    const std::vector<HintLine>& getHintLineList() const;

public:
    bool operator==(const HintLineList& other) const;
    bool operator!=(const HintLineList& other) const;

public:
	int getMaxItemCount() const;
};

#endif
