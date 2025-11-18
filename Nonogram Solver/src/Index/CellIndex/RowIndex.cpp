#include "Index/CellIndex/CellIndex.h"

#include "Index/CellIndex/RowIndex.h"
#include "Board/BoardLength/RowLength.h"

RowIndex::RowIndex(int index) : CellIndex(index) {}

RowIndex RowIndex::operator+(int shift) const {
    return RowIndex(index + shift);
}

RowIndex RowIndex::operator-(int shift) const {
    return RowIndex(index - shift);
}

RowIndex RowIndex::operator+(RowLength shift) const {
    return RowIndex(index + shift.getLength());
}

RowIndex RowIndex::operator-(RowLength shift) const {
    return RowIndex(index - shift.getLength());
}

RowIndex RowIndex::operator+(HintNumber shift) const {
    return RowIndex(index + shift.getNumber());
}

RowIndex RowIndex::operator-(HintNumber shift) const {
    return RowIndex(index - shift.getNumber());
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
bool RowIndex::operator<(const RowLength& other) const {
	return index < other.getLength();
}

bool RowIndex::operator<=(const RowLength& other) const {
	return index <= other.getLength();
}

bool RowIndex::operator>(const RowLength& other) const {
	return index > other.getLength();
}

bool RowIndex::operator>=(const RowLength& other) const {
	return index >= other.getLength();
}

std::vector<RowIndex> RowIndex::iterate(const int start, const int end){
	std::vector<RowIndex> indexes;
	for (int i = start; i < end; i++) {
		indexes.push_back(RowIndex(i));
	}
	return indexes;
}

