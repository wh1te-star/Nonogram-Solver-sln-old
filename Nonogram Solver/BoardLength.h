#ifndef BOARDLENGTH_H
#define BOARDLENGTH_H

class BoardLength {
protected:
    int length;
    BoardLength(int length) : length(length) {}

public:
    int getLength() const { return length; }
    
    bool operator==(const BoardLength& other) const;
    bool operator!=(const BoardLength& other) const;
    bool operator<(const BoardLength& other) const;
    bool operator<=(const BoardLength& other) const;
    bool operator>(const BoardLength& other) const;
    bool operator>=(const BoardLength& other) const;

};

#endif
