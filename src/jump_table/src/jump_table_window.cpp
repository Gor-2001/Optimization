// jump_table_window.cpp

#include "../inc/jump_table_window.h"
#include "../inc/jump_table_test.h"


JTWindow::JTWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto *central = new QWidget(this);
    auto *mainLayout = new QVBoxLayout(central);  // only ONE main layout

    // Button to open Info Window
    QPushButton *openButton = new QPushButton("Open Info Window", this);
    mainLayout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, [this]() {
        InfoWindow *info = new InfoWindow("Jump Table Test Info",
                                        "src/jump_table/jump_table_info",
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

    // RUN_COUNT
    auto *labelRunCount = new QLabel("RUN_COUNT:", this);
    spinRunCount = new QSpinBox(this);
    spinRunCount->setRange(1, 65536);
    spinRunCount->setValue(RUN_COUNT);  // default
    paramsLayout->addWidget(labelRunCount);
    paramsLayout->addWidget(spinRunCount);

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

    connect(runButton, &QPushButton::clicked, this, &JTWindow::runTest);
}

// Helper: print to both QTextEdit and console
void JTWindow::printResult(const QString &text)
{
    outputBox->append(text);
    qDebug() << text;
}

// Run Prediction test
void JTWindow::runTest()
{
    uint16_t vector_size;
    uint16_t run_count;

    // Update global parameters from UI
    vector_size = static_cast<uint16_t>(spinVectorSize->value());
    run_count = static_cast<uint16_t>(spinRunCount->value());

    //outputBox->clear();

    JT_params_t JT_params = {vector_size, run_count, SEPARATORS_COUNT};

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;
    microseconds duration{0};

    std::vector<uint8_t> data; 
    std::vector<uint8_t> count =
        random_vector_generation(JT_params.vector_size, JT_params.separators_count);

    for(uint16_t i = 0; i < run_count; ++i)
    {
        data = 
            random_vector_generation(JT_params.vector_size, JT_params.separators_count);
        
        start = high_resolution_clock::now();
        jump_table_switch(JT_params, data, count);
        stop = high_resolution_clock::now();
        duration += duration_cast<microseconds>(stop - start);
    }

    printResult(QString("%1 : %2 microseconds")
        .arg("SWITCH\t")
        .arg(duration.count(), 10)
    );

    for(uint16_t i = 0; i < run_count; ++i)
    {
        data = 
            random_vector_generation(JT_params.vector_size, JT_params.separators_count);
        
        start = high_resolution_clock::now();
        jump_table_ifelse(JT_params, data, count);
        stop = high_resolution_clock::now();
        duration += duration_cast<microseconds>(stop - start);
    }

    printResult(QString("%1 : %2 microseconds")
        .arg("IFELSE\t")
        .arg(duration.count(), 10)
    );
}

