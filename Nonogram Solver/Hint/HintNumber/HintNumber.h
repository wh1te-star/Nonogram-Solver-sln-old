#ifndef HINTNUMBER_H
#define HINTNUMBER_H


class HintNumber {
private:
	const int number;

public:
    explicit HintNumber(int number);

    const int& getNumber() const;

    bool operator==(const HintNumber& other) const;
    bool operator!=(const HintNumber& other) const;
};

#endif
