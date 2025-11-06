#ifndef COLUMN_H
#define COLUMN_H


#include "Board/Line/Line.h"
#include "Index/Coordinate/Coordinate.h"

class Column : public Line {
public:
    explicit Column(std::vector<Cell> line);
};


#endif
