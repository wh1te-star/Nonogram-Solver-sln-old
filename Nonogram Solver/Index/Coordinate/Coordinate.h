#ifndef COORDINATE_H
#define COORDINATE_H


#include "Index/CellIndex/RowIndex.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"

class Coordinate {
private:
    const RowIndex rowIndex;
    const ColumnIndex columnIndex;

public:
    explicit Coordinate(RowIndex rowIndex, ColumnIndex columnIndex);

public:
    const RowIndex& getRowIndex() const;
    const ColumnIndex& getColumnIndex() const;

public:
    bool operator==(const Coordinate& other) const;
    bool operator!=(const Coordinate& other) const;

public:
    Coordinate move(int rowShift, int columnShift) const;
    Coordinate move(RowLength rowShift, ColumnLength columnShift) const;
};

#endif
