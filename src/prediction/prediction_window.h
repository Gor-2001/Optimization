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

enum prediction_params_order_t {
    runCountIndexPred = 0,
    sampleSizeIndex = 1,
    sampleRangeIndex = 2,
    bucketCountIndex = 3,
};

class QPushButton;

class PredictionWindow : public BaseWindow {
    Q_OBJECT
public:
    PredictionWindow(QWidget *parent = nullptr);

private:
    prediction_params_t prediction_params;

    using BaseWindow::BaseWindow;

    static void 
    prediction_params_init(
        prediction_params_t& prediction_params, 
        const std::vector<uint16_t>& spinVariables
    );

    static void sample_gen(prediction_params_t& prediction_params);

    static void test_unsorted(prediction_params_t& prediction_params);
    static void test_sorted(prediction_params_t& prediction_params);

};

#endif // PREDICTION_WINDOW_H
