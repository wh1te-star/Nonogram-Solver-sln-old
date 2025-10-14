#ifndef BOARDLENGTH_H
#define BOARDLENGTH_H

class BoardLength {
protected:
    const int length;
    BoardLength(int length);

public:
    const int& getLength() const;
};

#endif
