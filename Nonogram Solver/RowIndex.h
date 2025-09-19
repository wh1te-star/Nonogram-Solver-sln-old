#ifndef ROWINDEX_H
#define ROWINDEX_H

class RowIndex {
private:
    const int index;

public:
    explicit RowIndex(int idx);

    int get() const;

    RowIndex operator+(int shift) const;
    RowIndex operator-(int shift) const;

    bool operator==(const RowIndex& other) const;
    bool operator!=(const RowIndex& other) const;
    bool operator<(const RowIndex& other) const;
    bool operator<=(const RowIndex& other) const;
    bool operator>(const RowIndex& other) const;
    bool operator>=(const RowIndex& other) const;
};

#endif
