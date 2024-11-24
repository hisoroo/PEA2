#include "config/Config.h"
#include "Benchmark.h"

int main() {
    Config config("config/config.txt");
    Benchmark benchmark;
    benchmark.runBenchmark(config);
    return 0;
}