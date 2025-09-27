#include "HintNumber.h"

HintNumber::HintNumber(int number) : number(number) {}

int HintNumber::getNumber() const {
    return number;
}

bool HintNumber::operator==(const HintNumber& other) const {
    return number == other.number;
}

bool HintNumber::operator!=(const HintNumber& other) const {
	return !(*this == other);
}
