// jump_table_test.cpp

#include "../inc/jump_table_test.h"

void jump_table_switch(    
    const JT_params_t JT_params, 
    const std::vector<uint8_t>& data,
    std::vector<uint8_t>& count
)
{
    for(uint16_t i = 0; i < JT_params.vector_size; ++i)
    {
        switch (data[i])
        {
        case 0:
            ++count[0];
            break;
        case 1:
            ++count[1];
            break;
        case 2:
            ++count[2];
            break;
        case 3:
            ++count[3];
            break;
        case 4:
            ++count[4];
            break;
        case 5:
            ++count[5];
            break;
        case 6:
            ++count[6];
            break;
        case 7:
            ++count[7];
            break;
        case 8:
            ++count[8];
            break;
        case 9:
            ++count[9];
            break;
        case 10:
            ++count[10];
            break;
        case 11:
            ++count[11];
            break;
        case 12:
            ++count[12];
            break;
        case 13:
            ++count[13];
            break;
        case 14:
            ++count[14];
            break;
        case 15:
            ++count[15];
            break;
        case 16:
            ++count[16];
            break;
        case 17:
            ++count[17];
            break;
        case 18:
            ++count[18];
            break;
        case 19:
            ++count[19];
            break;
        case 20:
            ++count[20];
            break;
        case 21:
            ++count[21];
            break;
        case 22:
            ++count[22];
            break;
        case 23:
            ++count[23];
            break;
        case 24:
            ++count[24];
            break;
        case 25:
            ++count[25];
            break;
        case 26:
            ++count[26];
            break;
        case 27:
            ++count[27];
            break;
        case 28:
            ++count[28];
            break;
        case 29:
            ++count[29];
            break;
        case 30:
            ++count[30];
            break;
        case 31:
            ++count[31];
            break;
        default:
            break;
        }
    }
}

void jump_table_ifelse(
    const JT_params_t JT_params, 
    const std::vector<uint8_t>& data,
    std::vector<uint8_t>& count
)
{
    for(uint16_t i = 0; i < JT_params.vector_size; ++i)
    {
        if (data[i] == 17) {
            ++count[17];
        }
        else if (data[i] == 3) {
            ++count[3];
        }
        else if (data[i] == 29) {
            ++count[29];
        }
        else if (data[i] == 0) {
            ++count[0];
        }
        else if (data[i] == 11) {
            ++count[11];
        }
        else if (data[i] == 24) {
            ++count[24];
        }
        else if (data[i] == 8) {
            ++count[8];
        }
        else if (data[i] == 5) {
            ++count[5];
        }
        else if (data[i] == 14) {
            ++count[14];
        }
        else if (data[i] == 1) {
            ++count[1];
        }
        else if (data[i] == 20) {
            ++count[20];
        }
        else if (data[i] == 26) {
            ++count[26];
        }
        else if (data[i] == 9) {
            ++count[9];
        }
        else if (data[i] == 31) {
            ++count[31];
        }
        else if (data[i] == 6) {
            ++count[6];
        }
        else if (data[i] == 18) {
            ++count[18];
        }
        else if (data[i] == 2) {
            ++count[2];
        }
        else if (data[i] == 22) {
            ++count[22];
        }
        else if (data[i] == 30) {
            ++count[30];
        }
        else if (data[i] == 15) {
            ++count[15];
        }
        else if (data[i] == 7) {
            ++count[7];
        }
        else if (data[i] == 12) {
            ++count[12];
        }
        else if (data[i] == 21) {
            ++count[21];
        }
        else if (data[i] == 10) {
            ++count[10];
        }
        else if (data[i] == 4) {
            ++count[4];
        }
        else if (data[i] == 16) {
            ++count[16];
        }
        else if (data[i] == 19) {
            ++count[19];
        }
        else if (data[i] == 28) {
            ++count[28];
        }
        else if (data[i] == 23) {
            ++count[23];
        }
        else if (data[i] == 25) {
            ++count[25];
        }
        else if (data[i] == 27) {
            ++count[27];
        }
        else if (data[i] == 13) {
            ++count[13];
        }
        else {
            // do nothing
        }
    }
}