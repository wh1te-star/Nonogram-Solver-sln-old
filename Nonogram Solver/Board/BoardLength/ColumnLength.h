#ifndef COLUMNLENGTH_H
#define COLUMNLENGTH_H

#include "Board/BoardLength/BoardLength.h"
class ColumnIndex;

class ColumnLength : public BoardLength {
public:
    explicit ColumnLength(int length);

    ColumnLength operator+(ColumnLength length) const;
    ColumnLength operator-(ColumnLength length) const;

    bool operator==(const ColumnLength& other) const;
    bool operator!=(const ColumnLength& other) const;
    bool operator<(const ColumnLength& other) const;
    bool operator<=(const ColumnLength& other) const;
    bool operator>(const ColumnLength& other) const;
    bool operator>=(const ColumnLength& other) const;
    bool operator<(const ColumnIndex& other) const;
    bool operator<=(const ColumnIndex& other) const;
    bool operator>(const ColumnIndex& other) const;
    bool operator>=(const ColumnIndex& other) const;
};

#endif
