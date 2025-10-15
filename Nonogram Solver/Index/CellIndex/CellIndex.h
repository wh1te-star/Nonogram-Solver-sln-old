#ifndef CELLINDEX_H
#define CELLINDEX_H


#include "Board/BoardLength/BoardLength.h"

class CellIndex {
protected:
    int index;
    explicit CellIndex(int index);

public:
    const int& getIndex() const;
};

#endif
