/***************************************/
// packaging_window.cpp
/***************************************/
#include "packaging_window.h"
/***************************************/

#define IS_LITTLE_ENDIAN (*(uint8_t *)&(uint16_t){1})
#include <cstdint>

PackagingWindow::PackagingWindow(QWidget *parent)
    : BaseWindow(parent)
{
    inner_test();
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount     = 10000;
    const uint16_t wordCount    = 1000;
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
        {"Bit By Bit\t\t", PackagingWindow::bit_by_bit},
        {"Word By Word\t", PackagingWindow::word_by_word},
        {"Chaining Standart u64\t", PackagingWindow::chaining_u64}//,
        //{"Chaining Standart u128\t", PackagingWindow::chaining_u128},
        //{"Chaining Big u64\t", PackagingWindow::chaining_u64_big},
        //{"Chaining Big u128\t", PackagingWindow::chaining_u128_big}
    });

    setInfoTitle("Packaging Test Info");
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
    packaging_params.srcRange = 256;
    packaging_params.wordsCount = spinVariables[PACK_WORD_COUNT_INDEX];
    packaging_params.wordsBitLen = spinVariables[PACK_WORD_BIT_LEN_INDEX];

    const uint16_t extra = 4;
    packaging_params.srcSize = packaging_params.wordsCount;
    packaging_params.srcSize *= packaging_params.wordsBitLen;
    packaging_params.srcSize >>= 3;
    packaging_params.srcSize += extra;

    packaging_params.words.resize(packaging_params.wordsCount);
}

void 
PackagingWindow::sample_gen(
    packaging_params_t& packaging_params
)
{
    packaging_params.src = random_sample_generation8(
        packaging_params.srcSize, 
        packaging_params.srcRange
    );
}

void 
PackagingWindow::bit_by_bit(    
    packaging_params_t& packaging_params
)
{
    uint64_t bitPos = 0;
    for (uint32_t i = 0; i < packaging_params.wordsCount; ++i) 
    {
        uint32_t value = 0;
        for (uint16_t b = 0; b < packaging_params.wordsBitLen; ++b) {
            uint32_t byteIndex = bitPos >> 3;
            uint8_t  bitIndex  = 7 - (bitPos & 7);
            uint8_t  bit = (packaging_params.src[byteIndex] >> bitIndex) & 1;

            value = (value << 1) | bit;
            ++bitPos;
        }

        packaging_params.words[i] = value;
    }
}

void 
PackagingWindow::word_by_word(    
    packaging_params_t& packaging_params
)
{
    uint64_t bitPos = 0;
    uint64_t value = 0;
    uint8_t* ptr;

    for (uint32_t i = 0; i < packaging_params.wordsCount; ++i) 
    {
        ptr = packaging_params.src.data() + (bitPos >> 3);

        value = *(ptr++);
        value <<= 8;
        value |= *(ptr++);
        value <<= 8;
        value |= *(ptr++);
        value <<= 8;
        value |= *(ptr++);
        value <<= 8;
        value |= *(ptr++);

        value <<= 24 + (bitPos & 7);
        value >>= (64 - packaging_params.wordsBitLen);
        packaging_params.words[i] = value;

        bitPos += packaging_params.wordsBitLen;
    }
}

void 
PackagingWindow::chaining_u64(    
    packaging_params_t& packaging_params
)
{
    uint8_t* ptr = packaging_params.src.data();

    uint64_t bitCount = 0;
    uint64_t value = 0;
    uint64_t temp = 0;

    uint64_t mask = 
        (1ull << packaging_params.wordsBitLen) - 1ull;

    for (uint32_t i = 0; i < packaging_params.wordsCount; ++i) 
    {
        if(bitCount < packaging_params.wordsBitLen)
        {
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            bitCount += 32;
        }

        bitCount -= packaging_params.wordsBitLen;
        temp = (value >> bitCount);
        temp &= mask;
        packaging_params.words[i] = temp;
    }
}

void 
PackagingWindow::chaining_u128(    
    packaging_params_t& packaging_params
)
{
    uint8_t* ptr = packaging_params.src.data();

    uint64_t bitCount = 0;

    unsigned __int128 value = 0;
    unsigned __int128 temp = 0;

    unsigned __int128 mask = 
        (1ull << packaging_params.wordsBitLen) - 1ull;

    for (uint32_t i = 0; i < packaging_params.wordsCount; ++i) 
    {
        if(bitCount < packaging_params.wordsBitLen)
        {
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);

            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);

            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);
            value <<= 8;
            value |= *(ptr++);

            bitCount += 96;
        }

        bitCount -= packaging_params.wordsBitLen;
        temp = (value >> bitCount);
        temp &= mask;
        packaging_params.words[i] = temp;
    }
}

void 
PackagingWindow::chaining_u64_big(    
    packaging_params_t& packaging_params
)
{
    uint32_t* ptr = (uint32_t*)packaging_params.src.data();

    uint64_t bitCount = 0;
    uint64_t value = 0;
    uint64_t temp = 0;

    uint64_t mask = 
        (1ull << packaging_params.wordsBitLen) - 1ull;

    for (uint32_t i = 0; i < packaging_params.wordsCount; ++i) 
    {
        if(bitCount < packaging_params.wordsBitLen)
        {
            value <<= 32;
            value |= *(ptr++);
            bitCount += 32;
        }

        bitCount -= packaging_params.wordsBitLen;
        temp = (value >> bitCount);
        temp &= mask;
        packaging_params.words[i] = temp;
    }
}

void 
PackagingWindow::chaining_u128_big(    
    packaging_params_t& packaging_params
)
{
    uint32_t* ptr = (uint32_t*)packaging_params.src.data();

    uint64_t bitCount = 0;

    unsigned __int128 value = 0;
    unsigned __int128 temp = 0;

    unsigned __int128 mask = 
        (1ull << packaging_params.wordsBitLen) - 1ull;

    for (uint32_t i = 0; i < packaging_params.wordsCount; ++i) 
    {
        if(bitCount < packaging_params.wordsBitLen)
        {
            value <<= 32;
            value |= *(ptr++);

            value <<= 32;
            value |= *(ptr++);

            value <<= 32;
            value |= *(ptr++);

            bitCount += 96;
        }

        bitCount -= packaging_params.wordsBitLen;
        temp = (value >> bitCount);
        temp &= mask;
        packaging_params.words[i] = temp;
    }
}

void
PackagingWindow::inner_test()
{
#ifdef __DEBUG

    #ifdef IS_LITTLE_ENDIAN
        std::cout << "Little endian \n";
    #else
        std::cout << "Big endian \n";
    #endif

    packaging_params_t packaging_params;
    std::vector<uint16_t> spinVariables = {1, 200, 0};

    std::cout << "Test params are\n";
    std::cout << "Words Bit Count = {1, 2, ..., 32}\n";
    std::cout << "Words Count = " << spinVariables[1] << "\n";

    for (size_t i = 0; i < 32; i++)
    {
        ++spinVariables[2];

        packaging_params_init(packaging_params, spinVariables);
        sample_gen(packaging_params);

        bit_by_bit(packaging_params);
        std::vector<uint32_t> bit_by_bit_dt = packaging_params.words;

        word_by_word(packaging_params);
        std::vector<uint32_t> word_by_word_dt = packaging_params.words;

        if (!std::equal(bit_by_bit_dt.begin(), bit_by_bit_dt.end(), word_by_word_dt.begin())) {
            std::cout << "Vectors are NOT equal!\n";
            std::cout << "bit_by_bit_dt:  ";
            for (auto v : bit_by_bit_dt) std::cout << (int)v << ' ';
            std::cout << "\nword_by_word_dt: ";
            for (auto v : word_by_word_dt) std::cout << (int)v << ' ';
            std::cout << '\n';
        }

        chaining_u64(packaging_params);
        std::vector<uint32_t> chaining_64_dt = packaging_params.words;

        if (!std::equal(bit_by_bit_dt.begin(), bit_by_bit_dt.end(), chaining_64_dt.begin())) {
            std::cout << "Vectors are NOT equal!\n";
            std::cout << "bit_by_bit_dt:  ";
            for (auto v : bit_by_bit_dt) std::cout << (int)v << ' ';
            std::cout << "\nchaining_64_dt: ";
            for (auto v : chaining_64_dt) std::cout << (int)v << ' ';
            std::cout << '\n';
        }

        chaining_u128(packaging_params);
        std::vector<uint32_t> chaining_128_dt = packaging_params.words;

        if (!std::equal(bit_by_bit_dt.begin(), bit_by_bit_dt.end(), chaining_128_dt.begin())) {
            std::cout << "Vectors are NOT equal!\n";
            std::cout << "bit_by_bit_dt:  ";
            for (auto v : bit_by_bit_dt) std::cout << (int)v << ' ';
            std::cout << "\nchaining_128_dt: ";
            for (auto v : chaining_128_dt) std::cout << (int)v << ' ';
            std::cout << '\n';
        }

    #ifndef IS_LITTLE_ENDIAN

        chaining_u64_big(packaging_params);
        std::vector<uint32_t> chaining_u64_big_dt = packaging_params.words;

        if (!std::equal(bit_by_bit_dt.begin(), bit_by_bit_dt.end(), chaining_u64_big_dt.begin())) {
            std::cout << "Vectors are NOT equal!\n";
            std::cout << "bit_by_bit_dt:  ";
            for (auto v : bit_by_bit_dt) std::cout << (int)v << ' ';
            std::cout << "\nchaining_u64_big_dt: ";
            for (auto v : chaining_u64_big_dt) std::cout << (int)v << ' ';
            std::cout << '\n';
        }

        chaining_u128_big(packaging_params);
        std::vector<uint32_t> chaining_u128_big = packaging_params.words;
        
        if (!std::equal(bit_by_bit_dt.begin(), bit_by_bit_dt.end(), chaining_u128_big.begin())) {
            std::cout << "Vectors are NOT equal!\n";
            std::cout << "bit_by_bit_dt:  ";
            for (auto v : bit_by_bit_dt) std::cout << (int)v << ' ';
            std::cout << "\nchaining_u128_big: ";
            for (auto v : chaining_u128_big) std::cout << (int)v << ' ';
            std::cout << '\n';
        }

    #endif

    }
#endif
}
