#ifndef ROWLENGTH_H
#define ROWLENGTH_H


#include "Board/BoardLength/BoardLength.h"
class RowIndex;

class RowLength : public BoardLength {
public:
    explicit RowLength(int length);

    RowLength operator+(RowLength length) const;
    RowLength operator-(RowLength length) const;

    bool operator==(const RowLength& other) const;
    bool operator!=(const RowLength& other) const;
    bool operator<(const RowLength& other) const;
    bool operator<=(const RowLength& other) const;
    bool operator>(const RowLength& other) const;
    bool operator>=(const RowLength& other) const;
    bool operator<(const RowIndex& other) const;
    bool operator<=(const RowIndex& other) const;
    bool operator>(const RowIndex& other) const;
    bool operator>=(const RowIndex& other) const;
};


#endif
