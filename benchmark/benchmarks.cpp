#include <benchmark/benchmark.h>

#include "../lib/examples/covid-19.hpp"
#include "../lib/examples/mutli_threading.hpp"


using namespace StochasticSimulation;

static void BM_SomeFunction(benchmark::State& state) {
    // Perform setup here
    auto vessel = Examples::seihr(20000);

    for (auto _ : state) {
        // This code gets timed
        Examples::getPeakAverage(1500, vessel, 100);
    }
}

BENCHMARK(BM_SomeFunction);
BENCHMARK_MAIN();