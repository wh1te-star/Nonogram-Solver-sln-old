#include "Index/CellIndex/CellIndex.h"

CellIndex::CellIndex(int index) : index(index) {}

int CellIndex::getIndex() const {
	return index;
}

bool CellIndex::operator==(const CellIndex& other) const {
	return index == other.index;
}

bool CellIndex::operator!=(const CellIndex& other) const {
	return index != other.index;
}

bool CellIndex::operator<(const CellIndex& other) const {
	return index < other.index;
}

bool CellIndex::operator<=(const CellIndex& other) const {
	return index <= other.index;
}

bool CellIndex::operator>(const CellIndex& other) const {
	return index > other.index;
}

bool CellIndex::operator>=(const CellIndex& other) const {
	return index >= other.index;
}