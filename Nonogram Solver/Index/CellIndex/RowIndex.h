#ifndef ROWINDEX_H
#define ROWINDEX_H


#include "Index/CellIndex/CellIndex.h"
#include "Board/BoardLength/RowLength.h"

class RowIndex : public CellIndex {
public:
    explicit RowIndex(int index);

    RowIndex operator+(RowLength shift) const;
    RowIndex operator-(RowLength shift) const;
};


#endif
