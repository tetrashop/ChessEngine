#include "MoveGenerator.h"
#include "Board.h"
#include <bitset>
#include <algorithm>

namespace ChessEngine {

	// جدول از پیش محاسبه‌شده برای حرکت اسب
	constexpr Bitboard knightAttacks[64] = { /* ... */ };

	// جدول از پیش محاسبه‌شده برای حرکت شاه
	constexpr Bitboard kingAttacks[64] = { /* ... */ };

	std::vector<Move> MoveGenerator::generateLegalMoves(const Board& board) {
		std::vector<Move> moves = generatePseudoLegalMoves(board);

		// حذف حرکاتی که شاه را در معرض کیش قرار می‌دهند
		auto it = std::remove_if(moves.begin(), moves.end(),
			[&](const Move& move) { return !isMoveLegal(board, move); });
		moves.erase(it, moves.end());

		return moves;
	}

	std::vector<Move> MoveGenerator::generatePseudoLegalMoves(const Board& board) {
		std::vector<Move> moves;
		Color color = board.getTurn();

		generatePawnMoves(board, moves, color);
		generateKnightMoves(board, moves, color);
		generateBishopMoves(board, moves, color);
		generateRookMoves(board, moves, color);
		generateQueenMoves(board, moves, color);
		generateKingMoves(board, moves, color);

		generateCastlingMoves(board, moves, color);
		generateEnPassantMoves(board, moves, color);

		return moves;
	}

	// ##### تولید حرکات پیاده #####
	void MoveGenerator::generatePawnMoves(const Board& board, std::vector<Move>& moves, Color color) {
		Bitboard pawns = board.getPieces(PieceType::Pawn, color);
		Bitboard enemies = board.getColorPieces(~color);
		Bitboard empty = ~board.getAllPieces();
		int pushDir = (color == Color::White) ? 8 : -8;

		while (pawns) {
			Square sq = popLsb(pawns);
			Square forward = sq + pushDir;

			// حرکت به جلو
			if (board.getPiece(forward) == Piece::None) {
				addPawnMove(moves, sq, forward, color, board);

				// حرکت دوگانه (فقط در ردیف شروع)
				if ((color == Color::White && rankOf(sq) == 1) ||
					(color == Color::Black && rankOf(sq) == 6)) {
					Square doublePush = forward + pushDir;
					if (board.getPiece(doublePush) == Piece::None) {
						moves.emplace_back(sq, doublePush, Piece::None, MoveType::DoublePawnPush);
					}
				}
			}

			// حملات
			Bitboard attacks = board.getPawnAttacks(sq, color) & enemies;
			while (attacks) {
				Square target = popLsb(attacks);
				addPawnMove(moves, sq, target, color, board);
			}
		}
	}

	// ##### تولید حرکات اسب #####
	void MoveGenerator::generateKnightMoves(const Board& board, std::vector<Move>& moves, Color color) {
		Bitboard knights = board.getPieces(PieceType::Knight, color);
		Bitboard targets = ~board.getColorPieces(color); // فقط خانه‌های خالی یا حریف

		while (knights) {
			Square sq = popLsb(knights);
			Bitboard attacks = knightAttacks[sq] & targets;
			addMoves(moves, sq, attacks, board);
		}
	}

	// ##### تولید حرکات فیل #####
	void MoveGenerator::generateBishopMoves(...) { /* منطق مشابه با پر کردن خطوط */ }

	// ##### تولید حرکات رخ #####
	void MoveGenerator::generateRookMoves(...) { /* منطق پر کردن خطوط مستقیم */ }

	// ##### تولید حرکات وزیر #####
	void MoveGenerator::generateQueenMoves(...) { /* ترکیب فیل و رخ */ }

	// ##### تولید حرکات شاه #####
	void MoveGenerator::generateKingMoves(...) {
		// حرکت عادی + قلعه (با بررسی حقوق قلعه)
	}

	// ##### حرکات خاص: قلعه #####
	void MoveGenerator::generateCastlingMoves(...) {
		if (!board.canCastle(color)) return;

		// بررسی مسیر خالی و عدم حمله به خانه‌های مسیر
		// اضافه کردن حرکت قلعه به لیست
	}

	// ##### حرکات خاص: En Passant #####
	void MoveGenerator::generateEnPassantMoves(...) {
		Square epSquare = board.getEnPassantSquare();
		if (epSquare == Square::None) return;

		// بررسی وجود پیاده قابل انجام En Passant
	}

	// ##### بررسی قانونی بودن حرکت #####
	bool MoveGenerator::isMoveLegal(const Board& board, const Move& move) {
		Board tempBoard = board;
		tempBoard.makeMove(move);
		return !tempBoard.isKingInCheck(board.getTurn());
	}

	// ##### توابع کمکی #####
	void MoveGenerator::addMoves(std::vector<Move>& moves, Square from, Bitboard targets, const Board& board) {
		while (targets) {
			Square to = popLsb(targets);
			Piece captured = board.getPiece(to);
			moves.emplace_back(from, to, captured);
		}
	}

	void MoveGenerator::addPawnMove(...) {
		// بررسی ارتقا
		if ((color == Color::White && rankOf(to) == 7) ||
			(color == Color::Black && rankOf(to) == 0)) {
			generatePromotions(move, moves);
		}
		else {
			moves.emplace_back(...);
		}
	}

	void MoveGenerator::generatePromotions(...) {
		moves.emplace_back(..., Piece::Queen);
		moves.emplace_back(..., Piece::Rook);
		moves.emplace_back(..., Piece::Bishop);
		moves.emplace_back(..., Piece::Knight);
	}

} // namespace ChessEngine