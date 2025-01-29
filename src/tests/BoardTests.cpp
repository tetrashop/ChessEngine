#include "gtest/gtest.h"
#include "Board.h"
#include "MoveGenerator.h"

using namespace ChessEngine;

TEST(BoardTest, InitialPosition) {
	Board board;
	board.setToStartPosition();

	// بررسی تعداد مهره‌ها در موقعیت شروع
	EXPECT_EQ(board.getPieceCount(Piece::WhitePawn), 8);
	EXPECT_EQ(board.getPieceCount(Piece::BlackKnight), 2);
	EXPECT_EQ(board.getTurn(), Color::White);
}

TEST(BoardTest, BasicPawnMove) {
	Board board;
	board.setToStartPosition();

	// حرکت پیاده سفید از e2 به e4
	Move move = { Square::E2, Square::E4, Piece::WhitePawn };
	board.makeMove(move);

	EXPECT_EQ(board.getPiece(Square::E4), Piece::WhitePawn);
	EXPECT_EQ(board.getPiece(Square::E2), Piece::None);
	EXPECT_EQ(board.getTurn(), Color::Black);
}

TEST(BoardTest, EnPassant) {
	Board board;
	// تنظیم موقعیت En Passant
	board.loadFEN("8/8/8/3pP3/8/8/8/8 w - d6 0 1");

	auto moves = board.generateLegalMoves();
	bool foundEnPassant = false;
	for (const auto& move : moves) {
		if (move.type == MoveType::EnPassant) {
			foundEnPassant = true;
			break;
		}
	}
	EXPECT_TRUE(foundEnPassant);
}

TEST(BoardTest, CastlingRights) {
	Board board;
	board.loadFEN("r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");

	// بررسی حقوق قلعه اولیه
	EXPECT_TRUE(board.canCastle(Color::White, CastleSide::KingSide));
	EXPECT_TRUE(board.canCastle(Color::Black, CastleSide::QueenSide));

	// حرکت رخ شاه‌پهلو سفید
	Move rookMove = { Square::A1, Square::A2, Piece::WhiteRook };
	board.makeMove(rookMove);
	EXPECT_FALSE(board.canCastle(Color::White, CastleSide::QueenSide));
}

TEST(BoardTest, FENConversion) {
	Board board;
	std::string fen = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";
	board.loadFEN(fen);

	// بررسی صحت تبدیل FEN به موقعیت
	EXPECT_EQ(board.getPiece(Square::C5), Piece::BlackPawn);
	EXPECT_EQ(board.getPiece(Square::E4), Piece::WhitePawn);
	EXPECT_EQ(board.getTurn(), Color::Black);
	EXPECT_EQ(board.toFEN(), fen);
}

TEST(BoardTest, CheckDetection) {
	Board board;
	board.loadFEN("4k3/8/8/8/8/8/8/R3K3 w Q - 0 1");

	// حرکت رخ به a8 (کیش)
	Move move = { Square::A1, Square::A8, Piece::WhiteRook };
	board.makeMove(move);
	EXPECT_TRUE(board.isKingInCheck(Color::Black));
}

TEST(BoardTest, UndoMove) {
	Board board;
	board.setToStartPosition();

	Move move = { Square::E2, Square::E4, Piece::WhitePawn };
	board.makeMove(move);
	board.undoMove();

	EXPECT_EQ(board.getPiece(Square::E4), Piece::None);
	EXPECT_EQ(board.getPiece(Square::E2), Piece::WhitePawn);
	EXPECT_EQ(board.getTurn(), Color::White);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}