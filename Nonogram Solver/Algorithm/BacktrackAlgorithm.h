#ifndef BACKTRACKALGORITHM_H
#define BACKTRACKALGORITHM_H


#include <atomic>
#include <thread>
#include "Shared/SharedBacktractBoard.h"

class BacktrackAlgorithm {
private:
	SharedBacktrackBoard& sharedBacktrackBoard;
    std::atomic<bool> should_terminate{ false };

public:
    explicit BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard);

	void run();

    void request_stop();
};


#endif
