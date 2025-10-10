#include "Index/CellIndex/CellIndex.h"

#include "Board/BoardLength/BoardLength.h"


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
bool CellIndex::operator<(const BoardLength& other) const {
	return index < other.getLength();
}

bool CellIndex::operator<=(const BoardLength& other) const {
	return index <= other.getLength();
}

bool CellIndex::operator>(const BoardLength& other) const {
	return index > other.getLength();
}

bool CellIndex::operator>=(const BoardLength& other) const {
	return index >= other.getLength();
}