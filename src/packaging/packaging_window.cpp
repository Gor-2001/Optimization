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
    const uint16_t sampleSize   = 256;
    const uint16_t sampleRange  = 256;
    const uint16_t bucketCount  = 256;

    setRunCount(runCount);
    setRunCountIndex(PACK_RUN_COUNT_INDEX);

    setSpinVariables({
        {"Run Count", runCount},
        {"Sample Size", sampleSize},
        {"Sample Range", sampleRange},
        {"Bucket Count", bucketCount}
    });

    setParam(packaging_params);
    setInitFunction<packaging_params_t>(PackagingWindow::packaging_params_init);
    setGenFunction<packaging_params_t>(PackagingWindow::sample_gen);

    setTestFunctions<packaging_params_t>({
        {"Asm\t", PackagingWindow::test_unsorted},
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
    packaging_params.sample_size = spinVariables[PACK_SAMPLE_SIZE_INDEX];
    packaging_params.sample_range = spinVariables[PACK_SAMPLE_RANGE_INDEX];
    packaging_params.buckets_count = spinVariables[PACK_BUCKET_COUNT_INDEX];
}

void 
PackagingWindow::sample_gen(
    packaging_params_t& packaging_params
)
{
    packaging_params.sample = 
        random_sample_generation(packaging_params.sample_size, packaging_params.sample_range);

    packaging_params.buckets = 
        random_sample_generation(packaging_params.buckets_count, packaging_params.sample_range);
}

void 
PackagingWindow::test_unsorted(    
    packaging_params_t& packaging_params
)
{
    print_asm_message();
}

void 
PackagingWindow::test_sorted(    
    packaging_params_t& packaging_params
)
{
    setvbuf(stdout, nullptr, _IONBF, 0); // disable buffering
    std::cout << "Hello World !" << std::endl;
}

