#include <benchmark/benchmark.h>

#include "../lib/examples/covid-19.hpp"
#include "../lib/examples/circadian_rythm.hpp"
#include "../lib/examples/exponential_decay.hpp"

#include "../lib/examples/multi_threading.hpp"


using namespace StochasticSimulation;

static void seihr_single_core(benchmark::State& state) {
    auto vessel = Examples::seihr(20000);

    for (const auto _ : state) {
        Examples::get_peak_average_serial(1500, vessel, 100);
    }
}


BENCHMARK(seihr_single_core);


static void seihr_multi_core(benchmark::State& state) {
    auto vessel = Examples::seihr(20000);
    for (const auto _ : state) {
        Examples::get_peak_average(1500, vessel, 100);
    }
}

BENCHMARK(seihr_multi_core);


static void circadian_rythm_single_core(benchmark::State& state) {
    auto vessel = Examples::circadian_rhythm();

    for (const auto _ : state) {
        Examples::get_peak_average_serial(1500, vessel, 100);
    }
}



BENCHMARK(circadian_rythm_single_core);


static void circadian_rythm_multi_core(benchmark::State& state) {
    auto vessel = Examples::circadian_rhythm();

    for (const auto _ : state) {
        Examples::get_peak_average(1500, vessel, 100);
    }
}

BENCHMARK(circadian_rythm_multi_core);


static void exponential_decay_single_core(benchmark::State& state) {
    auto vessel = Examples::exponential_decay(50, 0 ,50);

    for (const auto _ : state) {
        Examples::get_peak_average_serial(1500, vessel, 100);
    }

}

BENCHMARK(exponential_decay_single_core);


static void exponential_decay_multi_core(benchmark::State& state) {
    auto vessel = Examples::exponential_decay(50, 0, 50);

    for (const auto _ : state) {
        Examples::get_peak_average(1500, vessel, 100);
    }
}
BENCHMARK(exponential_decay_multi_core);



BENCHMARK_MAIN();