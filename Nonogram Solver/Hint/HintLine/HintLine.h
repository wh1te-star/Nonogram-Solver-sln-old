#ifndef HINTLINE_H
#define HINTLINE_H


#include <vector>
#include "Index/CellIndex/CellIndex.h"
#include "Hint/HintNumber/HintNumber.h"

class HintLine {
private:
	const std::vector<HintNumber> numbers;

public:
	HintLine(std::vector<HintNumber> numbers);

public:
	const std::vector<HintNumber>& getNumbers() const;

public:
	bool operator==(const HintLine& other) const;
	bool operator!=(const HintLine& other) const;
	HintNumber operator[](CellIndex index) const;

public:
	size_t size() const;
};


#endif
