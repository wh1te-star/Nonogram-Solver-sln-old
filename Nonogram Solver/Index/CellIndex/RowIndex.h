#ifndef ROWINDEX_H
#define ROWINDEX_H


#include "Index/CellIndex/CellIndex.h"
class RowLength;

class RowIndex : public CellIndex {
public:
    explicit RowIndex(int index);

    RowIndex operator+(RowLength shift) const;
    RowIndex operator-(RowLength shift) const;

    bool operator==(const RowIndex& other) const;
    bool operator!=(const RowIndex& other) const;
    bool operator<(const RowIndex& other) const;
    bool operator<=(const RowIndex& other) const;
    bool operator>(const RowIndex& other) const;
    bool operator>=(const RowIndex& other) const;
    bool operator<(const RowLength& other) const;
    bool operator<=(const RowLength& other) const;
    bool operator>(const RowLength& other) const;
    bool operator>=(const RowLength& other) const;
};


#endif
