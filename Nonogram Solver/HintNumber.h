#ifndef HINTNUMBER_H
#define HINTNUMBER_H


class HintNumber {
private:
	int number;

public:
    explicit HintNumber(int number);

    int getNumber() const;

    bool operator==(const HintNumber& other) const;
    bool operator!=(const HintNumber& other) const;
};

#endif
