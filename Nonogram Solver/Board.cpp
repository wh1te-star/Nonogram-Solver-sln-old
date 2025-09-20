#include "Board.h"

ColumnIndex::ColumnIndex(int idx) : index(idx) {}

int ColumnIndex::get() const {
    return index;
}

ColumnIndex ColumnIndex::operator+(int shift) const {
    return ColumnIndex(index + shift);
}

ColumnIndex ColumnIndex::operator-(int shift) const {
    return ColumnIndex(index - shift);
}

bool ColumnIndex::operator==(const ColumnIndex& other) const {
    return index == other.index;
}

bool ColumnIndex::operator!=(const ColumnIndex& other) const {
    return index != other.index;
}

bool ColumnIndex::operator<(const ColumnIndex& other) const {
    return index < other.index;
}

bool ColumnIndex::operator<=(const ColumnIndex& other) const {
    return index <= other.index;
}

bool ColumnIndex::operator>(const ColumnIndex& other) const {
    return index > other.index;
}

bool ColumnIndex::operator>=(const ColumnIndex& other) const {
    return index >= other.index;
}
