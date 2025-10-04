// prediction_window.cpp
#include "../inc/prediction_window.h"

PredictionWindow::PredictionWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);  // only ONE main layout

    // Button to open Info Window
    QPushButton *openButton = new QPushButton("Open Info Window", this);
    mainLayout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, [this]() {
        InfoWindow *info = new InfoWindow("Prediction Test Info",
                                          "src/prediction/prediction_info",
                                          this);
        info->show();
    });

    // Spin boxes layout
    auto *paramsLayout = new QHBoxLayout();

    // Use the helper instead of repeating code
    spinDataSize   = addLabeledSpinBox(paramsLayout, "DATA_SIZE:",        DATA_SIZE, this);
    spinSeparators = addLabeledSpinBox(paramsLayout, "SEPARATORS_COUNT:", SEPARATORS_COUNT_PRED, this);
    spinRunCount   = addLabeledSpinBox(paramsLayout, "RUN_COUNT:",        RUN_COUNT, this);
    spinRange      = addLabeledSpinBox(paramsLayout, "DATA_RANGE:",       DATA_RANGE, this);

    mainLayout->addLayout(paramsLayout);

    // Run Test button
    runButton = new QPushButton("Run Prediction Test", this);
    mainLayout->addWidget(runButton);

    // Output box
    outputBox = new QTextEdit(this);
    outputBox->setReadOnly(true);
    mainLayout->addWidget(outputBox);

    // Set central widget only ONCE
    setCentralWidget(central);

    // Make window larger by default
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    connect(runButton, &QPushButton::clicked, this, &PredictionWindow::runTest);
}

// Run Prediction test
void PredictionWindow::runTest()
{
    uint16_t separators_count;
    uint16_t data_size;
    uint16_t range;
    uint16_t run_count;

    // Update global parameters from UI
    data_size = static_cast<uint16_t>(spinDataSize->value());
    separators_count = static_cast<uint16_t>(spinSeparators->value());
    run_count = static_cast<uint16_t>(spinRunCount->value());
    range = static_cast<uint16_t>(spinRunCount->value());
    microseconds duration{0};

    duration = prediction_test(prediction_test_unsorted, data_size, separators_count, range, run_count);
    printToOutput(
        outputBox, 
        QString("%1 : %2 microseconds")
        .arg("UNSORTED\t")
        .arg(duration.count(), 10)
    );

    duration = prediction_test(prediction_test_sorted, data_size, separators_count, range, run_count);
    printToOutput(
        outputBox, 
        QString("%1 : %2 microseconds")
        .arg("SORTED\t")
        .arg(duration.count(), 10)
    );
}

