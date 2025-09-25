#ifndef BOARDLENGTH_H
#define BOARDLENGTH_H

class BoardLength {
protected:
    int length;
    BoardLength(int length);

public:
    int getLength() const;
    
    bool operator==(const BoardLength& other) const;
    bool operator!=(const BoardLength& other) const;
    bool operator<(const BoardLength& other) const;
    bool operator<=(const BoardLength& other) const;
    bool operator>(const BoardLength& other) const;
    bool operator>=(const BoardLength& other) const;

};

#endif
