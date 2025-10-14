#include "Board/BoardLength/BoardLength.h"

BoardLength::BoardLength(int length) : length(length) {}

const int& BoardLength::getLength() const {
	return length;
}
