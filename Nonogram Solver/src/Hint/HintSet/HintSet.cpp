#include "Hint/HintSet/HintSet.h"
#include "Hint/HintNumber/HintNumber.h"

HintSet::HintSet(std::vector<HintNumber> numbers) : numbers(numbers) {}

HintSet::HintSet(std::vector<int> numbers) {
	for(int number : numbers) {
		this->numbers.push_back(HintNumber(number));
	}
}

const std::vector<HintNumber>& HintSet::getNumbers() const {
	return numbers;
}

bool HintSet::operator==(const HintSet& other) const {
	return numbers == other.numbers;
}

bool HintSet::operator!=(const HintSet& other) const {
	return !(*this == other);
}

HintNumber HintSet::operator[](int index) const {
	return numbers[index];
}

size_t HintSet::size() const {
	return numbers.size();
}