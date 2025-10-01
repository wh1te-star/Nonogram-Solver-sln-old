#ifndef PLACEMENTCOUNT_H
#define PLACEMENTCOUNT_H


class PlacementCount {
private:
    int count;

public:
	explicit PlacementCount(int count);

    int getCount() const;

    bool operator==(const PlacementCount& other) const;
    bool operator!=(const PlacementCount& other) const;
};

#endif
