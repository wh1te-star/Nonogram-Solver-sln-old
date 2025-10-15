#ifndef SHAREDBACKTRACKBOARD_H
#define SHAREDBACKTRACKBOARD_H


#include <mutex>
#include "Board/BacktrackBoard/BacktrackBoard.h"
#include "Rendering/TableRenderer/TableRenderer.h"

class SharedBacktrackBoard {
private:
    mutable std::mutex mtx;
    BacktrackBoard backtrackBoard;

public:
	SharedBacktrackBoard(BacktrackBoard backtrackBoard);

public:
    const BacktrackBoard& getBacktrackBoard() const;

public:
    void applyPlacement(Coordinate coordinate, Placement &placement);
};


#endif
