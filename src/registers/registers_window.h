/***************************************/
// registers_window.h
/***************************************/
#ifndef REGISTERS_WINDOW_H
#define REGISTERS_WINDOW_H
/***************************************/
#include "../base_window.h"
/***************************************/

struct registers_params_t {
    std::vector<uint8_t> sample;
    uint16_t round_count;
    uint16_t sample_range;
    uint8_t row_count;
    uint8_t column_count;
};

enum registers_params_order_t {
    REG_RUN_COUNT_INDEX = 0,
    REG_ROUND_COUNT_INDEX = 1,
};

class QPushButton;

class RegistersWindow : public BaseWindow {
    Q_OBJECT
public:
    RegistersWindow(QWidget *parent = nullptr);

private:
    registers_params_t registers_params;

    using BaseWindow::BaseWindow;

    static void 
    registers_params_init(
        registers_params_t& registers_params, 
        const std::vector<uint16_t>& spinVariables
    );

    static void sample_gen(registers_params_t& registers_params);
    static void test_small_registers(registers_params_t& registers_params);
    static void test_large_registers(registers_params_t& registers_params);

};

#endif // REGISTERS_WINDOW_H
