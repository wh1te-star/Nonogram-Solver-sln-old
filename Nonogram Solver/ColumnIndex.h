#ifndef COLUMNINDEX_H
#define COLUMNINDEX_H

class ColumnIndex {
private:
    const int index;

public:
    explicit ColumnIndex(int idx);

    int get() const;

    ColumnIndex operator+(int shift) const;
    ColumnIndex operator-(int shift) const;

    bool operator==(const ColumnIndex& other) const;
    bool operator!=(const ColumnIndex& other) const;
    bool operator<(const ColumnIndex& other) const;
    bool operator<=(const ColumnIndex& other) const;
    bool operator>(const ColumnIndex& other) const;
    bool operator>=(const ColumnIndex& other) const;
};

#endif
