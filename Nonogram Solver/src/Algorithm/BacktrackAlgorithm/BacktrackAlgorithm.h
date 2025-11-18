#ifndef BACKTRACKALGORITHM_H
#define BACKTRACKALGORITHM_H


#include <atomic>
#include <thread>
#include "Shared/SharedBacktractBoard.h"
#include "Board/Line/Line.h"
#include "Hint/HintLine/HintLine.h"

class BacktrackAlgorithm {
private:
	SharedBacktrackBoard& sharedBacktrackBoard;
    std::atomic<bool> terminate{ false };

public:
    explicit BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard);

	void run();

	void recursiveSolve(int count, int max);
    void request_stop();
};


#endif
