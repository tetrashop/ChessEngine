#include <future>

int Search::parallelSearch(const Position& pos, int depth) {
	auto fut1 = std::async(std::launch::async, &Search::alphaBeta, this, pos, depth / 2, ...);
	auto fut2 = std::async(std::launch::async, &Search::alphaBeta, this, pos, depth / 2, ...);
	return std::max(fut1.get(), fut2.get());
}