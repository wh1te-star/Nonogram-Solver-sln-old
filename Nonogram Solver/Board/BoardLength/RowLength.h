#ifndef ROWLENGTH_H
#define ROWLENGTH_H


#include "Board/BoardLength/BoardLength.h"

class RowLength : public BoardLength {
public:
    explicit RowLength(int length);

    RowLength operator+(RowLength length) const;
    RowLength operator-(RowLength length) const;
};


#endif
