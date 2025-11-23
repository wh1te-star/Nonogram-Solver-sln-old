#ifndef SHAREDBACKTRACKSTACK_H
#define SHAREDBACKTRACKSTACK_H


#include <mutex>
#include "Algorithm/Backtrack/BacktrackStack/BacktrackStack.h"

class SharedBacktrackStack {
private:
    mutable std::mutex mtx;
    BacktrackStack backtrackStack;

public:
	SharedBacktrackStack(BacktrackStack backtrackStack);

public:
	BacktrackStack getBacktrackStack() const;
	int getDepthAtRowIndex(RowIndex rowIndex) const;
	int getDepthAtColumnIndex(ColumnIndex columnIndex) const;
	void pushRowIndex(RowIndex rowIndex);
	void pushColumnIndex(ColumnIndex columnIndex);
	void popDepth();
};


#endif
