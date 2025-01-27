#include "core/Move.hpp"
#include <stdexcept>

// تبدیل رشته UCI (مثل "e2e4") به شیء Move
Move Move::fromUCI(const std::string& uci, const Board& board) {
	if (uci.length() < 4) throw std::invalid_argument("Invalid UCI move");

	Square from = (uci[1] - '1') * 8 + (uci[0] - 'a');
	Square to = (uci[3] - '1') * 8 + (uci[2] - 'a');

	Move move;
	move.from = from;
	move.to = to;
	move.piece = board.getPiece(from);

	// تشخیص Promotion
	if (uci.length() == 5) {
		char promoChar = tolower(uci[4]);
		move.promotionType = static_cast<PieceType>(
			" pnbrqk"[promoChar == 'q' ? 4 : (promoChar == 'r' ? 3 :
			(promoChar == 'b' ? 2 : (promoChar == 'n' ? 1 : 0)))]
			);
	}

	return move;
}