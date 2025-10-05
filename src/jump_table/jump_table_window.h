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

class QPushButton;

class JumpTableWindow : public BaseWindow {
    Q_OBJECT
public:
    JumpTableWindow(QWidget *parent = nullptr);

private:
    jump_table_params_t test_params;

    void 
    jump_table_params_init(
        jump_table_params_t& test_params,
        const uint16_t sample_size,
        const uint16_t sample_range
    );

    using BaseWindow::BaseWindow;
    static void sample_gen(jump_table_params_t& test_params);

    static void test_ifelse(jump_table_params_t& test_params);
    static void test_switch(jump_table_params_t& test_params);

};

#endif // JUMP_TABLE_WINDOW_H
