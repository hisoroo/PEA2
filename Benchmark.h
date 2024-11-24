#ifndef BENCHMARK_H
#define BENCHMARK_H

#include "config/Config.h"
#include "Matrix.h"
#include "TSP.h"

class Benchmark {
public:
    void runBenchmark(const Config &config);
};

#endif