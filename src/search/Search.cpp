// src/search/Search.cpp
#include "Search.h"
#include "../utils/MoveGenerator.h"

Search::Search(Board& board, Evaluator& evaluator)
	: currentBoard(board), evaluator(evaluator) {}

SearchResult Search::startSearch(int depth) {
	SearchResult result;
	result.nodesVisited = 0;

	int alpha = -INFINITY;
	int beta = INFINITY;

	Move bestMove = MOVE_NONE;
	int bestValue = -INFINITY;

	MoveGenerator generator(currentBoard);
	auto moves = generator.generateLegalMoves();

	for (const auto& move : moves) {
		currentBoard.makeMove(move);
		int currentValue = alphaBeta(currentBoard, depth - 1, alpha, beta, false);
		currentBoard.unmakeMove(move);

		if (currentValue > bestValue) {
			bestValue = currentValue;
			bestMove = move;
		}

		alpha = std::max(alpha, bestValue);
	}

	result.bestMove = bestMove;
	result.score = bestValue;
	return result;
}

int Search::alphaBeta(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) {
	if (depth == 0 || board.isGameOver()) {
		return evaluator.evaluate(board);
	}

	MoveGenerator generator(board);
	auto moves = generator.generateLegalMoves();

	if (maximizingPlayer) {
		int value = -INFINITY;
		for (const auto& move : moves) {
			board.makeMove(move);
			value = std::max(value, alphaBeta(board, depth - 1, alpha, beta, false));
			board.unmakeMove(move);

			alpha = std::max(alpha, value);
			if (value >= beta)
				break; // Beta cutoff
		}
		return value;
	}
	else {
		int value = INFINITY;
		for (const auto& move : moves) {
			board.makeMove(move);
			value = std::min(value, alphaBeta(board, depth - 1, alpha, beta, true));
			board.unmakeMove(move);

			beta = std::min(beta, value);
			if (value <= alpha)
				break; // Alpha cutoff
		}
		return value;
	}
}
// فعالسازی جستجوی موازی ساده (۲ thread)
void Search::startParallelSearch(int depth) {
	std::vector<std::thread> threads;
	for (int i = 0; i < 2; i++) {
		threads.emplace_back([this, depth]() {
			alphaBeta(currentBoard, depth, -INFINITY, INFINITY, true);
		});
	}
	for (auto& t : threads) t.join();
}
// مثال ساده از Minimax با هرس آلفا-بتا

	// Search.cpp
int Search::AlphaBeta(Board& board, int depth, int alpha, int beta, bool maximizingPlayer) {
	if (depth == 0 || board.IsGameOver()) {
		return evaluator.Evaluate(board);
	}

	auto moves = board.GenerateMoves();
	if (maximizingPlayer) {
		int value = -INFINITY;
		for (Move move : moves) {
			board.MakeMove(move);
			value = std::max(value, AlphaBeta(board, depth - 1, alpha, beta, false));
			board.UndoMove(move);
			alpha = std::max(alpha, value);
			if (alpha >= beta) break; // Beta cutoff
		}
		return value;
	}
	else {
		int value = INFINITY;
		for (Move move : moves) {
			board.MakeMove(move);
			value = std::min(value, AlphaBeta(board, depth - 1, alpha, beta, true));
			board.UndoMove(move);
			beta = std::min(beta, value);
			if (beta <= alpha) break; // Alpha cutoff
		}
		return value;
	}
	int Search::Quiescence(Board& board, int alpha, int beta) {
		int standPat = evaluator.Evaluate(board);
		if (standPat >= beta) return beta;
		if (standPat > alpha) alpha = standPat;

		auto captures = moveGenerator.GenerateCaptures(board);
		for (const auto& move : captures) {
			board.MakeMove(move);
			int score = -Quiescence(board, -beta, -alpha);
			board.UndoMove(move);
			if (score >= beta) return beta;
			if (score > alpha) alpha = score;
		}
		return alpha;
	}

	int Search::AlphaBeta(Board& board, int depth, int alpha, int beta, bool isQuiescence) {
		if (depth == 0) return Quiescence(board, alpha, beta); // فراخوانی Quiescence
		// ... ادامه کد AlphaBeta
	}
	// مرتب‌سازی حرکات بر اساس:
// 1. حرکات کیش
// 2. حرکات با ارزش بالاتر (مثلاً Capture/ Promotion)
	void Search::OrderMoves(std::vector<Move>& moves, const Board& board) {
		std::sort(moves.begin(), moves.end(), [&](const Move& a, const Move& b) {
			return evaluator.EvaluateMove(a, board) > evaluator.EvaluateMove(b, board);
		});
	}
	Move Search::FindBestMove(Board& board, int maxDepth) {
		Move bestMove;
		for (int depth = 1; depth <= maxDepth; depth++) {
			int score = AlphaBeta(board, depth, -INFINITY, INFINITY);
			// به‌روزرسانی بهترین حرکت بر اساس عمق جستجو
		}
		return bestMove;
	}
	// در Search.cpp
	int alphaBeta(...) {
		TTEntry* entry = tt.probe(zobristKey);
		if (entry->depth >= depth) return entry->score;
		// ...
	}

}
// در Search.cpp  
SearchResult minimax(Board board, int depth) {
	if (depth == 0) {
		return { Move(), board.evaluate() };
	}
	auto moves = board.generate_all_moves();
	if (moves.empty()) return { Move(), -9999 }; // مات  

	SearchResult best = { moves[0], -99999 };
	for (const auto& move : moves) {
		Board new_board = board;
		new_board.apply_move(move);
		int score = -minimax(new_board, depth - 1).score;
		if (score > best.score) {
			best = { move, score };
		}
	}
	return best;
}