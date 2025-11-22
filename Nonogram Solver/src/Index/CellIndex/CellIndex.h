#ifndef CELLINDEX_H
#define CELLINDEX_H


#include <vector>
#include "Board/BoardLength/BoardLength.h"
#include "Hint/HintNumber/HintNumber.h"

class CellIndex {
protected:
    int index;

public:
    explicit CellIndex(int index);

public:
    const int& getIndex() const;

public:
    CellIndex operator+(int shift) const;
    CellIndex operator-(int shift) const;
    CellIndex operator+(BoardLength shift) const;
    CellIndex operator-(BoardLength shift) const;
    CellIndex operator+(HintNumber shift) const;
    CellIndex operator-(HintNumber shift) const;
    CellIndex operator++();
    CellIndex operator--();
    CellIndex operator++(int);
    CellIndex operator--(int);
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
    static std::vector<CellIndex> range(int first, int last);
};

#endif
