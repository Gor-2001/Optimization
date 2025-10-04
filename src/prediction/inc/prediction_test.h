// prediction_test.h

#ifndef PREDICTION_TEST_H
#define PREDICTION_TEST_H

#include "../../main_utils.h"

#define SEPARATORS_COUNT_PRED 256

struct prediction_params_t {
    std::vector<uint16_t> data;
    uint16_t data_size;

    std::vector<uint16_t> separator;
    uint16_t separators_count;

    uint16_t range;
};

microseconds    
prediction_test(
    void (*prediction_test_sub)(const prediction_params_t&),
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range,
    uint16_t run_count
);

// Benchmark functions

void 
prediction_params_init(
    prediction_params_t& prediction_params, 
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range
);

void 
prediction_test_unsorted(    
    const prediction_params_t& prediction_params
);

void prediction_test_sorted(    
    const prediction_params_t& prediction_params
);

#endif // PREDICTION_TEST_H