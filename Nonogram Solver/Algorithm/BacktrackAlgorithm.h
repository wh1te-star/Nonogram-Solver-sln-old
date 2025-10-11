#ifndef BACKTRACKALGORITHM_H
#define BACKTRACKALGORITHM_H


#include <atomic>
#include <thread>
#include "Board/BacktrackBoard/BacktrackBoard.h"

class BacktrackAlgorithm {
private:
	BacktrackBoard backtrackBoard;
    std::atomic<bool> should_terminate{ false };

public:
    explicit BacktrackAlgorithm(BacktrackBoard backtrackBoard);

	void run();

    void request_stop();
};


#endif
