#ifndef ROWINDEX_H
#define ROWINDEX_H


#include "Index/CellIndex/CellIndex.h"

class RowIndex : public CellIndex {
public:
    explicit RowIndex(int index);

    RowIndex operator+(int shift) const;
    RowIndex operator-(int shift) const;
};


#endif
