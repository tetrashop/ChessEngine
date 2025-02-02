#pragma once  
#include <unordered_map>  
#include "ChessBoard.h"  

class TranspositionTable {
public:
	void Store(uint64_t key, int eval, int depth);
	bool Retrieve(uint64_t key, int& eval, int& depth);

private:
	std::unordered_map<uint64_t, std::pair<int, int>> table;
	std::unordered_map<uint64_t, TranspositionTableEntry> table;
public:
	void store(uint64_t key, int depth, int score, int flag) {
		table[key] = { depth, score, flag };
	}
	TranspositionTableEntry* probe(uint64_t key) {
		auto it = table.find(key);
		return it != table.end() ? &it->second : nullptr;
	}
};
