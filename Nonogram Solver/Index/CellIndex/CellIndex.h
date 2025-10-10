#ifndef CELLINDEX_H
#define CELLINDEX_H


#include "Board/BoardLength/BoardLength.h"

class CellIndex {
protected:
    int index;
    explicit CellIndex(int index);

public:
    int getIndex() const;
    
    bool operator==(const CellIndex& other) const;
    bool operator!=(const CellIndex& other) const;
    bool operator<(const CellIndex& other) const;
    bool operator<=(const CellIndex& other) const;
    bool operator>(const CellIndex& other) const;
    bool operator>=(const CellIndex& other) const;
    bool operator<(const BoardLength& other) const;
    bool operator<=(const BoardLength& other) const;
    bool operator>(const BoardLength& other) const;
    bool operator>=(const BoardLength& other) const;

};

#endif
