// UnitTests.cpp
void TestFENParser() {
	Board board;
	board.ResetToFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	assert(board.GetPieceCount(WHITE_KNIGHT) == 2);
	assert(board.GetPieceCount(BLACK_PAWN) == 8);
}
void TestKnightMoves() {
	Board board;
	board.ResetToFEN("8/8/8/4n3/8/8/8/8 b - - 0 1"); // اسب سیاه در e5
	auto moves = board.GenerateMoves();
	assert(moves.size() == 8); // اسب باید ۸ حرکت ممکن داشته باشد
}