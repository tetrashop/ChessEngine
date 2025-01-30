// در فایل MoveGeneratorTests.cpp
#include "MoveGenerator.hpp"
#include "Board.hpp"
#include <gtest/gtest.h>

TEST(MoveGeneratorTest, PawnAttacks) {
	Board board;
	board.pawns[0] = 0x000000000000FF00; // پیادههای سفید در ردیف دوم
	board.turn = 0;
	auto moves = MoveGenerator::generateLegalMoves(board);
	ASSERT_EQ(moves.size(), 16); // 8 حرکت مستقیم + 8 حمله
}