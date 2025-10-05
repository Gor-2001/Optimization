/***************************************/
// jump_table_window.h
/***************************************/
#ifndef JUMP_TABLE_WINDOW_H
#define JUMP_TABLE_WINDOW_H
/***************************************/
#include "../base_window.h"
/***************************************/

struct jump_table_params_t {
    std::vector<uint16_t> sample;
    uint16_t sample_size;
    uint16_t sample_range;
};

enum jump_table_params_order_t {
    JUMP_RUN_COUNT_INDEX = 0,
    JUMP_SAMPLE_SIZE_INDEX,
    JUMP_SAMPLE_RANGE_INDEX,
};

class QPushButton;

class JumpTableWindow : public BaseWindow {
    Q_OBJECT
public:
    JumpTableWindow(QWidget *parent = nullptr);

private:
    jump_table_params_t jump_table_params;

    using BaseWindow::BaseWindow;

    static void 
    jump_table_params_init(
        jump_table_params_t& jump_table_params,
        const std::vector<uint16_t>& spinVariables
    );

    static void sample_gen(jump_table_params_t& jump_table_params);

    static void test_ifelse(jump_table_params_t& jump_table_params);
    static void test_switch(jump_table_params_t& jump_table_params);

};

#endif // JUMP_TABLE_WINDOW_H
