#include <benchmark/benchmark.h>

#include "circadian_rhythm.hpp"
#include "debug_print.hpp"
#include "../lib/examples/covid-19.hpp"
#include "../lib/examples/exponential_decay.hpp"
#include "../lib/examples/multi_threading.hpp"


using namespace StochasticSimulation;

// Requirement 10: Benchmark and compare the stochastic simulation performance (e.g. the time it takes to compute 100 simulations
// a single core, multiple cores, or improved implementation). Record the timings and make your conclusions.

static void seihr_single_core(benchmark::State &state) {
    auto vessel = Examples::seihr(20000);

    debug_print("\nStarting single core seihr");
    for (const auto _: state) {
        Examples::get_peak_average_serial(100, vessel, 100, "H");
    }
    debug_print("End single core seihr");
}


BENCHMARK(seihr_single_core)->Unit(benchmark::kMillisecond)->Iterations(50);;


static void seihr_multi_core(benchmark::State &state) {
    auto vessel = Examples::seihr(20000);

    debug_print("\nStarting multi-core seihr");
    for (const auto _: state) {
        Examples::get_peak_average(100, vessel, 100, "H");
    }
    debug_print("End multi-core seihr");
}

BENCHMARK(seihr_multi_core)->Unit(benchmark::kMillisecond)->Iterations(50);


static void circadian_rhythm_single_core_100_runs(benchmark::State &state) {
    auto vessel = Examples::circadian_rhythm();

    debug_print("\nStarting circadian_rhythm_single_core_100_runs");
    for (const auto _: state) {
        Examples::get_peak_average_serial(48, vessel, 100, "DA");
        // This finds peak average of H - H does not exist in all examples
    }
    debug_print("End circadian_rhythm_single_core_100_runs");
}

BENCHMARK(circadian_rhythm_single_core_100_runs)->Unit(benchmark::kMillisecond)->Iterations(50);

static void circadian_rhythm_single_core_100_runs_optimized(benchmark::State &state) {
    auto vessel = Examples::circadian_rhythm();

    debug_print("\nStarting circadian_rhythm_single_core_100_runs_optimized");
    for (const auto _: state) {
        Examples::get_peak_average_serial_optimized(48, vessel, 100, "DA");
        // This finds peak average of H - H does not exist in all examples
    }
    debug_print("End circadian_rhythm_single_core_100_runs_optimized");
}

BENCHMARK(circadian_rhythm_single_core_100_runs_optimized)->Unit(benchmark::kMillisecond)->Iterations(50);


static void circadian_rhythm_multi_core_100_runs(benchmark::State &state) {
    auto vessel = Examples::circadian_rhythm();

    debug_print("\nStarting circadian_rhythm_multi_core_100_runs");
    for (const auto _: state) {
        Examples::get_peak_average(48, vessel, 100, "DA");
    }
    debug_print("End circadian_rhythm_multi_core_100_runs");
}

BENCHMARK(circadian_rhythm_multi_core_100_runs)->Unit(benchmark::kMillisecond)->Iterations(50);


static void exponential_decay_single_core(benchmark::State &state) {
    auto vessel = Examples::exponential_decay(50, 0, 50);

    debug_print("\nStarting exponential_decay_single_core");
    for (const auto _: state) {
        Examples::get_peak_average_serial(48, vessel, 100, "C");
    }
    debug_print("End exponential_decay_single_core");
}

BENCHMARK(exponential_decay_single_core)->Unit(benchmark::kMillisecond)->Iterations(50);


static void exponential_decay_multi_core(benchmark::State &state) {
    auto vessel = Examples::exponential_decay(50, 0, 50);

    debug_print("\nStarting exponential_decay_multi_core");
    for (const auto _: state) {
        Examples::get_peak_average(1500, vessel, 100, "C");
    }
    debug_print("End exponential_decay_multi_core");
}

BENCHMARK(exponential_decay_multi_core)->Unit(benchmark::kMillisecond)->Iterations(50);

BENCHMARK_MAIN();
