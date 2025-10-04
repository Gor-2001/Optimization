// packaging_test.cpp

#include "../inc/packaging_test.h"

microseconds     
packaging_test(
    void (*packaging_test_sub)(const packaging_params_t&),
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range,
    uint16_t run_count
)
{
    packaging_params_t packaging_params;

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;
    microseconds duration{0};

    for(uint16_t i = 0; i < run_count; ++i)
    {
        packaging_params_init(packaging_params, data_size, separators_count, range);
        start = high_resolution_clock::now();
        packaging_test_sub(packaging_params);
        stop = high_resolution_clock::now();
        duration += duration_cast<microseconds>(stop - start);
    }

    return duration;
}

void 
packaging_params_init(
    packaging_params_t& packaging_params, 
    uint16_t data_size,
    uint16_t separators_count,
    uint16_t range
)
{
    packaging_params.data_size = data_size;
    packaging_params.separators_count = separators_count;
    packaging_params.range = range;

    packaging_params.data = 
        random_vector_generation(packaging_params.data_size, packaging_params.range);

    packaging_params.separator = 
        random_vector_generation(packaging_params.separators_count, packaging_params.range);

}

void
packaging_test_unsorted(
    const packaging_params_t& packaging_params
)
{
    std::vector<uint16_t> sums(packaging_params.separators_count, 0);

    std::vector<uint16_t> copy(packaging_params.data.begin(), packaging_params.data.end());

    for(uint16_t i = 0; i < packaging_params.separators_count; ++i) 
    {
        for(uint16_t j = 0; j < packaging_params.data_size; ++j) 
        {
            if(copy[j] > packaging_params.separator[i])
                sums[i] += copy[j];     
        }
    }
}

void 
packaging_test_sorted(
    const packaging_params_t& packaging_params
)
{
    std::vector<uint16_t> sums(packaging_params.separators_count, 0);

    std::vector<uint16_t> copy(packaging_params.data.begin(), packaging_params.data.end());
    std::sort(copy.begin(), copy.end());

    for(uint16_t i = 0; i < packaging_params.separators_count; ++i) 
    {
        for(uint16_t j = 0; j < packaging_params.data_size; ++j) 
        {
            if(copy[j] > packaging_params.separator[i])
                sums[i] += copy[j];     
        }
    }
}

