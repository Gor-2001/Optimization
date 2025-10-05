/***************************************/
// prediction_window.cpp
/***************************************/
#include "prediction_window.h"
/***************************************/

PredictionWindow::PredictionWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount     = 100;
    const uint16_t sampleSize   = 256;
    const uint16_t sampleRange  = 256;
    const uint16_t bucketCount  = 256;

    const uint8_t  spinCount    = 4; 
    const uint8_t  testCount    = 2;

    setCenter();
    setMainLayout();

    setSpinVariablesCount(spinCount);
    setSpinVariables();

    setSpinVariableNames({
        "Run Count",
        "Sample Size",
        "Sample Range",
        "Bucket Count"
    });

    setSpinVariableDefValues({
        runCount, 
        sampleSize,
        sampleRange,
        bucketCount
    });

    prediction_params_t test_params;
    test_params_init(test_params, sampleSize, bucketCount, sampleRange);
    setParam(test_params);
    setGenFunction<prediction_params_t>(PredictionWindow::sample_gen);
    setRunCount(runCount);

    setInfoTitle("Prediction Test Info");
    setInfoPath("src/prediction/prediction_info");
    setRunTitle("Run Prediction Test");

    drawInfoButton();
    drawSpinVariableButtons();
    drawRunButton();
    drawOutputBox();

    setTestCount(testCount);
    setTestNames({"UNSORTED\t", "SORTED\t"});

    setSubTestFunctions<prediction_params_t>
        ({PredictionWindow::test_unsorted, PredictionWindow::test_sorted});

    setupWindow();
}

void 
PredictionWindow::test_params_init(
    prediction_params_t& test_params, 
    const uint16_t sample_size,
    const uint16_t buckets_count,
    const uint16_t sample_range
)
{
    test_params.sample_size = sample_size;
    test_params.buckets_count = buckets_count;
    test_params.sample_range = sample_range;
}

void 
PredictionWindow::sample_gen(
    prediction_params_t& test_params
)
{
    BaseWindow bw;

    test_params.sample = 
        bw.random_sample_generation(test_params.sample_size, test_params.sample_range);

    test_params.buckets = 
        bw.random_sample_generation(test_params.buckets_count, test_params.sample_range);
}

void 
PredictionWindow::test_unsorted(    
    prediction_params_t& test_params
)
{
    std::vector<uint16_t> sums(test_params.buckets_count, 0);

    std::vector<uint16_t> copy(test_params.sample.begin(), test_params.sample.end());

    for(uint16_t i = 0; i < test_params.buckets_count; ++i) 
    {
        for(uint16_t j = 0; j < test_params.sample_size; ++j) 
        {
            if(copy[j] > test_params.buckets[i])
                sums[i] += copy[j];     
        }
    }
}

void 
PredictionWindow::test_sorted(    
    prediction_params_t& test_params
)
{
    std::vector<uint16_t> sums(test_params.buckets_count, 0);

    std::vector<uint16_t> copy(test_params.sample.begin(), test_params.sample.end());
    std::sort(copy.begin(), copy.end());

    for(uint16_t i = 0; i < test_params.buckets_count; ++i) 
    {
        for(uint16_t j = 0; j < test_params.sample_size; ++j) 
        {
            if(copy[j] > test_params.buckets[i])
                sums[i] += copy[j];     
        }
    }
}

