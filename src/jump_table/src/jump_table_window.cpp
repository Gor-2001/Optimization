// jump_table_window.cpp

#include "../inc/jump_table_window.h"

JumpTableWindow::JumpTableWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);  // only ONE main layout

    // Button to open Info Window
    auto openButton = new QPushButton("Open Info Window", this);
    mainLayout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, [this]() {
        InfoWindow *info = new InfoWindow("Jump Table Test Info",
                                          "src/jump_table/jump_table_info",
                                          this);
        info->show();
    });

    // Spin boxes layout
    auto *paramsLayout = new QHBoxLayout();

    // DATA_SIZE
    spinDataSize = addLabeledSpinBox0(paramsLayout, "DATA_SIZE:", DATA_SIZE, this);

    // RUN_COUNT
    spinRunCount = addLabeledSpinBox0(paramsLayout, "RUN_COUNT:", RUN_COUNT, this);

    mainLayout->addLayout(paramsLayout);

    // Run Test button
    runButton = new QPushButton("Run Jump Table Test", this);
    mainLayout->addWidget(runButton);

    // Output box
    outputBox = new QTextEdit(this);
    outputBox->setReadOnly(true);
    mainLayout->addWidget(outputBox);

    // Set central widget only ONCE
    setCentralWidget(central);

    // Make window larger by default
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    connect(runButton, &QPushButton::clicked, this, &JumpTableWindow::runTest);
}

// Run Prediction test
void JumpTableWindow::runTest()
{

    uint16_t data_size;
    uint16_t run_count;

    // Update global parameters from UI
    data_size = static_cast<uint16_t>(spinDataSize->value());
    run_count = static_cast<uint16_t>(spinRunCount->value());
    microseconds duration{0};

    duration = jump_table_test(jump_table_test_switch, data_size, DATA_RANGE, run_count);
    printToOutput0(
        outputBox,
        QString("%1 : %2 microseconds")
        .arg("SWITCH\t")
        .arg(duration.count(), 10)
    );
    
    duration = jump_table_test(jump_table_test_ifelse, data_size, DATA_RANGE, run_count);
    printToOutput0(
        outputBox,
        QString("%1 : %2 microseconds")
        .arg("IFELSE\t")
        .arg(duration.count(), 10)
    );
}

