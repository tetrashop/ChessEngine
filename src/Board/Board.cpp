#include "Board.h"
#include "MoveGenerator.h"
#include <iostream>
#include <sstream>

namespace ChessEngine {

	Board::Board() {
		setToStartPosition();
	}

	void Board::setToStartPosition() {
		// پاکسازی صفحه
		m_squares.fill(Piece::None);

		// تنطیم مهره‌های سفید
		m_squares[0] = Piece::WhiteRook;
		m_squares[1] = Piece::WhiteKnight;
		m_squares[2] = Piece::WhiteBishop;
		m_squares[3] = Piece::WhiteQueen;
		m_squares[4] = Piece::WhiteKing;
		m_squares[5] = Piece::WhiteBishop;
		m_squares[6] = Piece::WhiteKnight;
		m_squares[7] = Piece::WhiteRook;
		for (int i = 8; i < 16; i++) m_squares[i] = Piece::WhitePawn;

		// تنطیم مهره‌های سیاه
		m_squares[56] = Piece::BlackRook;
		m_squares[57] = Piece::BlackKnight;
		m_squares[58] = Piece::BlackBishop;
		m_squares[59] = Piece::BlackQueen;
		m_squares[60] = Piece::BlackKing;
		m_squares[61] = Piece::BlackBishop;
		m_squares[62] = Piece::BlackKnight;
		m_squares[63] = Piece::BlackRook;
		for (int i = 48; i < 56; i++) m_squares[i] = Piece::BlackPawn;

		// تنظیمات اولیه
		m_turn = Color::White;
		std::fill(m_castlingRights, m_castlingRights + 4, true);
		m_enPassantSquare = Square::None;
		m_halfMoveClock = 0;
		m_fullMoveNumber = 1;
	}

	std::vector<Move> Board::generateLegalMoves() const {
		return MoveGenerator::generateLegalMoves(*this);
	}

	void Board::makeMove(const Move& move) {
		// ذخیره تاریخچه برای undo
		MoveHistory history;
		history.move = move;
		history.castlingRights = { m_castlingRights[0], m_castlingRights[1], m_castlingRights[2], m_castlingRights[3] };
		history.enPassantSquare = m_enPassantSquare;
		history.halfMoveClock = m_halfMoveClock;
		m_moveHistory.push_back(history);

		// اعمال حرکت
		m_squares[move.to] = m_squares[move.from];
		m_squares[move.from] = Piece::None;

		// پردازش حرکات خاص
		if (move.type == MoveType::Castling) {
			// حرکت قلعه
			// ...
		}
		else if (move.type == MoveType::EnPassant) {
			// حذف پیاده حریف در En Passant
			// ...
		}
		else if (move.type == MoveType::Promotion) {
			// ارتقای پیاده
			m_squares[move.to] = move.promotion;
		}

		// به‌روزرسانی وضعیت
		m_turn = (m_turn == Color::White) ? Color::Black : Color::White;
	}

	void Board::undoMove() {
		if (m_moveHistory.empty()) return;

		const auto& history = m_moveHistory.back();
		const Move& move = history.move;

		// بازگرداندن حرکت
		m_squares[move.from] = m_squares[move.to];
		m_squares[move.to] = Piece::None;

		// بازگردانی وضعیت
		std::copy(history.castlingRights.begin(), history.castlingRights.end(), m_castlingRights);
		m_enPassantSquare = history.enPassantSquare;
		m_halfMoveClock = history.halfMoveClock;
		m_turn = (m_turn == Color::White) ? Color::Black : Color::White;

		m_moveHistory.pop_back();
	}

	std::string Board::toFEN() const {
		std::stringstream fen;
		int empty = 0;

		// موقعیت مهره‌ها
		for (int rank = 7; rank >= 0; rank--) {
			for (int file = 0; file < 8; file++) {
				int sq = rank * 8 + file;
				Piece piece = m_squares[sq];
				if (piece == Piece::None) {
					empty++;
				}
				else {
					if (empty > 0) fen << empty;
					empty = 0;
					fen << pieceToChar(piece);
				}
			}
			if (empty > 0) fen << empty;
			if (rank > 0) fen << '/';
			empty = 0;
		}

		// رنگ نوبت
		fen << (m_turn == Color::White ? " w " : " b ");

		// حقوق قلعه
		bool anyCastling = false;
		if (m_castlingRights[0]) { fen << 'K'; anyCastling = true; }
		if (m_castlingRights[1]) { fen << 'Q'; anyCastling = true; }
		if (m_castlingRights[2]) { fen << 'k'; anyCastling = true; }
		if (m_castlingRights[3]) { fen << 'q'; anyCastling = true; }
		if (!anyCastling) fen << '-';

		// En Passant
		fen << (m_enPassantSquare == Square::None ? " - " : " " + squareToString(m_enPassantSquare) + " ");

		// ساعت حرکت
		fen << m_halfMoveClock << " " << m_fullMoveNumber;

		return fen.str();
	}

	void Board::print() const {
		const std::string pieces = " PNBRQK  pnbrqk";
		for (int rank = 7; rank >= 0; rank--) {
			std::cout << rank + 1 << " ";
			for (int file = 0; file < 8; file++) {
				int sq = rank * 8 + file;
				std::cout << pieces[static_cast<int>(m_squares[sq])] << " ";
			}
			std::cout << "\n";
		}
		std::cout << "  a b c d e f g h\n";
	}

	// توابع کمکی
	Bitboard Board::getPawnAttacks(Square sq, Color color) const {
		// محاسبه حمله‌های پیاده با Bitboard
		// ...
	}

	Bitboard Board::getKnightAttacks(Square sq) const {
		// جدول از پیش محاسبه شده برای حرکت اسب
		static const Bitboard knightAttacks[64] = {/*...*/ };
		return knightAttacks[sq];
	}

	bool Board::isSquareAttacked(Square sq, Color attackerColor) const {
		// بررسی حمله توسط تمام مهره‌های حریف
		// ...
	}
	

// تکمیل پارسر FEN
	void Board::ResetToFEN(const std::string& fen) {
		// مثال FEN: "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
		std::istringstream iss(fen);
		std::string piecePlacement, activeColor, castling, enPassant, halfMove, fullMove;

		iss >> piecePlacement >> activeColor >> castling >> enPassant >> halfMove >> fullMove;

		// ریست تخته
		memset(bitboards, 0, sizeof(bitboards));

		int row = 7, col = 0;
		for (char c : piecePlacement) {
			if (c == '/') {
				row--;
				col = 0;
			}
			else if (isdigit(c)) {
				col += c - '0';
			}
			else {
				int piece = CharToPiece(c);
				SetBit(bitboards[piece], row * 8 + col);
				col++;
			}
		}

		isWhiteTurn = (activeColor == "w");
		// مدیریت وضعیت قلعه و آنپاسان (نیاز به پیاده‌سازی)
	}
	// MoveGenerator.cpp
	std::vector<Move> Board::GenerateKnightMoves(int square, Color color) {
		std::vector<Move> moves;
		uint64_t knightAttacks = precomputedKnightAttacks[square];
		uint64_t targetSquares = knightAttacks & ~GetColorBitboard(color);

		while (targetSquares) {
			int target = GetLSB(targetSquares);
			moves.push_back(CreateMove(square, target));
			targetSquares &= targetSquares - 1;
		}
		return moves;
	}
	// در Board.cpp  
	std::vector<Move> Board::generate_pawn_moves(int x, int y) {
		std::vector<Move> moves;
		Piece piece = squares[x][y];

		// حرکت سفیدها به جلو  
		if (piece == Piece::WhitePawn) {
			// حرکت ۱ خانه  
			if (x > 0 && squares[x - 1][y] == Piece::None) {
				moves.push_back({ x, y, x - 1, y });
				// حرکت ۲ خانه در اولین حرکت  
				if (x == 6 && squares[x - 2][y] == Piece::None) {
					moves.push_back({ x, y, x - 2, y });
				}
			}
			// ضربهی اریب (چپ)  
			if (x > 0 && y > 0 && squares[x - 1][y - 1] != Piece::None) {
				moves.push_back({ x, y, x - 1, y - 1 });
			}
			// ضربهی اریب (راست)  
			if (x > 0 && y < 7 && squares[x - 1][y + 1] != Piece::None) {
				moves.push_back({ x, y, x - 1, y + 1 });
			}
		}
		// حرکت سیاهها به جلو (مشابه با جهت معکوس)  
		return moves;
	}
	// در Board.cpp  
	std::vector<Move> Board::generate_knight_moves(int x, int y) {
		std::vector<Move> moves;
		Piece piece = squares[x][y];
		int directions[8][2] = {
			{-2, -1}, {-2, 1},
			{-1, -2}, {-1, 2},
			{1, -2},  {1, 2},
			{2, -1},  {2, 1}
		};

		for (auto& dir : directions) {
			int new_x = x + dir[0];
			int new_y = y + dir[1];
			if (new_x >= 0 && new_x < 8 && new_y >= 0 && new_y < 8) {
				Piece target = squares[new_x][new_y];
				if (target == Piece::None || (is_white(piece) != is_white(target))) {
					moves.push_back({ x, y, new_x, new_y });
				}
			}
		}
		return moves;
	}
} // namespace ChessEngine