#pragma once
#include "ChessBoard.h"

class Search {
public:
	static Move findBestMove(ChessBoard& board, int depth);

private:
	static int alphaBeta(ChessBoard& board, int depth, int alpha, int beta, bool maximizingPlayer);
	int alphaBeta(ChessBoard& board, int depth, int alpha, int beta, bool maximizingPlayer) {
		if (depth == 0 || board.isGameOver()) {
			return board.evaluatePosition() + (maximizingPlayer ? depth : -depth); // Encourages faster checkmates
		}

		auto moves = board.getAllMoves(maximizingPlayer ? Color::White : Color::Black);
		sortMoves(moves, board); // حرکتهای امیدوارکننده را اول بررسی کن

		if (maximizingPlayer) {
			int maxEval = INT_MIN;
			for (const auto& move : moves) {
				board.makeMove(move.from, move.to);
				int eval = alphaBeta(board, depth - 1, alpha, beta, false);
				board.undoMove();

				maxEval = max(maxEval, eval);
				alpha = max(alpha, eval);
				if (beta <= alpha) break;
			}
			return maxEval;
		}
		else {
			// پیادهسازی مشابه برای مینیمایزر
		}
	}

	void sortMoves(vector<Move>& moves, const ChessBoard& board) {
		// اولویت‌دهی حرکات بر اساس:
		// 1. حرکات کیش
		// 2. زدن مهره‌های ارزشمند
		// 3. تاریخچه حرکات (Heuristic)
		for (auto& move : moves) {
			move.score = 0;
			Piece captured = board.getPiece(move.to);
			if (captured.type != PieceType::None) {
				move.score += 10 * getPieceValue(captured.type); // امتیاز برای زدن مهره
			}
			if (board.moveCausesCheck(move)) {
				move.score += 50; // امتیاز برای حرکات کیش
			}
		}
		sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
			return a.score > b.score;
		});
	}

	Move findBestMove(ChessBoard& board, int maxDepth) {
		Move bestMove;
		for (int depth = 1; depth <= maxDepth; ++depth) {
			int currentEval = alphaBeta(board, depth, INT_MIN, INT_MAX, true);
			// ذخیره بهترین حرکت در هر عمق
			bestMove = currentBestMove;
		}
		return bestMove;
	}

#include <thread>
#include <mutex>

	mutex mtx;
	Move globalBestMove;

	void parallelSearch(ChessBoard board, int depth, int alpha, int beta, bool maximizing) {
		int eval = alphaBeta(board, depth, alpha, beta, maximizing);
		lock_guard<mutex> guard(mtx);
		if (eval > globalBestMove.score) {
			globalBestMove = currentBestMove;
		}
	}

	Move threadedSearch(ChessBoard board, int depth) {
		vector<thread> threads;
		auto moves = board.getAllMoves(board.getCurrentTurn());

		for (auto& move : moves) {
			ChessBoard newBoard = board;
			newBoard.makeMove(move);
			threads.emplace_back(parallelSearch, newBoard, depth - 1, INT_MIN, INT_MAX, false);
		}

		for (auto& t : threads) t.join();
		return globalBestMove;
	}

};
