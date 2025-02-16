#pragma once
#include "../Core/Board.h"

namespace ChessEngine {

	class Evaluator {
	public:
		static int evaluate(const Board& board);

	private:
		// �ǘ�����? ���?��?
		static int materialScore(const Board& board);
		static int pawnStructureScore(const Board& board);
		static int mobilityScore(const Board& board);
		static int kingSafetyScore(const Board& board);
		static int positionalScore(const Board& board);

		// ����� ���� ����?�?
		static const std::array<std::array<int, 64>, 6> pieceSquareTables;
	};

} // namespace ChessEngine