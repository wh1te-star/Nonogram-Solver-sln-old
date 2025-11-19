#ifndef HINTSET_H
#define HINTSET_H


#include <vector>
#include "Index/CellIndex/CellIndex.h"
#include "Hint/HintNumber/HintNumber.h"

class HintSet {
private:
	std::vector<HintNumber> numbers;

public:
	HintSet(std::vector<HintNumber> numbers);
	HintSet(std::vector<int> numbers);

public:
	const std::vector<HintNumber>& getNumbers() const;

public:
	bool operator==(const HintSet& other) const;
	bool operator!=(const HintSet& other) const;
	HintNumber operator[](int index) const;

public:
	size_t size() const;
};


#endif
