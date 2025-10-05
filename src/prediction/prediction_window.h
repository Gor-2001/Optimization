/***************************************/
// prediction_window.h
/***************************************/
#ifndef PREDICTION_WINDOW_H
#define PREDICTION_WINDOW_H
/***************************************/
#include "../base_window.h"
/***************************************/

struct prediction_params_t {
    std::vector<uint16_t> sample;
    uint16_t sample_size;
    uint16_t sample_range;

    std::vector<uint16_t> buckets;
    uint16_t buckets_count;
};

class QPushButton;

class PredictionWindow : public BaseWindow {
    Q_OBJECT
public:
    PredictionWindow(QWidget *parent = nullptr);

private:
    prediction_params_t test_params;

    void 
    test_params_init(
        prediction_params_t& test_params, 
        const uint16_t sample_size,
        const uint16_t buckets_count,
        const uint16_t sample_range
    );

    using BaseWindow::BaseWindow;
    static void sample_gen(prediction_params_t& test_params);

    static void test_unsorted(prediction_params_t& test_params);
    static void test_sorted(prediction_params_t& test_params);

};

#endif // PREDICTION_WINDOW_H
