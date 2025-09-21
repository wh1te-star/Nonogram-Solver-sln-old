#ifndef COLUMNINDEX_H
#define COLUMNINDEX_H


#include "CellIndex.h"

class ColumnIndex : public CellIndex {
public:
    explicit ColumnIndex(int index);

    ColumnIndex operator+(int shift) const;
    ColumnIndex operator-(int shift) const;
};

#endif
