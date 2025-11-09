/***************************************/
// registers_window.cpp
/***************************************/
#include "registers_window.h"
/***************************************/
extern "C" void transform_sample_asm(uint8_t* sample, uint16_t rounds);
/***************************************/

RegistersWindow::RegistersWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount     = 1000;
    const uint16_t roundCount   = 100;

    setRunCount(runCount);
    setRunCountIndex(REG_RUN_COUNT_INDEX);

    setSpinVariables({
        {"Run Count", runCount},
        {"Round Count", roundCount}
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
    registers_params.round_count = spinVariables[REG_ROUND_COUNT_INDEX];
}

void 
RegistersWindow::sample_gen(
    registers_params_t& registers_params
)
{
    registers_params.sample = random_sample_generation8(
            registers_params.column_count * registers_params.column_count,
            registers_params.sample_range);

}

void RegistersWindow::test_small_registers(registers_params_t& registers_params)
{
    auto& sample = registers_params.sample; // flat vector
    const uint16_t rounds = registers_params.round_count;
    const size_t row_count = registers_params.row_count;       // 4
    const size_t column_count = registers_params.column_count; // 16

    auto add_rows = [&](size_t row_a, size_t row_b) {
        for (size_t j = 0; j < column_count; ++j) {
            sample[row_a * column_count + j] =
                static_cast<uint8_t>(
                    sample[row_a * column_count + j] + 
                    sample[row_b * column_count + j]
                ); // wraps around automatically
        }
    };

    for (uint16_t r = 0; r < rounds; ++r)
    {
        // --- Step 1: Row arithmetic ---
        add_rows(0, 1); // row0 += row1
        add_rows(2, 3); // row2 += row3

        // --- Step 2: Swap rows 1 and 2 ---
        for (size_t j = 0; j < column_count; ++j) {
            std::swap(
                sample[1 * column_count + j],
                sample[2 * column_count + j]
            );
        }

        // --- Step 3: Cyclic shifts ---
        // Row 0: left by 1
        std::rotate(
            sample.begin() + 0 * column_count,
            sample.begin() + 0 * column_count + 1,
            sample.begin() + 1 * column_count
        );

        // Row 1: right by 1
        std::rotate(
            sample.rbegin() + (row_count - 1 - 1) * column_count,
            sample.rbegin() + (row_count - 1 - 1) * column_count + 1,
            sample.rbegin() + (row_count - 1 - 0) * column_count
        );

        // Row 2: left by 2
        std::rotate(
            sample.begin() + 2 * column_count,
            sample.begin() + 2 * column_count + 2,
            sample.begin() + 3 * column_count
        );

        // Row 3: right by 2
        std::rotate(
            sample.rbegin() + (row_count - 1 - 3) * column_count,
            sample.rbegin() + (row_count - 1 - 3) * column_count + 2,
            sample.rbegin() + (row_count - 1 - 2) * column_count
        );
    }
}


void 
RegistersWindow::test_large_registers(    
    registers_params_t& registers_params
)
{
    transform_sample_asm(
        registers_params.sample.data(),
        registers_params.round_count);
}

