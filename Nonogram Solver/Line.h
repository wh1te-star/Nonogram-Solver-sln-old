#ifndef LINE_H
#define LINE_H


#include <vector>
#include "Cell.h"
#include "Orientation.h"

class Line {
private:
	Orientation orientation;
    std::vector<Cell> line;

    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;

public:
    explicit Line(Orientation orientation, std::vector<Cell> line);
};

#endif
