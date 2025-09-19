#include "RowIndex.h"

RowIndex::RowIndex(int idx) : index(idx) {}

int RowIndex::get() const {
    return index;
}

RowIndex RowIndex::operator+(int shift) const {
    return RowIndex(index + shift);
}

RowIndex RowIndex::operator-(int shift) const {
    return RowIndex(index - shift);
}

bool RowIndex::operator==(const RowIndex& other) const {
    return index == other.index;
}

bool RowIndex::operator!=(const RowIndex& other) const {
    return index != other.index;
}

bool RowIndex::operator<(const RowIndex& other) const {
    return index < other.index;
}

bool RowIndex::operator<=(const RowIndex& other) const {
    return index <= other.index;
}

bool RowIndex::operator>(const RowIndex& other) const {
    return index > other.index;
}

bool RowIndex::operator>=(const RowIndex& other) const {
    return index >= other.index;
}
