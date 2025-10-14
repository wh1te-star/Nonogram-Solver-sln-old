#include "Hint/HintNumber/HintNumber.h"

HintNumber::HintNumber(int number) : number(number) {}

const int& HintNumber::getNumber() const {
    return number;
}

bool HintNumber::operator==(const HintNumber& other) const {
    return number == other.number;
}

bool HintNumber::operator!=(const HintNumber& other) const {
	return !(*this == other);
}
