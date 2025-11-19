#ifndef ROWINDEX_H
#define ROWINDEX_H


#include "Index/CellIndex/CellIndex.h"
class RowLength;

class RowIndex : public CellIndex {
public:
    explicit RowIndex(int index);

public:
    RowIndex operator+(int shift) const;
    RowIndex operator-(int shift) const;
    RowIndex operator+(RowLength shift) const;
    RowIndex operator-(RowLength shift) const;
    RowIndex operator+(HintNumber shift) const;
    RowIndex operator-(HintNumber shift) const;
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
    static std::vector<RowIndex> iterate(const int start, const int end);
};

namespace std {
    template <>
    struct hash<RowIndex> {
        size_t operator()(const RowIndex& rowIndex) const {
            return std::hash<int>{}(rowIndex.getIndex()); 
        }
    };
}


#endif
