// TranspositionTable.h
#pragma once
#include <unordered_map>
#include "Board.h"

struct TTEntry {
	int depth;
	int score;
	// سایر اطلاعات: نوع گره (EXACT, LOWER_BOUND, UPPER_BOUND)
};

class TranspositionTable {
private:
	std::unordered_map<uint64_t, TTEntry> table; // کلید: hash موقعیت
public:
	void Store(uint64_t hash, TTEntry entry) { table[hash] = entry; }
	TTEntry* Probe(uint64_t hash) { return table.count(hash) ? &table[hash] : nullptr; }
};