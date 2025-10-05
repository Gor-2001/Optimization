/***************************************/
// prediction_window.cpp
/***************************************/
#include "jump_table_window.h"
/***************************************/

JumpTableWindow::JumpTableWindow(QWidget *parent)
    : BaseWindow(parent)
{
    // Variables that may change during execution (mutable, e.g., loop/spine-related)
    const uint16_t runCount    = 100;
    const uint16_t sampleSize  = 256;

    // Variables that remain constant (immutable, not related to loop/spines)
    const uint16_t sampleRange = 32;

    const uint8_t  spinCount    = 2; 
    const uint8_t  testCount    = 2;

    setCenter();
    setMainLayout();

    setSpinVariablesCount(spinCount);
    setSpinVariables();

    setSpinVariableNames({
        "Run Count",
        "Sample Size"
    });

    setSpinVariableDefValues({
        runCount, 
        sampleSize
    });

    jump_table_params_t jump_table_params;
    jump_table_params_init(jump_table_params, sampleSize, sampleRange);
    setParam(jump_table_params);
    setGenFunction<jump_table_params_t>(JumpTableWindow::sample_gen);
    setRunCount(runCount);

    setInfoTitle("Jump Table Test Info");
    setInfoPath("src/jump_table/jump_table_info");
    setRunTitle("Run Jump Table Test");

    drawInfoButton();
    drawSpinVariableButtons();
    drawRunButton();
    drawOutputBox();

    setTestCount(testCount);
    setTestNames({"IFELSE\t", "SWITCH\t"});

    setSubTestFunctions<jump_table_params_t>
        ({JumpTableWindow::test_ifelse, JumpTableWindow::test_switch});

    setupWindow();
}

void 
JumpTableWindow::jump_table_params_init(
    jump_table_params_t& jump_table_params, 
    const uint16_t sample_size,
    const uint16_t sample_range
)
{
    jump_table_params.sample_size = sample_size;
    jump_table_params.sample_range = sample_range;
}

void 
JumpTableWindow::sample_gen(
    jump_table_params_t& jump_table_params
)
{
    BaseWindow bw;

    jump_table_params.sample = 
        bw.random_sample_generation(jump_table_params.sample_size, jump_table_params.sample_range);
}

void 
JumpTableWindow::test_ifelse(    
    jump_table_params_t& jump_table_params
)
{
    std::vector<uint16_t> count(jump_table_params.sample_size, 0);

    for(uint16_t i = 0; i < jump_table_params.sample_size; ++i)
    {
        if (jump_table_params.sample[i] == 17) {
            ++count[17];
        }
        else if (jump_table_params.sample[i] == 3) {
            ++count[3];
        }
        else if (jump_table_params.sample[i] == 29) {
            ++count[29];
        }
        else if (jump_table_params.sample[i] == 0) {
            ++count[0];
        }
        else if (jump_table_params.sample[i] == 11) {
            ++count[11];
        }
        else if (jump_table_params.sample[i] == 24) {
            ++count[24];
        }
        else if (jump_table_params.sample[i] == 8) {
            ++count[8];
        }
        else if (jump_table_params.sample[i] == 5) {
            ++count[5];
        }
        else if (jump_table_params.sample[i] == 14) {
            ++count[14];
        }
        else if (jump_table_params.sample[i] == 1) {
            ++count[1];
        }
        else if (jump_table_params.sample[i] == 20) {
            ++count[20];
        }
        else if (jump_table_params.sample[i] == 26) {
            ++count[26];
        }
        else if (jump_table_params.sample[i] == 9) {
            ++count[9];
        }
        else if (jump_table_params.sample[i] == 31) {
            ++count[31];
        }
        else if (jump_table_params.sample[i] == 6) {
            ++count[6];
        }
        else if (jump_table_params.sample[i] == 18) {
            ++count[18];
        }
        else if (jump_table_params.sample[i] == 2) {
            ++count[2];
        }
        else if (jump_table_params.sample[i] == 22) {
            ++count[22];
        }
        else if (jump_table_params.sample[i] == 30) {
            ++count[30];
        }
        else if (jump_table_params.sample[i] == 15) {
            ++count[15];
        }
        else if (jump_table_params.sample[i] == 7) {
            ++count[7];
        }
        else if (jump_table_params.sample[i] == 12) {
            ++count[12];
        }
        else if (jump_table_params.sample[i] == 21) {
            ++count[21];
        }
        else if (jump_table_params.sample[i] == 10) {
            ++count[10];
        }
        else if (jump_table_params.sample[i] == 4) {
            ++count[4];
        }
        else if (jump_table_params.sample[i] == 16) {
            ++count[16];
        }
        else if (jump_table_params.sample[i] == 19) {
            ++count[19];
        }
        else if (jump_table_params.sample[i] == 28) {
            ++count[28];
        }
        else if (jump_table_params.sample[i] == 23) {
            ++count[23];
        }
        else if (jump_table_params.sample[i] == 25) {
            ++count[25];
        }
        else if (jump_table_params.sample[i] == 27) {
            ++count[27];
        }
        else if (jump_table_params.sample[i] == 13) {
            ++count[13];
        }
        else {
            // do nothing
        }
    }
}

void 
JumpTableWindow::test_switch(    
    jump_table_params_t& jump_table_params
)
{
    std::vector<uint16_t> count(jump_table_params.sample_range, 0);

    for(uint16_t i = 0; i < jump_table_params.sample_size; ++i)
    {
        switch (jump_table_params.sample[i])
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

