// prediction_test.cpp

#include "../inc/prediction_test.h"

microseconds     
prediction_test(
    void (*prediction_test_sub)(const prediction_params_t&),
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range,
    uint16_t run_count
)
{
    prediction_params_t prediction_params;
    //outputBox->clear();

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;
    microseconds duration{0};

    for(uint16_t i = 0; i < run_count; ++i)
    {
        prediction_params_init(prediction_params, data_size, separators_count, range);
        start = high_resolution_clock::now();
        prediction_test_sub(prediction_params);
        stop = high_resolution_clock::now();
        duration += duration_cast<microseconds>(stop - start);
    }

    return duration;
}

void 
prediction_params_init(
    prediction_params_t& prediction_params, 
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range
)
{
    prediction_params.data_size = data_size;
    prediction_params.separators_count = separators_count;
    prediction_params.range = range;

    prediction_params.data = 
        random_vector_generation(prediction_params.data_size, prediction_params.range);

    prediction_params.separator = 
        random_vector_generation(prediction_params.separators_count, prediction_params.range);

}

void
prediction_test_unsorted(
    const prediction_params_t& prediction_params
)
{
    std::vector<uint16_t> sums(prediction_params.separators_count, 0);

    std::vector<uint16_t> copy(prediction_params.data.begin(), prediction_params.data.end());

    for(uint16_t i = 0; i < prediction_params.separators_count; ++i) 
    {
        for(uint16_t j = 0; j < prediction_params.data_size; ++j) 
        {
            if(copy[j] > prediction_params.separator[i])
                sums[i] += copy[j];     
        }
    }
}

void 
prediction_test_sorted(
    const prediction_params_t& prediction_params
)
{
    std::vector<uint16_t> sums(prediction_params.separators_count, 0);

    std::vector<uint16_t> copy(prediction_params.data.begin(), prediction_params.data.end());
    std::sort(copy.begin(), copy.end());

    for(uint16_t i = 0; i < prediction_params.separators_count; ++i) 
    {
        for(uint16_t j = 0; j < prediction_params.data_size; ++j) 
        {
            if(copy[j] > prediction_params.separator[i])
                sums[i] += copy[j];     
        }
    }
}

