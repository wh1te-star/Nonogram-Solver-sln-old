#include "Index/CellIndex/ColumnIndex.h"

#include "Index/CellIndex/CellIndex.h"
#include "Board/BoardLength/ColumnLength.h"

ColumnIndex::ColumnIndex(int index) : CellIndex(index) {}

ColumnIndex ColumnIndex::operator+(int shift) const {
    return ColumnIndex(index + shift);
}

ColumnIndex ColumnIndex::operator-(int shift) const {
    return ColumnIndex(index - shift);
}

ColumnIndex ColumnIndex::operator+(ColumnLength shift) const {
    return ColumnIndex(index + shift.getLength());
}

ColumnIndex ColumnIndex::operator-(ColumnLength shift) const {
    return ColumnIndex(index - shift.getLength());
}

ColumnIndex ColumnIndex::operator+(HintNumber shift) const {
    return ColumnIndex(index + shift.getNumber());
}

ColumnIndex ColumnIndex::operator-(HintNumber shift) const {
    return ColumnIndex(index - shift.getNumber());
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

std::vector<ColumnIndex> ColumnIndex::iterate(const int start, const int end){
	std::vector<ColumnIndex> indexes;
	for (int i = start; i < end; i++) {
		indexes.push_back(ColumnIndex(i));
	}
	return indexes;
}

