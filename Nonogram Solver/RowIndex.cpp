#include "RowIndex.h"

RowIndex::RowIndex(int index) : CellIndex(index) {}

RowIndex RowIndex::operator+(int shift) const {
    return RowIndex(index + shift);
}

RowIndex RowIndex::operator-(int shift) const {
    return RowIndex(index - shift);
}
