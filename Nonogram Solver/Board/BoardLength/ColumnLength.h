#ifndef COLUMNLENGTH_H
#define COLUMNLENGTH_H

#include "Board/BoardLength/BoardLength.h"

class ColumnLength : public BoardLength {
public:
    explicit ColumnLength(int length);

    ColumnLength operator+(ColumnLength length) const;
    ColumnLength operator-(ColumnLength length) const;
};

#endif
