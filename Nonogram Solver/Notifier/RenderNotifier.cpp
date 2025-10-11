#include "Notifier/RenderNotifier.h"

#include <atomic>
#include <thread>
#include <chrono>


RenderNotifier::RenderNotifier(){}

void RenderNotifier::set_board(BacktrackBoard& board) {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackBoardPtr = &board;
}

void RenderNotifier::clear() {
	std::lock_guard<std::mutex> lock(mtx);
	backtrackBoardPtr = nullptr;
}

BacktrackBoard& RenderNotifier::get_board_ref() {
	std::lock_guard<std::mutex> lock(mtx);
	
	return *backtrackBoardPtr; 
}
