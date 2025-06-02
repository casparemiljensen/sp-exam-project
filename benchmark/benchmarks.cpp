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


BENCHMARK(seihr_single_core);


static void seihr_multi_core(benchmark::State& state) {

    auto vessel = Examples::seihr(20000);

    Examples::getPeakAverage(1500, vessel, 100);
}

BENCHMARK(seihr_multi_core);


static void covid_19_single_core(benchmark::State& state) {

}

BENCHMARK(covid_19_single_core);


static void covid_19_multi_core(benchmark::State& state) {

}

BENCHMARK(covid_19_multi_core);


static void exponential_decay_single_core(benchmark::State& state) {

}

BENCHMARK(exponential_decay_single_core);


static void exponential_decay_multi_core(benchmark::State& state) {

}
BENCHMARK(exponential_decay_multi_core);



BENCHMARK_MAIN();