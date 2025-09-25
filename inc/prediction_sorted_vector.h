#ifndef PREDICTION_SORTED_VECTOR_H
#define PREDICTION_SORTED_VECTOR_H

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
void PSV_unsorted();
void PSV_sorted();

// Helper
std::vector<uint16_t>  
random_vector_generation(    
    const vector_params_t& vector_params
);

#endif // PREDICTION_SORTED_VECTOR_H