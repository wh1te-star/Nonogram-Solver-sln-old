#include "HintLine.h"

HintLine::HintLine(std::vector<HintNumber> numbers) : numbers(numbers) {}

bool HintLine::operator==(const HintLine& other) const {
	return numbers == other.numbers;
}

bool HintLine::operator!=(const HintLine& other) const {
	return !(*this == other);
}

std::vector<HintNumber> HintLine::getNumbers() const {
	return numbers;
}