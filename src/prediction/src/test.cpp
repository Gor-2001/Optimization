#include "../inc/test.h"
using namespace std::chrono;

void prediction_test_unsorted(uint16_t separators_count, uint16_t numbers_range, uint16_t vector_size)
{
    vector_params_t separators_params = {numbers_range, separators_count};
    std::vector<uint16_t> separator = random_vector_generation(separators_params);
    std::vector<uint16_t> sums(separators_count, 0);

    vector_params_t vector_params = {numbers_range, vector_size};
    std::vector<uint16_t> v = random_vector_generation(vector_params);

    for(uint16_t i = 0; i < separators_count; ++i) 
    {
        for(uint16_t j = 0; j < vector_size; ++j) 
        {
            if(v[j] > separator[i])
                sums[i] += v[j];     
        }
    }
}

void prediction_test_sorted(uint16_t separators_count, uint16_t numbers_range, uint16_t vector_size)
{
    vector_params_t separators_params = {numbers_range, separators_count};
    std::vector<uint16_t> separator = random_vector_generation(separators_params);
    std::vector<uint16_t> sums(separators_count, 0);

    vector_params_t vector_params = {numbers_range, vector_size};
    std::vector<uint16_t> v = random_vector_generation(vector_params);

    std::sort(v.begin(), v.end());

    for(uint16_t i = 0; i < separators_count; ++i) 
    {
        for(uint16_t j = 0; j < vector_size; ++j) 
        {
            if(v[j] > separator[i])
                sums[i] += v[j];     
        }
    }
}

std::vector<uint16_t> 
random_vector_generation(
    const vector_params_t& vector_params
)
{
    std::vector<uint16_t> result(vector_params.size, 0);

    for(auto& it : result)
        it = rand() % vector_params.range;
    return result;
}

