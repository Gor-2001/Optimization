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

    setSpinVariables({
        {"Run Count", runCount},
        {"Sample Size", sampleSize},
        {"Sample Range", sampleRange},
        {"Bucket Count", bucketCount}
    });

    setParam(prediction_params);
    setInitFunction<prediction_params_t>(PredictionWindow::prediction_params_init);
    setGenFunction<prediction_params_t>(PredictionWindow::sample_gen);

    setTestFunctions<prediction_params_t>({
        {"UNSORTED\t", PredictionWindow::test_unsorted},
        {"SORTED\t", PredictionWindow::test_sorted}
    });

    setRunCount(runCount);
    setRunCountIndex(PRED_RUN_COUNT_INDEX);

    setInfoTitle("Prediction Test Info");
    setInfoPath("src/prediction/prediction_info");
    setRunTitle("Run Prediction Test");

    setupWindow();
}

void 
PredictionWindow::prediction_params_init(
    prediction_params_t& prediction_params, 
    const std::vector<uint16_t>& spinVariables
)
{
    prediction_params.sample_size = spinVariables[PRED_SAMPLE_SIZE_INDEX];
    prediction_params.sample_range = spinVariables[PRED_SAMPLE_RANGE_INDEX];
    prediction_params.buckets_count = spinVariables[PRED_BUCKET_COUNT_INDEX];
}

void 
PredictionWindow::sample_gen(
    prediction_params_t& prediction_params
)
{
    prediction_params.sample = 
        random_sample_generation(prediction_params.sample_size, prediction_params.sample_range);

    prediction_params.buckets = 
        random_sample_generation(prediction_params.buckets_count, prediction_params.sample_range);
}

void 
PredictionWindow::test_unsorted(    
    prediction_params_t& prediction_params
)
{
    std::vector<uint16_t> sums(prediction_params.buckets_count, 0);

    std::vector<uint16_t> copy(prediction_params.sample.begin(), prediction_params.sample.end());

    for(uint16_t i = 0; i < prediction_params.buckets_count; ++i) 
    {
        for(uint16_t j = 0; j < prediction_params.sample_size; ++j) 
        {
            if(copy[j] > prediction_params.buckets[i])
                sums[i] += copy[j];     
        }
    }
}

void 
PredictionWindow::test_sorted(    
    prediction_params_t& prediction_params
)
{
    std::vector<uint16_t> sums(prediction_params.buckets_count, 0);

    std::vector<uint16_t> copy(prediction_params.sample.begin(), prediction_params.sample.end());
    std::sort(copy.begin(), copy.end());

    for(uint16_t i = 0; i < prediction_params.buckets_count; ++i) 
    {
        for(uint16_t j = 0; j < prediction_params.sample_size; ++j) 
        {
            if(copy[j] > prediction_params.buckets[i])
                sums[i] += copy[j];     
        }
    }
}

