#include "Rendering/HighlightIndexes/HighlightIndexes.h"


HighlightIndexes::HighlightIndexes(){}

void HighlightIndexes::addRowIndex(const RowIndex& rowIndex) {
	rowIndexes.insert(rowIndex);
}

void HighlightIndexes::addColumnIndex(const ColumnIndex& columnIndex) {
	columnIndexes.insert(columnIndex);
}

void HighlightIndexes::deleteRowIndex(const RowIndex& rowIndex) {
	rowIndexes.erase(rowIndex);
}

void HighlightIndexes::deleteColumnIndex(const ColumnIndex& columnIndex) {
	columnIndexes.erase(columnIndex);
}

bool HighlightIndexes::findRowIndex(const RowIndex& rowIndex) const {
	return rowIndexes.find(rowIndex) != rowIndexes.end();
}

bool HighlightIndexes::findColumnIndex(const ColumnIndex& columnIndex) const {
	return columnIndexes.find(columnIndex) != columnIndexes.end();
}

void HighlightIndexes::clear() {
	rowIndexes.clear();
	columnIndexes.clear();
}

void HighlightIndexes::clearRowIndexes() {
	rowIndexes.clear();
}

void HighlightIndexes::clearColumnIndexes() {
	columnIndexes.clear();
}
