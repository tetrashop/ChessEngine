﻿#ifndef CHESSENGINE_BOARD_H
#define CHESSENGINE_BOARD_H

#include <array>
#include <vector>
#include <string>
#include <cstdint>

namespace ChessEngine {
	// در Board.h  
#include <vector>  
#include <string>  

	

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
		std::vector<Move> generate_pawn_moves(int x, int y);
		std::array<std::array<Piece, 8>, 8> squares;
		std::vector<Move> generate_knight_moves(int x, int y);
		std::array<std::array<Piece, 8>, 8> squares;
		std::vector<Move> generate_pawn_moves(int x, int y);
		bool is_in_check(bool is_white); // بررسی کیش بودن رنگ خاص  
		bool is_move_legal(const Move& move); // بررسی قانونی بودن حرکت  
		std::array<std::array<Piece, 8>, 8> squares;
		bool is_white_turn = true; // نوبت بازیکن  
		void set_from_fen(const std::string& fen);
		std::vector<Move> generate_all_moves();
		bool is_in_check(bool is_white);
		bool is_move_legal(const Move& move);
		bool is_checkmate(bool is_white);

		void set_from_fen(const std::string& fen) {
			// پیادهسازی سادهی FEN Parser برای موقعیت شروع
			if (fen == "startpos") {
				// تنظیم مهرهها در موقعیت اولیه
				squares[0] = { /* رخ, اسب, فیل, وزیر, شاه, ... */ };
				// ...
			}
		}
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
		int from_x, from_y;
		int to_x, to_y;
		std::string to_string() const {
			char cols[] = { 'a','b','c','d','e','f','g','h' };
			return std::string(1, cols[from_y]) + std::to_string(8 - from_x) +
				std::string(1, cols[to_y]) + std::to_string(8 - to_x);
		}
	};

} // namespace ChessEngine

#endif // CHESSENGINE_BOARD_H