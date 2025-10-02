#include "Hint/HintLine/HintLine.h"
#include "Hint/HintNumber/HintNumber.h"

HintLine::HintLine(std::vector<HintNumber> numbers) : numbers(numbers) {}

bool HintLine::operator==(const HintLine& other) const {
	return numbers == other.numbers;
}

bool HintLine::operator!=(const HintLine& other) const {
	return !(*this == other);
}

size_t HintLine::size() const {
	return numbers.size();
}

std::vector<HintNumber> HintLine::getNumbers() const {
	return numbers;
}