/***************************************/
// registers_window.cpp
/***************************************/
#include "registers_window.h"
/***************************************/
//extern "C" { void print_asm_message(); }
/***************************************/

RegistersWindow::RegistersWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount     = 100;

    setRunCount(runCount);
    setRunCountIndex(REG_RUN_COUNT_INDEX);

    setSpinVariables({
        {"Run Count", runCount}
    });

    setParam(registers_params);
    setInitFunction<registers_params_t>(RegistersWindow::registers_params_init);
    setGenFunction<registers_params_t>(RegistersWindow::sample_gen);

    setTestFunctions<registers_params_t>({
        {"SMALL\t", RegistersWindow::test_small_registers},
        {"LARGE\t", RegistersWindow::test_large_registers}
    });

    setInfoTitle("Registers Test Info");
    setInfoPath("src/registers/registers_info");
    setRunTitle("Run Registers Test");

    setupWindow();
}

void 
RegistersWindow::registers_params_init(
    registers_params_t& registers_params, 
    const std::vector<uint16_t>& spinVariables
)
{
    registers_params.row_count = 4;
    registers_params.column_count = 16;
    registers_params.sample_range = 256;
}

void 
RegistersWindow::sample_gen(
    registers_params_t& registers_params
)
{
    registers_params.sample.erase(
        registers_params.sample.begin(), 
        registers_params.sample.end());

    for(uint8_t i = 0; i < registers_params.row_count; ++i)
        registers_params.sample.push_back(
            random_sample_generation8(
                registers_params.column_count, 
                registers_params.sample_range));

}


void 
RegistersWindow::test_small_registers(    
    registers_params_t& registers_params
)
{
    auto sample = registers_params.sample;

    const size_t n = sample[0].size();

    auto add_rows = [](std::vector<uint8_t>& a, const std::vector<uint8_t>& b) {
        for (size_t j = 0; j < a.size(); ++j)
            a[j] = static_cast<uint8_t>(a[j] + b[j]); // wraps around automatically
    };

    // --- Step 1: Row arithmetic ---
    add_rows(sample[0], sample[1]);
    add_rows(sample[2], sample[3]);

    // --- Step 2: Swap rows 1 and 2 ---
    std::swap(sample[1], sample[2]);

    // --- Step 3: Cyclic shifts ---
    // Row 0: left by 1
    std::rotate(sample[0].begin(), sample[0].begin() + 1, sample[0].end());
    // Row 1: right by 1
    std::rotate(sample[1].rbegin(), sample[1].rbegin() + 1, sample[1].rend());
    // Row 2: left by 2
    std::rotate(sample[2].begin(), sample[2].begin() + 2, sample[2].end());
    // Row 3: right by 2
    std::rotate(sample[3].rbegin(), sample[3].rbegin() + 2, sample[3].rend());

    // --- Step 4: Repeat add+swap ---
    add_rows(sample[0], sample[1]);
    add_rows(sample[2], sample[3]);
    std::swap(sample[1], sample[2]);
}

void 
RegistersWindow::test_large_registers(    
    registers_params_t& registers_params
)
{
    // std::vector<uint16_t> sums(registers_params.buckets_count, 0);

    // std::vector<uint16_t> copy(registers_params.sample.begin(), registers_params.sample.end());
    // std::sort(copy.begin(), copy.end());

    // for(uint16_t i = 0; i < registers_params.buckets_count; ++i) 
    // {
    //     for(uint16_t j = 0; j < registers_params.sample_size; ++j) 
    //     {
    //         if(copy[j] > registers_params.buckets[i])
    //             sums[i] += copy[j];     
    //     }
    // }
}

