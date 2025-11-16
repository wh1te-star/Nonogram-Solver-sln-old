#ifndef HINTLINE_H
#define HINTLINE_H


#include <vector>
#include "Index/CellIndex/CellIndex.h"
#include "Hint/HintNumber/HintNumber.h"

class HintLine {
private:
	std::vector<HintNumber> numbers;

public:
	HintLine(std::vector<HintNumber> numbers);
	HintLine(std::vector<int> numbers);

public:
	const std::vector<HintNumber>& getNumbers() const;

public:
	bool operator==(const HintLine& other) const;
	bool operator!=(const HintLine& other) const;
	HintNumber operator[](int index) const;

public:
	size_t size() const;
};


#endif
