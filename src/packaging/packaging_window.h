/***************************************/
// packaging_window.h
/***************************************/
#ifndef PACKAGING_WINDOW_H
#define PACKAGING_WINDOW_H
/***************************************/
#include "../base_window.h"
/***************************************/

struct packaging_params_t {
    std::vector<uint16_t> sample;
    uint16_t sample_size;
    uint16_t sample_range;

    std::vector<uint16_t> buckets;
    uint16_t buckets_count;
};

enum packaging_params_order_t {
    PACK_RUN_COUNT_INDEX = 0,
    PACK_SAMPLE_SIZE_INDEX,
    PACK_SAMPLE_RANGE_INDEX,
    PACK_BUCKET_COUNT_INDEX,
};

class QPushButton;

class PackagingWindow : public BaseWindow {
    Q_OBJECT
public:
    PackagingWindow(QWidget *parent = nullptr);

private:
    packaging_params_t packaging_params;

    using BaseWindow::BaseWindow;

    static void 
    packaging_params_init(
        packaging_params_t& packaging_params, 
        const std::vector<uint16_t>& spinVariables
    );

    static void sample_gen(packaging_params_t& packaging_params);

    static void test_unsorted(packaging_params_t& packaging_params);
    static void test_sorted(packaging_params_t& packaging_params);

};

#endif // PACKAGING_WINDOW_H
