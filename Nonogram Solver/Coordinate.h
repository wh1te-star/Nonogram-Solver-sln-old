#include "RowIndex.h"
#include "ColumnIndex.h"

#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate {
private:
    const RowIndex rowIndex;
    const ColumnIndex columnIndex;

public:
    explicit Coordinate(RowIndex rowIndex, ColumnIndex columnIndex);

    Coordinate move(int rowShift, int columnShift) const;
};

#endif
