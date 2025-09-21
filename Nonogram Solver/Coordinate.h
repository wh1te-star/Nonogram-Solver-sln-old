#include "RowIndex.h"
#include "ColumnIndex.h"

#ifndef COORDINATE_H
#define COORDINATE_H

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
};

#endif
