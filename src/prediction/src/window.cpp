#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>

#include "../inc/test.h"
#include "../inc/window.h"
#include "../../info/info_window.h"
#include "../../define.h"

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
    spinRange->setValue(NUMBERS_RANGE);  // probably you meant NUMBERS_RANGE instead of RUN_COUNT
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
    uint16_t vector_size;
    uint16_t numbers_range;
    uint16_t run_count;

    // Update global parameters from UI
    vector_size = static_cast<uint16_t>(spinVectorSize->value());
    separators_count = static_cast<uint16_t>(spinSeparators->value());
    run_count = static_cast<uint16_t>(spinRunCount->value());
    numbers_range = static_cast<uint16_t>(spinRunCount->value());

    //outputBox->clear();

    auto start_unsorted = std::chrono::high_resolution_clock::now();
    for(uint16_t i = 0; i < run_count; ++i)
        prediction_test_unsorted(separators_count, numbers_range, vector_size);

    auto stop_unsorted = std::chrono::high_resolution_clock::now();
    auto duration_unsorted = std::chrono::duration_cast<std::chrono::microseconds>(stop_unsorted - start_unsorted);

    printResult(QString("%1 : %2 microseconds")
        .arg("UNSORTED\t")
        .arg(duration_unsorted.count(), 10)
    );

    auto start_sorted = std::chrono::high_resolution_clock::now();
    for(uint16_t i = 0; i < run_count; ++i)
        prediction_test_sorted(separators_count, numbers_range, vector_size);

    auto stop_sorted = std::chrono::high_resolution_clock::now();
    auto duration_sorted = std::chrono::duration_cast<std::chrono::microseconds>(stop_sorted - start_sorted);

    printResult(QString("%1 : %2 microseconds")
        .arg("SORTED\t")
        .arg(duration_sorted.count(), 10)
    );
}

