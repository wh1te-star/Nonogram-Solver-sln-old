#ifndef TABLERENDERER_H
#define TABLERENDERER_H


#include "Board/BacktrackBoard/BacktrackBoard.h"

class TableRenderer {
private:
	BacktrackBoard backtrackBoard;
public:
	TableRenderer(BacktrackBoard backtrackBoard);
	void render();
};


#endif
