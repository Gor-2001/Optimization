/***************************************/
// dependency_window.h
/***************************************/
#ifndef DEPENDENCY_WINDOW_H
#define DEPENDENCY_WINDOW_H
/***************************************/
#include "../base_window.h"
/***************************************/

struct dependency_params_t {
    std::vector<uint16_t> sample;
    uint16_t sample_size;
    uint16_t sample_range;
};

enum dependency_params_order_t {
    DEP_RUN_COUNT_INDEX = 0,
    DEP_SAMPLE_SIZE_INDEX,
    DEP_SAMPLE_RANGE_INDEX
};

class QPushButton;

class DependencyWindow : public BaseWindow {
    Q_OBJECT
public:
    DependencyWindow(QWidget *parent = nullptr);

private:
    dependency_params_t dependency_params;

    using BaseWindow::BaseWindow;

    static void 
    dependency_params_init(
        dependency_params_t& dependency_params, 
        const std::vector<uint16_t>& spinVariables
    );

    static void sample_gen(dependency_params_t& dependency_params);

    static void test_neighbor_add(dependency_params_t& dependency_params);
    static void test_halfway_add(dependency_params_t& dependency_params);
};

#endif // DEPENDENCY_WINDOW_H
