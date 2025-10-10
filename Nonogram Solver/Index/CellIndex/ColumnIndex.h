#ifndef COLUMNINDEX_H
#define COLUMNINDEX_H


#include "Index/CellIndex/CellIndex.h"
#include "Board/BoardLength/ColumnLength.h"

class ColumnIndex : public CellIndex {
public:
    explicit ColumnIndex(int index);

    ColumnIndex operator+(ColumnLength shift) const;
    ColumnIndex operator-(ColumnLength shift) const;
};

#endif
