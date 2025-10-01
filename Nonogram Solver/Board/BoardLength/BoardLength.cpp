#include "Board/BoardLength/BoardLength.h"

BoardLength::BoardLength(int length) : length(length) {}

int BoardLength::getLength() const {
	return length;
}

bool BoardLength::operator==(const BoardLength& other) const {
	return length == other.length;
}

bool BoardLength::operator!=(const BoardLength& other) const {
	return length != other.length;
}

bool BoardLength::operator<(const BoardLength& other) const {
	return length < other.length;
}

bool BoardLength::operator<=(const BoardLength& other) const {
	return length <= other.length;
}

bool BoardLength::operator>(const BoardLength& other) const {
	return length > other.length;
}

bool BoardLength::operator>=(const BoardLength& other) const {
	return length >= other.length;
}