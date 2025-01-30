#pragma once
#include "ChessBoard.h"

class Evaluator {
public:
	static int evaluate(const ChessBoard& board, Color color);

private:
	static int materialScore(const ChessBoard& board, Color color);
	static int pawnStructureScore(const ChessBoard& board, Color color);
	static int kingSafetyScore(const ChessBoard& board, Color color);
int Evaluator::pawnStructureScore(const ChessBoard& board, Color color) {
    int score = 0;
    // پیاده‌های ایزوله (بدون پیاده همسایه)
    for (int x = 0; x < 8; x++) {
        bool isolated = true;
        if (x > 0 && board.hasPawnInColumn(x - 1, color)) isolated = false;
        if (x < 7 && board.hasPawnInColumn(x + 1, color)) isolated = false;
        if (isolated) score -= 15;
    }
    // پیاده‌های مضاعف (دو پیاده در یک ستون)
    for (int x = 0; x < 8; x++) {
        if (board.countPawnsInColumn(x, color) > 1) score -= 10;
    }
    return score;
}
int Evaluator::bishopMobility(const ChessBoard& board, Color color) {
    int mobility = 0;
    uint64_t bishops = board.getBitboard(PieceType::Bishop, color);
    while (bishops) {
        int square = bitScanForward(bishops);
        mobility += popCount(Bitboard::bishopAttacks(1ULL << square, board.getOccupied()));
        bishops &= bishops - 1;
    }
    return mobility * 5; // ضریب پویایی
}
int Evaluator::kingSafety(const ChessBoard& board, Color color) {
    int safety = 0;
    Position kingPos = board.findKing(color);
    // تعداد مهره‌های حریف در اطراف شاه
    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            Position p = {kingPos.x + dx, kingPos.y + dy};
            if (board.isEnemy(p, color)) safety -= 10;
        }
    }
    // تعداد پیاده‌های دفاعی
    safety += popCount(board.getPawnShield(color)) * 5;
    return safety;
}

};
