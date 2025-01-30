// در فایل Evaluator.cpp
int Evaluator::pieceActivity(const ChessBoard& board, Color color) {
    int activity = 0;
    // فعالیت اسب: تعداد خانه‌های قابل دسترسی
    uint64_t knights = board.getBitboard(PieceType::Knight, color);
    while (knights) {
        int square = bitScanForward(knights);
        activity += popCount(Bitboard::knightAttacks(1ULL << square));
        knights &= knights - 1;
    }
    // فعالیت فیل: تعداد خانه‌های مورب کنترل‌شده
    uint64_t bishops = board.getBitboard(PieceType::Bishop, color);
    while (bishops) {
        int square = bitScanForward(bishops);
        activity += popCount(Bitboard::bishopAttacks(1ULL << square, board.getOccupied()));
        bishops &= bishops - 1;
    }
    return activity;
}
// Evaluator.cpp
int Evaluator::Evaluate(const Board& board) {
	int score = 0;
	// امتیاز مواد (Material Score)
	score += GetMaterialScore(board);
	// امتیاز موقعیت (Piece-Square Tables)
	score += GetPositionalScore(board);
	// ایمنی شاه (King Safety)
	score += EvaluateKingSafety(board);
	return score;
}