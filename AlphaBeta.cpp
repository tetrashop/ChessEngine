// AlphaBeta.cpp
#include <vector>
#include <climits>

class AlphaBeta {
public:
	// ������ ���? ���?� ?� �ј�
	struct Move {
		int score;
		// ��?� ���������? ����� �� �ј�
	};

	AlphaBeta() {} // Constructor

	// ���� ���?��? ���?� ���? (������ �� ���? ��� ��?� �?������? ���)
	int evaluatePosition() {
		// ���� ���?��?
		return 0;
	}

	// ����?�� ����-���
	int alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer) {
		if (depth == 0 /* ?� ��� ��?�� ���? */) {
			return evaluatePosition();
		}

		if (maximizingPlayer) {
			int maxEval = INT_MIN;
			for (auto& move : generatePossibleMoves()) {
				// ����� �ј�
				int eval = alphaBeta(depth - 1, alpha, beta, false);
				maxEval = std::max(maxEval, eval);
				alpha = std::max(alpha, eval);
				// ��Ґ������ �ј�
				if (beta <= alpha)
					break; // ��� ����-���
			}
			return maxEval;
		}
		else {
			int minEval = INT_MAX;
			for (auto& move : generatePossibleMoves()) {
				// ����� �ј�
				int eval = alphaBeta(depth - 1, alpha, beta, true);
				minEval = std::min(minEval, eval);
				beta = std::min(beta, eval);
				// ��Ґ������ �ј�
				if (beta <= alpha)
					break; // ��� ����-���
			}
			return minEval;
		}

	}

	// ���?� �ј�� ��� (��?� ������ �� ���? ��� �?������? ���)
	std::vector<Move> generatePossibleMoves() {
		std::vector<Move> moves;
		// ���� ���?� �ј��
		return moves;
	}

	// ���� ���? ���? ��?��� ����?� �ј�
	Move getBestMove(int depth) {
		Move bestMove;
		int bestValue = INT_MIN;
		for (auto& move : generatePossibleMoves()) {
			// ����� �ј�
			int moveValue = alphaBeta(depth, INT_MIN, INT_MAX, false);
			// ��Ґ������ �ј�

			if (moveValue > bestValue) {
				bestValue = moveValue;
				bestMove = move;
			}
		}
		return bestMove;
	}
};