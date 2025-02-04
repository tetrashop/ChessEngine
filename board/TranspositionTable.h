class TranspositionTable {
private:
	struct Entry {
		uint64_t hash;
		int score;
	};
	std::unique_ptr<Entry[]> entries; // جایگزین Entry* entries  
	size_t size;

public:
	TranspositionTable(size_t size) : entries(std::make_unique<Entry[]>(size)), size(size) {}

	void addEntry(uint64_t hash, int score) {
		entries[hash % size] = { hash, score };
	}
};