#ifndef PREDICTION_EXPERIMENT_H
#define PREDICTION_EXPERIMENT_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SEPARATORS_COUNT    1024
#define VECTOR_SIZE         256
#define NUMBERS_RANGE       1024
#define RUN_COUNT           100

struct vector_params_t {
    uint16_t range;
    uint16_t size;
};

// Benchmark functions

void PSV();

void PSV_unsorted(
    uint16_t separators_count = SEPARATORS_COUNT,
    uint16_t numbers_range = NUMBERS_RANGE, 
    uint16_t vector_size = VECTOR_SIZE
);

void PSV_sorted(
    uint16_t separators_count = SEPARATORS_COUNT,
    uint16_t numbers_range = NUMBERS_RANGE, 
    uint16_t vector_size = VECTOR_SIZE
);

// Helper
std::vector<uint16_t>  
random_vector_generation(    
    const vector_params_t& vector_params
);

#endif // PREDICTION_EXPERIMENT_H