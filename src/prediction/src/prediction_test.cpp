// prediction_test.cpp

#include "../inc/prediction_test.h"

void prediction_test_unsorted(    
    const prediction_params_t& prediction_params,
    const std::vector<uint16_t>& separator,
    const std::vector<uint16_t>& v
)
{
    std::vector<uint16_t> sums(prediction_params.separators_count, 0);

    for(uint16_t i = 0; i < prediction_params.separators_count; ++i) 
    {
        for(uint16_t j = 0; j < prediction_params.vector_size; ++j) 
        {
            if(v[j] > separator[i])
                sums[i] += v[j];     
        }
    }
}

void prediction_test_sorted(
    const prediction_params_t& prediction_params,
    const std::vector<uint16_t>& separator,
    std::vector<uint16_t>& v
)
{
    std::vector<uint16_t> sums(prediction_params.separators_count, 0);
    std::sort(v.begin(), v.end());

    for(uint16_t i = 0; i < prediction_params.separators_count; ++i) 
    {
        for(uint16_t j = 0; j < prediction_params.vector_size; ++j) 
        {
            if(v[j] > separator[i])
                sums[i] += v[j];     
        }
    }
}

