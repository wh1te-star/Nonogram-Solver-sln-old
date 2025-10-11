#ifndef RENDERNOTIFIER_H
#define RENDERNOTIFIER_H


#include <mutex>
#include "Board/BacktrackBoard/BacktrackBoard.h"

class RenderNotifier {
private:
    std::mutex mtx;
    BacktrackBoard* backtrackBoardPtr = nullptr; 

public:
	RenderNotifier();

    void set_board(BacktrackBoard& board);
    void clear();
    BacktrackBoard& get_board_ref();
};


#endif
