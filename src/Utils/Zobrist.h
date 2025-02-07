#pragma once
#include <cstdint>

class Zobrist {
public:
	// در Zobrist.h
	extern uint64_t zobristKeys[12][64]; // 12 نوع مهره × 64 خانه
	static void init();
	static uint64_t computeHash(const ChessBoard& board);

private:
	static uint64_t zobristTable[8][8][12]; // 12 = 6 مهره * 2 رنگ

	uint64_t keys[8][8][12]; // [x][y][piece]
	uint64_t turnKey;
public:
	Zobrist() { /* مقداردهی تصادفی */ }
	uint64_t computeHash(const ChessBoard& board) const;
	uint64_t computeZobristHash(const ChessBoard& board) {
		uint64_t hash = 0;
		for (const auto&[pos, piece] : board.pieces) {
			int pieceIndex = static_cast<int>(piece.type) + 6 * static_cast<int>(piece.color);
			hash ^= zobristTable[pos.x][pos.y][pieceIndex];
		}
		return hash;
	}

};