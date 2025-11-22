#ifndef SHAREDHIGHLIGHTINDEXES_H
#define SHAREDHIGHLIGHTINDEXES_H


#include <mutex>
#include "Rendering/HighlightIndexes/HighlightIndexes.h"
#include "Rendering/TableRenderer/TableRenderer.h"

class SharedHighlightIndexes {
private:
    mutable std::mutex mtx;
	HighlightIndexes highlightIndexes;

public:
	SharedHighlightIndexes();

public:
	HighlightIndexes getHighlightIndexes() const;
	void addRowIndex(RowIndex rowIndex);
	void addColumnIndex(ColumnIndex columnIndex);
	void deleteRowIndex(RowIndex rowIndex);
	void deleteColumnIndex(ColumnIndex columnIndex);
	bool findRowIndex(RowIndex rowIndex) const;
	bool findColumnIndex(ColumnIndex columnIndex) const;
	void clear();
	void clearRowIndexes();
	void clearColumnIndexes();
};


#endif
