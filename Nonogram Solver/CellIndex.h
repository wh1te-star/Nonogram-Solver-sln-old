#ifndef CELLINDEX_H
#define CELLINDEX_H

class CellIndex {
protected:
    int index;
    CellIndex(int index) : index(index) {}

public:
    int getIndex() const { return index; }
    
    bool operator==(const CellIndex& other) const;
    bool operator!=(const CellIndex& other) const;
    bool operator<(const CellIndex& other) const;
    bool operator<=(const CellIndex& other) const;
    bool operator>(const CellIndex& other) const;
    bool operator>=(const CellIndex& other) const;

};

#endif
