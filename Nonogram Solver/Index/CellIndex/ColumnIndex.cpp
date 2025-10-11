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
bool ColumnIndex::operator<(const ColumnLength& other) const {
	return index < other.getLength();
}

bool ColumnIndex::operator<=(const ColumnLength& other) const {
	return index <= other.getLength();
}

bool ColumnIndex::operator>(const ColumnLength& other) const {
	return index > other.getLength();
}

bool ColumnIndex::operator>=(const ColumnLength& other) const {
	return index >= other.getLength();
}
