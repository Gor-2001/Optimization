// prediction_test.h

#ifndef PREDICTION_TEST_H
#define PREDICTION_TEST_H

#include "../../main_utils.h"

#define VECTOR_SIZE         256
#define RUN_COUNT           100
#define SEPARATORS_COUNT    1024
#define RANGE               1024


struct prediction_params_t {
    uint16_t vector_size;
    uint16_t run_count;
    uint16_t separators_count;
    uint16_t range;
};

// Benchmark functions

void prediction_test_unsorted(    
    const prediction_params_t& prediction_params,
    const std::vector<uint16_t>& separator,
    const std::vector<uint16_t>& v
);

void prediction_test_sorted(    
    const prediction_params_t& prediction_params,
    const std::vector<uint16_t>& separator,
    std::vector<uint16_t>& v
);

#endif // PREDICTION_TEST_H