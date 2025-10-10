#include "Index/CellIndex/CellIndex.h"

#include "Index/CellIndex/RowIndex.h"
#include "Board/BoardLength//RowLength.h"

RowIndex::RowIndex(int index) : CellIndex(index) {}

RowIndex RowIndex::operator+(RowLength shift) const {
    return RowIndex(index + shift.getLength());
}

RowIndex RowIndex::operator-(RowLength shift) const {
    return RowIndex(index - shift.getLength());
}
