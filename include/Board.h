#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <array>
#include <vector>
#include <string>
#include <cstdint>

namespace ChessEngine {

	// انواع مهره‌ها
	enum class Piece {
		None = 0,
		WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
		BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing
	};

	// رنگ بازیکن
	enum class Color { White, Black, None };

	// موقعیت مهره‌ها با استفاده از Bitboard (بهینه‌سازی)
	using Bitboard = uint64_t;

	// کلاس اصلی صفحه شطرنج
	class Board {
	public:
		Board();

		// تنظیم موقعیت اولیه
		void setToStartPosition();

		// تولید تمام حرکات مجاز
		std::vector<Move> generateLegalMoves() const;

		// اعمال یک حرکت روی صفحه
		void makeMove(const Move& move);

		// بازگرداندن آخرین حرکت
		void undoMove();

		// تبدیل به FEN (برای ذخیره موقعیت)
		std::string toFEN() const;

		// چاپ صفحه به صورت متن
		void print() const;

		// بررسی وضعیت بازی (مات، پات، تساوی)
		GameState getGameState() const;

	private:
		// داده‌های صفحه
		std::array<Piece, 64> m_squares;
		Color m_turn;
		bool m_castlingRights[4]; // [WhiteKingSide, WhiteQueenSide, BlackKingSide, BlackQueenSide]
		Square m_enPassantSquare;
		int m_halfMoveClock;
		int m_fullMoveNumber;

		// تاریخچه حرکات برای undo
		std::vector<MoveHistory> m_moveHistory;

		// توابع کمکی
		Bitboard getPawnAttacks(Square sq, Color color) const;
		Bitboard getKnightAttacks(Square sq) const;
		bool isSquareAttacked(Square sq, Color attackerColor) const;
	};

	// ساختار حرکت
	struct Move {
		Square from;
		Square to;
		Piece piece;
		Piece promotion; // برای ارتقاء پیاده
		MoveType type;   // عادی، En Passant، قلعه، ارتقاء
	};

} // namespace ChessEngine

#endif // CHESSENGINE_BOARD_H