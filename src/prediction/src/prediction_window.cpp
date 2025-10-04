// prediction_window.cpp
#include "../inc/prediction_window.h"

PredictionWindow::PredictionWindow(QWidget *parent)
    : BaseWindow(parent)
{
    setCenter();
    setMainLayout();

    setSpinVariablesCount(4);
    setSpinVariables();

    setSpinVariableNames({
        "DATA_SIZE",
        "SEPARATORS_COUNT",
        "RUN_COUNT",
        "DATA_RANGE"
    });

    setSpinVariableDefValues({
        DATA_SIZE, 
        SEPARATORS_COUNT_PRED,
        RUN_COUNT,
        DATA_RANGE
    });

    setInfoTitle("Prediction Test Info");
    setInfoPath("src/prediction/prediction_info");
    setRunTitle("Run Prediction Test");

    drawInfoButton();
    drawSpinVariableButtons();
    drawRunButton();
    drawOutputBox();

    setTestCount(2);
    setTestNames({"UNSORTED\t", "SORTED\t"});
    setupWindow();
}

