#include <benchmark/benchmark.h>

static void BM_AlphaBeta(benchmark::State& state) {
	Position pos;
	pos.setToStartPosition();
	for (auto _ : state) {
		alphaBeta(pos, state.range(0), -INFINITY, INFINITY);
	}
}
BENCHMARK(BM_AlphaBeta)->Arg(4)->Arg(6);
