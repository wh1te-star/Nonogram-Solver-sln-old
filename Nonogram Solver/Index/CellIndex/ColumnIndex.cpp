#include "Index/CellIndex/ColumnIndex.h"

#include "Index/CellIndex/CellIndex.h"
#include "Board/BoardLength/ColumnLength.h"

ColumnIndex::ColumnIndex(int index) : CellIndex(index) {}

ColumnIndex ColumnIndex::operator+(ColumnLength shift) const {
    return ColumnIndex(index + shift.getLength());
}

ColumnIndex ColumnIndex::operator-(ColumnLength shift) const {
    return ColumnIndex(index - shift.getLength());
}
