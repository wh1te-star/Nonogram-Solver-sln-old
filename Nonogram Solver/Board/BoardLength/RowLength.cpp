#include "Board/BoardLength/RowLength.h"
#include "Index/CellIndex/RowIndex.h"

RowLength::RowLength(int length) : BoardLength(length) {}

RowLength RowLength::operator+(RowLength length) const {
    return RowLength(this->length + length.length);
}

RowLength RowLength::operator-(RowLength length) const {
    return RowLength(this->length - length.length);
}

bool RowLength::operator==(const RowLength& other) const {
	return length == other.length;
}

bool RowLength::operator!=(const RowLength& other) const {
	return length != other.length;
}

bool RowLength::operator<(const RowLength& other) const {
	return length < other.length;
}

bool RowLength::operator<=(const RowLength& other) const {
	return length <= other.length;
}

bool RowLength::operator>(const RowLength& other) const {
	return length > other.length;
}

bool RowLength::operator>=(const RowLength& other) const {
	return length >= other.length;
}

bool RowLength::operator<(const RowIndex& other) const {
	return length < other.getIndex();
}

bool RowLength::operator<=(const RowIndex& other) const {
	return length <= other.getIndex();
}

bool RowLength::operator>(const RowIndex& other) const {
	return length > other.getIndex();
}

bool RowLength::operator>=(const RowIndex& other) const {
	return length >= other.getIndex();
}
