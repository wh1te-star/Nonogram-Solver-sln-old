#include "Index/CellIndex/CellIndex.h"

#include "Board/BoardLength/BoardLength.h"


CellIndex::CellIndex(int index) : index(index) {}

int CellIndex::getIndex() const {
	return index;
}
