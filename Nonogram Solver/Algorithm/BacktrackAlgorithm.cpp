#include "Algorithm/BacktrackAlgorithm.h"

#include <atomic>
#include <thread>
#include <chrono>


BacktrackAlgorithm::BacktrackAlgorithm(BacktrackBoard backtrackBoard)
	: backtrackBoard(backtrackBoard) {}

void BacktrackAlgorithm::run() {
	int i = 0;
	while (!should_terminate) {
		printf("count: %d\n", i);
		std::this_thread::sleep_for(std::chrono::milliseconds(2500));
	}
}

void BacktrackAlgorithm::request_stop() {
	should_terminate = true;
}
