// jump_table_test.h

#ifndef JUMP_TABLE_TEST_H
#define JUMP_TABLE_TEST_H

#include "../../main_utils.h"

struct JT_params_t {
    uint16_t vector_size;
    uint16_t run_count;
    uint8_t  separators_count;
};

// Benchmark functions

void jump_table_switch(
    const JT_params_t JT_params,
    const std::vector<uint8_t>& data,
    std::vector<uint8_t>& count
);

void jump_table_ifelse(
    const JT_params_t JT_params,
    const std::vector<uint8_t>& data,
    std::vector<uint8_t>& count
);

#endif // JUMP_TABLE_TEST_H