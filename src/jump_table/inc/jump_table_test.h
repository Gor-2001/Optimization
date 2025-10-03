// jump_table_test.h

#ifndef JUMP_TABLE_TEST_H
#define JUMP_TABLE_TEST_H

#include "../../main_utils.h"

struct jump_table_params_t {
    std::vector<uint16_t> data;
    uint16_t data_size;

    uint16_t range;
};

microseconds    
jump_table_test(
    void (*jump_table_test_sub)(const jump_table_params_t&),
    uint16_t data_size,
    uint16_t range,
    uint16_t run_count
);

// Benchmark functions

void 
jump_table_params_init(
    jump_table_params_t& jump_table_params, 
    uint16_t data_size,
    uint16_t range
);

void 
jump_table_test_switch(
    const jump_table_params_t& jt_params
);

void 
jump_table_test_ifelse(
    const jump_table_params_t& jt_params
);

#endif // JUMP_TABLE_TEST_H