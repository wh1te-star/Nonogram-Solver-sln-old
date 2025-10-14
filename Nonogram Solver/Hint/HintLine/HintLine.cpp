#include "Hint/HintLine/HintLine.h"
#include "Hint/HintNumber/HintNumber.h"

HintLine::HintLine(std::vector<HintNumber> numbers) : numbers(numbers) {}

const std::vector<HintNumber>& HintLine::getNumbers() const {
	return numbers;
}

bool HintLine::operator==(const HintLine& other) const {
	return numbers == other.numbers;
}

bool HintLine::operator!=(const HintLine& other) const {
	return !(*this == other);
}

HintNumber HintLine::operator[](CellIndex index) const {
	return numbers[index.getIndex()];
}

size_t HintLine::size() const {
	return numbers.size();
}