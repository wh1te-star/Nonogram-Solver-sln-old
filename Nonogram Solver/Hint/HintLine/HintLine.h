#ifndef HINTLINE_H
#define HINTLINE_H


#include <vector>
#include "Hint/HintNumber/HintNumber.h"

class HintLine {
private:
	std::vector<HintNumber> numbers;

public:
	HintLine(std::vector<HintNumber> numbers);
	bool operator==(const HintLine& other) const;
	bool operator!=(const HintLine& other) const;

	size_t size() const;
	std::vector<HintNumber> getNumbers() const;
};


#endif
