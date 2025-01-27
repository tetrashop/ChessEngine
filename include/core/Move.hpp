#pragma once
#include "Piece.hpp"
#include <cstdint>

// نمایش مربع‌های صفحه با مختصات 0-63 (از a1=0 تا h8=63)
using Square = uint8_t;

// پرچم‌های حرکت خاص
enum MoveFlag {
	None = 0,
	Capture = 1 << 0,
	DoublePush = 1 << 1,
	EnPassant = 1 << 2,
	Castling = 1 << 3,
	Promotion = 1 << 4
};

struct Move {
	Square from;          // مبدأ حرکت
	Square to;            // مقصد حرکت
	Piece piece;          // مهره حرکت دهنده
	Piece capturedPiece;  // مهره حریف (در صورت Capture)
	int flags = MoveFlag::None; // پرچم‌های حرکت

	// برای حرکات Promotion
	PieceType promotionType = PieceType::None;

	// تبدیل حرکت به رشته UCI (مثال: "e2e4" یا "a7a8q")
	std::string toUCI() const {
		std::string uci;
		uci += static_cast<char>('a' + (from % 8));
		uci += static_cast<char>('1' + (from / 8));
		uci += static_cast<char>('a' + (to % 8));
		uci += static_cast<char>('1' + (to / 8));
		if (promotionType != PieceType::None) {
			uci += "qnrkbQNRKB"[static_cast<int>(promotionType)];
		}
		return uci;
	}
};