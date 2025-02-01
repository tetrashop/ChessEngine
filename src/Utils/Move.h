#ifndef MOVE_H
#define MOVE_H

#include <string>

// موقعیت روی صفحه شطرنج (ردیف و ستون)
struct Position {
	int row;
	int col;
	Position(int r = -1, int c = -1) : row(r), col(c) {}
};

// انواع مهره‌های شطرنج
enum class PieceType {
	None,
	Pawn,
	Knight,
	Bishop,
	Rook,
	Queen,
	King
};

// پرچم‌های حرکت (قلعه، آنپاسان، ارتقاء و ...)
enum class MoveFlag {
	None,
	Castling,
	EnPassant,
	Promotion,
	Capture
};

class Move {
private:
	Position startPos;    // موقعیت شروع
	Position endPos;      // موقعیت پایان
	PieceType piece;      // نوع مهره حرکت‌دهنده
	PieceType capturedPiece; // مهره حذفشده (در صورت وجود)
	PieceType promotion;  // نوع مهره ارتقاء (برای پیاده)
	MoveFlag flag;        // پرچم حرکت خاص

public:
	// سازنده‌ها
	Move();
	Move(Position start, Position end, PieceType p, PieceType captured = PieceType::None, MoveFlag f = MoveFlag::None);
	Move(Position start, Position end, PieceType p, PieceType captured, PieceType promo, MoveFlag f);

	// متدهای دسترسی (getters)
	Position getStart() const;
	Position getEnd() const;
	PieceType getPiece() const;
	PieceType getCapturedPiece() const;
	PieceType getPromotion() const;
	MoveFlag getFlag() const;

	// بررسی معتبر بودن حرکت
	bool isValid() const;

	// بررسی نوع حرکت
	bool isCapture() const;
	bool isPromotion() const;
	bool isCastling() const;
	bool isEnPassant() const;

	// تبدیل به نماد استاندارد شطرنج (مثال: e2e4, e7e8q)
	std::string toString() const;

	// عملگرهای مقایسه
	bool operator==(const Move& other) const;
	bool operator!=(const Move& other) const;
};

#endif