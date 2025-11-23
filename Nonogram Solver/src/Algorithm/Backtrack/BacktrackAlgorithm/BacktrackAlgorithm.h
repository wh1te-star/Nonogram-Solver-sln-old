#ifndef BACKTRACKALGORITHM_H
#define BACKTRACKALGORITHM_H


#include <atomic>
#include <thread>
#include "Shared/SharedBacktrackBoard/SharedBacktrackBoard.h"
#include "Shared/SharedHighlightIndexes/SharedHighlightIndexes.h"
#include "Algorithm/Backtrack/BacktrackState/BacktrackState.h"
#include "Board/Line/Line.h"
#include "Hint/HintSet/HintSet.h"

class BacktrackAlgorithm {
private:
	SharedBacktrackBoard& sharedBacktrackBoard;
	SharedHighlightIndexes& sharedHighlightIndexes;
    std::atomic<bool> terminate{ false };

public:
    explicit BacktrackAlgorithm(
		SharedBacktrackBoard& sharedBacktrackBoard,
		SharedHighlightIndexes& sharedHighlightIndexes
    );

	void run();

	void backtrackSolve();
	void backtrackSolveRecursive(BacktrackState backtrackState);

	void deterministicSolve();

    bool waitAndCheckTermination(const int waitMillis) const;
    void request_stop();
};


#endif
