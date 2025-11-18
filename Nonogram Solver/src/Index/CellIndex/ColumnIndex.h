#ifndef COLUMNINDEX_H
#define COLUMNINDEX_H


#include "Index/CellIndex/CellIndex.h"
class ColumnLength;

class ColumnIndex : public CellIndex {
public:
    explicit ColumnIndex(int index);

public:
    ColumnIndex operator+(int shift) const;
    ColumnIndex operator-(int shift) const;
    ColumnIndex operator+(ColumnLength shift) const;
    ColumnIndex operator-(ColumnLength shift) const;
    ColumnIndex operator+(HintNumber shift) const;
    ColumnIndex operator-(HintNumber shift) const;
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
    static std::vector<ColumnIndex> iterate(const int start, const int end);
};

#endif
