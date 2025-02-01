#pragma once  
#include <unordered_map>  
#include "ChessBoard.h"  

class TranspositionTable {
public:
	void Store(uint64_t key, int eval, int depth);
	bool Retrieve(uint64_t key, int& eval, int& depth);

private:
	std::unordered_map<uint64_t, std::pair<int, int>> table;
};