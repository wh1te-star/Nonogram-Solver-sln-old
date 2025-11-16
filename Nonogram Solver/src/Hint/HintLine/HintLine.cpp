#include "Hint/HintLine/HintLine.h"
#include "Hint/HintNumber/HintNumber.h"

HintLine::HintLine(std::vector<HintNumber> numbers) : numbers(numbers) {}

HintLine::HintLine(std::vector<int> numbers) {
	for(int number : numbers) {
		this->numbers.emplace_back(HintNumber(number));
	}
}

const std::vector<HintNumber>& HintLine::getNumbers() const {
	return numbers;
}

bool HintLine::operator==(const HintLine& other) const {
	return numbers == other.numbers;
}

bool HintLine::operator!=(const HintLine& other) const {
	return !(*this == other);
}

HintNumber HintLine::operator[](int index) const {
	return numbers[index];
}

size_t HintLine::size() const {
	return numbers.size();
}