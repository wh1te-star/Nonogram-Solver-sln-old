#ifndef PLACEMENTCOUNT_H
#define PLACEMENTCOUNT_H


class PlacementCount {
private:
    int count;

public:
	explicit PlacementCount(int count);

public:
    PlacementCount operator+(const PlacementCount& other) const;
    PlacementCount operator-(const PlacementCount& other) const;
    PlacementCount& operator+=(const PlacementCount& other);
    PlacementCount& operator-=(const PlacementCount& other);
	bool operator<(const PlacementCount& other) const;
	bool operator>(const PlacementCount& other) const;
	bool operator<=(const PlacementCount& other) const;
	bool operator>=(const PlacementCount& other) const;
    bool operator==(const PlacementCount& other) const;
    bool operator!=(const PlacementCount& other) const;

public:
    int getCount() const;
    void setCount(PlacementCount placementCount);

};

#endif
