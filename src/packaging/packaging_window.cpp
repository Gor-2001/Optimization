/***************************************/
// packaging_window.cpp
/***************************************/
#include "packaging_window.h"
/***************************************/
extern "C" { void print_asm_message(); }
/***************************************/
PackagingWindow::PackagingWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount     = 100;
    const uint16_t wordCount    = 200;
    const uint16_t wordBitLen   = 11;

    setRunCount(runCount);
    setRunCountIndex(PACK_RUN_COUNT_INDEX);

    setSpinVariables({
        {"Run Count", runCount},
        {"Word Count", wordCount},
        {"Word Len in Bits", wordBitLen}
    });

    setParam(packaging_params);
    setInitFunction<packaging_params_t>(PackagingWindow::packaging_params_init);
    setGenFunction<packaging_params_t>(PackagingWindow::sample_gen);

    setTestFunctions<packaging_params_t>({
        {"Bit By Bit\t", PackagingWindow::bit_by_bit},
        {"C++\t", PackagingWindow::test_sorted}
    });

    setInfoTitle("Packaging  Test Info");
    setInfoPath("src/packaging/packaging_info");
    setRunTitle("Run Packaging  Test");

    setupWindow();
}

void 
PackagingWindow::packaging_params_init(
    packaging_params_t& packaging_params, 
    const std::vector<uint16_t>& spinVariables
)
{
    packaging_params.wordsCount = spinVariables[PACK_WORD_COUNT_INDEX];
    packaging_params.wordsBitLen = spinVariables[PACK_WORD_BIT_LEN_INDEX];
}

#define BIT_TO_BYTE(c) ((c) + 7) >> 3

void 
PackagingWindow::sample_gen(
    packaging_params_t& packaging_params
)
{
    const uint16_t range = 256;
    const uint16_t extra = 4;

    packaging_params.srcSize = 
        BIT_TO_BYTE(packaging_params.wordsCount + packaging_params.wordsBitLen) + extra;


    packaging_params.src = random_sample_generation8(packaging_params.srcSize, range);
    packaging_params.words.resize(packaging_params.wordsCount);
}

void 
PackagingWindow::bit_by_bit(    
    packaging_params_t& packaging_params
)
{
    //print_asm_message();
}

void 
PackagingWindow::test_sorted(    
    packaging_params_t& packaging_params
)
{
    //setvbuf(stdout, nullptr, _IONBF, 0); // disable buffering
    //std::cout << "Hello World !" << std::endl;
}

