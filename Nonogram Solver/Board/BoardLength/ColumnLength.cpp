#include "Board/BoardLength/ColumnLength.h"

ColumnLength::ColumnLength(int length) : BoardLength(length) {}

ColumnLength ColumnLength::operator+(ColumnLength length) const {
    return ColumnLength(this->length + length.length);
}

ColumnLength ColumnLength::operator-(ColumnLength length) const {
    return ColumnLength(this->length - length.length);
}
