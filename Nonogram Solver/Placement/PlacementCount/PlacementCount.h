#ifndef PLACEMENTCOUNT_H
#define PLACEMENTCOUNT_H


class PlacementCount {
private:
    const int count;

public:
	explicit PlacementCount(int count);

public:
    const int& getCount() const;

public:
    bool operator==(const PlacementCount& other) const;
    bool operator!=(const PlacementCount& other) const;
};

#endif
