// prediction_test.cpp

#include "../inc/prediction_test.h"

void prediction_test_unsorted(const prediction_params_t& prediction_params)
{
    for(uint16_t k = 0; k < prediction_params.run_count; ++k)
    {
        std::vector<uint16_t> sums(prediction_params.separators_count, 0);

        std::vector<uint16_t> separator = 
            random_vector_generation(prediction_params.separators_count, prediction_params.range);

        std::vector<uint16_t> v =
            random_vector_generation(prediction_params.vector_size, prediction_params.range);

        for(uint16_t i = 0; i < prediction_params.separators_count; ++i) 
        {
            for(uint16_t j = 0; j < prediction_params.vector_size; ++j) 
            {
                if(v[j] > separator[i])
                    sums[i] += v[j];     
            }
        }
    }
}

void prediction_test_sorted(const prediction_params_t& prediction_params)
{
    for(uint16_t k = 0; k < prediction_params.run_count; ++k)
    {
        std::vector<uint16_t> sums(prediction_params.separators_count, 0);

        std::vector<uint16_t> separator = 
            random_vector_generation(prediction_params.separators_count, prediction_params.range);

        std::vector<uint16_t> v =
            random_vector_generation(prediction_params.vector_size, prediction_params.range);

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
}

std::vector<uint16_t> 
random_vector_generation(
    const uint16_t vector_size,
    const uint16_t range
)
{
    std::vector<uint16_t> result(vector_size, 0);

    for(auto& it : result)
        it = rand() % range;
    return result;
}

