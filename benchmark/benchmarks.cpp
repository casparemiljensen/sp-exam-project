#include <benchmark/benchmark.h>

#include "debug_print.hpp"
#include "../lib/examples/covid-19.hpp"
#include "../lib/examples/circadian_rythm.hpp"
#include "../lib/examples/exponential_decay.hpp"

#include "../lib/examples/multi_threading.hpp"


using namespace StochasticSimulation;

static void seihr_single_core(benchmark::State& state) {
    auto vessel = Examples::seihr(20000);

    //debug_print("\nStarting single core seihr");
    for (const auto _ : state) {
        Examples::get_peak_average_serial(1500, vessel, 100, "H");
    }
    debug_print("End single core seihr");
}


BENCHMARK(seihr_single_core)->Unit(benchmark::kMillisecond);


static void seihr_multi_core(benchmark::State& state) {
    auto vessel = Examples::seihr(20000);

    debug_print("\nStarting multi-core seihr");
    for (const auto _ : state) {
        Examples::get_peak_average(1500, vessel, 100, "H");
    }
    debug_print("End multi-core seihr");
}

BENCHMARK(seihr_multi_core)->Unit(benchmark::kMillisecond);


static void circadian_rythm_single_core_10_runs(benchmark::State& state) {
    auto vessel = Examples::circadian_rhythm();

    debug_print("\nStarting circadian_rythm_single_core_10_runs");
    for (const auto _ : state) {
        Examples::get_peak_average_serial(1500, vessel, 10, "DA"); // This finds peak average of H - H does not exist in all examples
    }
    debug_print("End circadian_rythm_single_core_10_runs");
}

BENCHMARK(circadian_rythm_single_core_10_runs)->Unit(benchmark::kMillisecond);

static void circadian_rythm_single_core_10_runs_optimized(benchmark::State& state) {
    auto vessel = Examples::circadian_rhythm();

    debug_print("\nStarting circadian_rythm_single_core_10_runs_optimized");
    for (const auto _ : state) {
        Examples::get_peak_average_serial_optimized(1500, vessel, 10, "DA"); // This finds peak average of H - H does not exist in all examples
    }
    debug_print("End circadian_rythm_single_core_10_runs_optimized");
}

BENCHMARK(circadian_rythm_single_core_10_runs_optimized)->Unit(benchmark::kMillisecond);


static void circadian_rythm_multi_core_100_runs(benchmark::State& state) {
    auto vessel = Examples::circadian_rhythm();

    debug_print("\nStarting circadian_rythm_multi_core_100_runs");
    for (const auto _ : state) {
        Examples::get_peak_average(1500, vessel, 100, "DA");
    }
    debug_print("End circadian_rythm_multi_core_100_runs");
}

BENCHMARK(circadian_rythm_multi_core_100_runs)->Unit(benchmark::kMillisecond);


static void exponential_decay_single_core(benchmark::State& state) {
    auto vessel = Examples::exponential_decay(50, 0 ,50);

    debug_print("\nStarting exponential_decay_single_core");
    for (const auto _ : state) {
        Examples::get_peak_average_serial(1500, vessel, 100, "C");
    }
    debug_print("End exponential_decay_single_core");
}

BENCHMARK(exponential_decay_single_core)->Unit(benchmark::kMillisecond);


static void exponential_decay_multi_core(benchmark::State& state) {
    auto vessel = Examples::exponential_decay(50, 0, 50);

    debug_print("\nStarting exponential_decay_multi_core");
    for (const auto _ : state) {
        Examples::get_peak_average(1500, vessel, 100, "C");
    }
    debug_print("End exponential_decay_multi_core");
}
BENCHMARK(exponential_decay_multi_core)->Unit(benchmark::kMillisecond);



BENCHMARK_MAIN();

