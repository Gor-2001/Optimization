// prediction_window.cpp
#include "../inc/prediction_window.h"
#include "../inc/prediction_test.h"

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

    // VECTOR_SIZE
    auto *labelVectorSize = new QLabel("VECTOR_SIZE:", this);
    spinVectorSize = new QSpinBox(this);
    spinVectorSize->setRange(1, 65536);
    spinVectorSize->setValue(VECTOR_SIZE);  // default
    paramsLayout->addWidget(labelVectorSize);
    paramsLayout->addWidget(spinVectorSize);

    // SEPARATORS_COUNT
    auto *labelSeparators = new QLabel("SEPARATORS_COUNT:", this);
    spinSeparators = new QSpinBox(this);
    spinSeparators->setRange(1, 65536);
    spinSeparators->setValue(SEPARATORS_COUNT);  // default
    paramsLayout->addWidget(labelSeparators);
    paramsLayout->addWidget(spinSeparators);

    // RUN_COUNT
    auto *labelRunCount = new QLabel("RUN_COUNT:", this);
    spinRunCount = new QSpinBox(this);
    spinRunCount->setRange(1, 65536);
    spinRunCount->setValue(RUN_COUNT);  // default
    paramsLayout->addWidget(labelRunCount);
    paramsLayout->addWidget(spinRunCount);

    // NUMBERS_RANGE
    auto *labelRange = new QLabel("NUMBERS_RANGE:", this);
    spinRange = new QSpinBox(this);
    spinRange->setRange(1, 65536);
    spinRange->setValue(RANGE);  // probably you meant NUMBERS_RANGE instead of RUN_COUNT
    paramsLayout->addWidget(labelRange);
    paramsLayout->addWidget(spinRange);

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


// Helper: print to both QTextEdit and console
void PredictionWindow::printResult(const QString &text)
{
    outputBox->append(text);
    qDebug() << text;
}

// Run Prediction test
void PredictionWindow::runTest()
{
    uint16_t separators_count;
    uint16_t data_size;
    uint16_t range;
    uint16_t run_count;

    // Update global parameters from UI
    data_size = static_cast<uint16_t>(spinVectorSize->value());
    separators_count = static_cast<uint16_t>(spinSeparators->value());
    run_count = static_cast<uint16_t>(spinRunCount->value());
    range = static_cast<uint16_t>(spinRunCount->value());
    microseconds duration{0};

    duration = prediction_test(prediction_test_unsorted, data_size, separators_count, range, run_count);
    printResult(QString("%1 : %2 microseconds")
        .arg("UNSORTED\t")
        .arg(duration.count(), 10)
    );

    duration = prediction_test(prediction_test_sorted, data_size, separators_count, range, run_count);
    printResult(QString("%1 : %2 microseconds")
        .arg("SORTED\t")
        .arg(duration.count(), 10)
    );
}

