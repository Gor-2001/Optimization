// main_utils.h

#ifndef DEFINE_H
#define DEFINE_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>

/// Size of the data buffer (number of elements)
#define DATA_SIZE                   256

/// Maximum value range for data elements
#define DATA_RANGE                  512

/// Number of times the test/algorithm should run
#define RUN_COUNT                   100

using namespace std::chrono;

template <typename T>
std::vector<T> random_vector_generation(
    std::size_t vector_size,
    T range
)
{
    std::vector<T> result(vector_size, 0);

    for (auto& it : result)
        it = static_cast<T>(rand() % range);

    return result;
}

#endif // DEFINE_H