#ifndef COORDINATE_H
#define COORDINATE_H


#include "Index/CellIndex/RowIndex.h"
#include "Index/CellIndex/ColumnIndex.h"
#include "Board/BoardLength/RowLength.h"
#include "Board/BoardLength/ColumnLength.h"

class Coordinate {
private:
    RowIndex rowIndex;
    ColumnIndex columnIndex;

public:
    explicit Coordinate(RowIndex rowIndex, ColumnIndex columnIndex);

    bool operator==(const Coordinate& other) const;
    bool operator!=(const Coordinate& other) const;

    RowIndex getRowIndex() const;
    ColumnIndex getColumnIndex() const;

    Coordinate move(int rowShift, int columnShift) const;
    Coordinate move(RowLength rowShift, ColumnLength columnShift) const;
};

#endif
