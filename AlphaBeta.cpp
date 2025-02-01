// AlphaBeta.cpp
#include <vector>
#include <climits>

class AlphaBeta {
public:
	// ”«Œ «— »—«? ‰„«?‘ ?ò Õ—ò 
	struct Move {
		int score;
		// ”«?— Å«—«„ —Â«? „—»Êÿ »Â Õ—ò 
	};

	AlphaBeta() {} // Constructor

	//  «»⁄ «—“?«»? Ê÷⁄?  »«“? („ ‰«”» »« »«“? ‘„« »«?œ Å?«œÂù”«“? ‘Êœ)
	int evaluatePosition() {
		// „‰ÿﬁ «—“?«»?
		return 0;
	}

	// «·êÊ—? „ ¬·›«-» «
	int alphaBeta(int depth, int alpha, int beta, bool maximizingPlayer) {
		if (depth == 0 /* ?« ‘—ÿ Å«?«‰ »«“? */) {
			return evaluatePosition();
		}

		if (maximizingPlayer) {
			int maxEval = INT_MIN;
			for (auto& move : generatePossibleMoves()) {
				// «‰Ã«„ Õ—ò 
				int eval = alphaBeta(depth - 1, alpha, beta, false);
				maxEval = std::max(maxEval, eval);
				alpha = std::max(alpha, eval);
				// »«“ê—œ«‰œ‰ Õ—ò 
				if (beta <= alpha)
					break; // ﬁÿ⁄ ¬·›«-» «
			}
			return maxEval;
		}
		else {
			int minEval = INT_MAX;
			for (auto& move : generatePossibleMoves()) {
				// «‰Ã«„ Õ—ò 
				int eval = alphaBeta(depth - 1, alpha, beta, true);
				minEval = std::min(minEval, eval);
				beta = std::min(beta, eval);
				// »«“ê—œ«‰œ‰ Õ—ò 
				if (beta <= alpha)
					break; // ﬁÿ⁄ ¬·›«-» «
			}
			return minEval;
		}

	}

	//  Ê·?œ Õ—ò«  „„ò‰ (»«?œ „ ‰«”» »« »«“? ‘„« Å?«œÂù”«“? ‘Êœ)
	std::vector<Move> generatePossibleMoves() {
		std::vector<Move> moves;
		// „‰ÿﬁ  Ê·?œ Õ—ò« 
		return moves;
	}

	//  «»⁄ «’·? »—«? œ—?«›  »Â —?‰ Õ—ò 
	Move getBestMove(int depth) {
		Move bestMove;
		int bestValue = INT_MIN;
		for (auto& move : generatePossibleMoves()) {
			// «‰Ã«„ Õ—ò 
			int moveValue = alphaBeta(depth, INT_MIN, INT_MAX, false);
			// »«“ê—œ«‰œ‰ Õ—ò 

			if (moveValue > bestValue) {
				bestValue = moveValue;
				bestMove = move;
			}
		}
		return bestMove;
	}
};