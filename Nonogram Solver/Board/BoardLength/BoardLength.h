#ifndef BOARDLENGTH_H
#define BOARDLENGTH_H

class BoardLength {
private:
    const int length;

public:
    BoardLength(int length);

public:
    const int& getLength() const;
};

#endif
