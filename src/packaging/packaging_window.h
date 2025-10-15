/***************************************/
// packaging_window.h
/***************************************/
#ifndef PACKAGING_WINDOW_H
#define PACKAGING_WINDOW_H
/***************************************/
#include "../base_window.h"
/***************************************/

struct packaging_params_t {
    std::vector<uint8_t> src;
    uint16_t srcSize;

    std::vector<uint32_t> words;
    uint16_t wordsCount;
    uint8_t wordsBitLen;
};

enum packaging_params_order_t {
    PACK_RUN_COUNT_INDEX = 0,
    PACK_WORD_COUNT_INDEX,
    PACK_WORD_BIT_LEN_INDEX
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

    static void bit_by_bit(packaging_params_t& packaging_params);
    static void test_sorted(packaging_params_t& packaging_params);

};

#endif // PACKAGING_WINDOW_H
