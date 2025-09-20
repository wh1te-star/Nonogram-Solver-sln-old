#ifndef LINE_H
#define LINE_H


#include <vector>
#include "CellState.h"
#include "Orientation.h"

class Line {
private:
	const Orientation orientation;
    const std::vector<CellState> line;

public:
    explicit Line(Orientation orientation, std::vector<CellState> line);
};

#endif
