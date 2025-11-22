#include "Index/CellIndex/CellIndex.h"

#include <algorithm>
#include <vector>
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

std::vector<RowIndex> RowIndex::range(int first, int last){
    const int minVal = std::min(first, last);
    const int maxVal = std::max(first, last);
    const size_t range_size = maxVal - minVal + 1;
	std::vector<RowIndex> indexes = std::vector<RowIndex>(range_size, RowIndex(0));

    for (int index = 0; index <= maxVal - minVal; index++) {
		int value = index + minVal;
		indexes[index] = RowIndex(value);
    }

    if (first > last) {
        std::reverse(indexes.begin(), indexes.end());
    }
    
    return indexes;
}

