#ifndef LINE_H
#define LINE_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"
#include "Index/Coordinate/Coordinate.h"

class Line {
private:

protected:
    std::vector<Cell> line;

public:
    explicit Line(std::vector<Cell> line);
    virtual ~Line() = default;

public:
	const std::vector<Cell>& getLine() const;

public:
    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;
	Cell operator[](const CellIndex& index) const;

public:
	const size_t size() const;
    const std::vector<CellLocation> getCellLocationList(const Coordinate& coordinate) const;
	bool canPlaceBlock(const CellIndex& startIndex, const HintNumber& hintNumber) const;
};

#endif
