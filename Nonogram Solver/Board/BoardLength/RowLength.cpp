#include "Board/BoardLength/RowLength.h"

RowLength::RowLength(int length) : BoardLength(length) {}

RowLength RowLength::operator+(RowLength length) const {
    return RowLength(this->length + length.length);
}

RowLength RowLength::operator-(RowLength length) const {
    return RowLength(this->length - length.length);
}
