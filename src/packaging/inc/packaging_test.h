// packaging_test.h

#ifndef PACKAGING_TEST_H
#define PACKAGING_TEST_H

#include "../../main_utils.h"

#define SEPARATORS_COUNT_PACK 256

struct packaging_params_t {
    std::vector<uint16_t> data;
    uint16_t data_size;

    std::vector<uint16_t> separator;
    uint16_t separators_count;

    uint16_t range;
};

microseconds    
packaging_test(
    void (*packaging_test_sub)(const packaging_params_t&),
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range,
    uint16_t run_count
);

// Benchmark functions

void 
packaging_params_init(
    packaging_params_t& packaging_params, 
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range
);

void 
packaging_test_unsorted(    
    const packaging_params_t& packaging_params
);

void packaging_test_sorted(    
    const packaging_params_t& packaging_params
);

#endif // PACKAGING_TEST_H