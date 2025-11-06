#include "Index/CellIndex/CellIndex.h"

#include "Board/BoardLength/BoardLength.h"


CellIndex::CellIndex(int index) : index(index) {}

const int& CellIndex::getIndex() const {
	return index;
}

CellIndex CellIndex::operator+(int shift) const {
    return CellIndex(index + shift);
}

CellIndex CellIndex::operator-(int shift) const {
    return CellIndex(index - shift);
}

CellIndex CellIndex::operator+(BoardLength shift) const {
    return CellIndex(index + shift.getLength());
}

CellIndex CellIndex::operator-(BoardLength shift) const {
    return CellIndex(index - shift.getLength());
}

CellIndex CellIndex::operator+(HintNumber shift) const {
    return CellIndex(index + shift.getNumber());
}

CellIndex CellIndex::operator-(HintNumber shift) const {
    return CellIndex(index - shift.getNumber());
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

