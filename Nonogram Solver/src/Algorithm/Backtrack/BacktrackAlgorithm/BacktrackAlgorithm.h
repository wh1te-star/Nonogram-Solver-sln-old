#ifndef BACKTRACKALGORITHM_H
#define BACKTRACKALGORITHM_H


#include <atomic>
#include <thread>
#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedBacktrackStack/SharedBacktrackStack.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"
#include "Board/Line/Line.h"
#include "Hint/HintSet/HintSet.h"

class BacktrackAlgorithm {
private:
	SharedBacktrackBoard& sharedBacktrackBoard;
	SharedBacktrackStack& sharedBacktrackStack;
	SharedHighlightIndexes& sharedHighlightIndexes;
    std::atomic<bool> terminate{ false };
	std::vector<Board> solutions;

public:
    explicit BacktrackAlgorithm(
		SharedBacktrackBoard& sharedBacktrackBoard,
		SharedBacktrackStack& sharedBacktrackStack,
		SharedHighlightIndexes& sharedHighlightIndexes
    );

	void run();

	void backtrackSolve();
	void backtrackSolveRecursive(int depth);

	bool deterministicSolve(int waitMillis);

    bool waitAndCheckTermination(const int waitMillis) const;
    void request_stop();
};


#endif
