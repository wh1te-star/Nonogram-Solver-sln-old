#include "Index/CellIndex/ColumnIndex.h"

#include <algorithm>
#include <vector>
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

std::vector<ColumnIndex> ColumnIndex::range(int first, int last){
    const int minVal = std::min(first, last);
    const int maxVal = std::max(first, last);
    const size_t range_size = maxVal - minVal + 1;
	std::vector<ColumnIndex> indexes = std::vector<ColumnIndex>(range_size, ColumnIndex(0));

    for (int index = 0; index <= maxVal - minVal; index++) {
		int value = index + minVal;
		indexes[index] = ColumnIndex(value);
    }

    if (first > last) {
        std::reverse(indexes.begin(), indexes.end());
    }
    
    return indexes;
}

