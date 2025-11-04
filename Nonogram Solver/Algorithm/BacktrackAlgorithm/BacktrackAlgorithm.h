#ifndef BACKTRACKALGORITHM_H
#define BACKTRACKALGORITHM_H


#include <atomic>
#include <thread>
#include "Shared/SharedBacktractBoard.h"

class BacktrackAlgorithm {
private:
	SharedBacktrackBoard& sharedBacktrackBoard;
    std::atomic<bool> terminate{ false };

public:
    explicit BacktrackAlgorithm(SharedBacktrackBoard& sharedBacktrackBoard);

	void run();

	void recursiveSolve(int count, int max);

    PlacementCount countPlacements(
		const Line& line,
		const HintLine& hintLine
	);

    void request_stop();
};


#endif
