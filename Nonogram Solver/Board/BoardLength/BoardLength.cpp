#include "Board/BoardLength/BoardLength.h"

BoardLength::BoardLength(int length) : length(length) {}

int BoardLength::getLength() const {
	return length;
}
