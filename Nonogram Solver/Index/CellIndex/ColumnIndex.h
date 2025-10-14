#ifndef COLUMNINDEX_H
#define COLUMNINDEX_H


#include "Index/CellIndex/CellIndex.h"
class ColumnLength;

class ColumnIndex : public CellIndex {
public:
    explicit ColumnIndex(int index);

public:
    ColumnIndex operator+(ColumnLength shift) const;
    ColumnIndex operator-(ColumnLength shift) const;
    bool operator==(const ColumnIndex& other) const;
    bool operator!=(const ColumnIndex& other) const;
    bool operator<(const ColumnIndex& other) const;
    bool operator<=(const ColumnIndex& other) const;
    bool operator>(const ColumnIndex& other) const;
    bool operator>=(const ColumnIndex& other) const;
    bool operator<(const ColumnLength& other) const;
    bool operator<=(const ColumnLength& other) const;
    bool operator>(const ColumnLength& other) const;
    bool operator>=(const ColumnLength& other) const;
};

#endif
