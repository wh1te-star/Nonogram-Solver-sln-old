#include "ColumnIndex.h"

ColumnIndex::ColumnIndex(int index) : CellIndex(index) {}

ColumnIndex ColumnIndex::operator+(int shift) const {
    return ColumnIndex(index + shift);
}

ColumnIndex ColumnIndex::operator-(int shift) const {
    return ColumnIndex(index - shift);
}
