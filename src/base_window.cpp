// base_window.cpp
#include "base_window.h"

BaseWindow::BaseWindow(QWidget* parent)
    : QMainWindow(parent), central(nullptr), mainLayout(nullptr),
      runButton(nullptr), openButton(nullptr),
      spinVariablesCount(0){}

void 
BaseWindow::setCenter() {
    central = new QWidget(this);
}

void 
BaseWindow::setMainLayout() {
    mainLayout = new QVBoxLayout(central);
}

void 
BaseWindow::setSpinVariablesCount(uint16_t size) {
    spinVariablesCount = size;
}

void 
BaseWindow::setSpinVariables() {
    spinVariables = std::vector<QSpinBox*> (spinVariablesCount);
}

void 
BaseWindow::setSpinVariableNames(const std::vector<std::string>& names) {
    spinVariableNames = std::vector<std::string> (spinVariablesCount);

    for (uint16_t i = 0; i < names.size(); ++i)
        spinVariableNames[i] = names[i];
}

void BaseWindow::setSpinVariableDefValues(const std::vector<uint16_t>& values) {

    spinVariableDefValues = std::vector<uint16_t> (spinVariablesCount);

    for(uint16_t i = 0; i < values.size(); ++i)
        spinVariableDefValues[i] = values[i];
}

void 
BaseWindow::setInfoTitle(const std::string& info_title) {
    infoTitle = std::move(info_title);
}

void 
BaseWindow::setInfoPath(const std::string& info_path) {
    infoPath = std::move(info_path);
}

void 
BaseWindow::setRunTitle(const std::string& run_title) {
    runTitle = std::move(run_title);
}

void 
BaseWindow::drawInfoButton() {
    // Button to open Info Window
    openButton = new QPushButton("Open Info Window", this);
    mainLayout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, [this]() {
        InfoWindow* info = new InfoWindow(
            QString::fromStdString(this->infoTitle),
            QString::fromStdString(this->infoPath),
            this
        );
        info->show();
    });
}

void
BaseWindow::drawSpinVariableButtons() {

    auto *paramsLayout = new QHBoxLayout();

    for(uint16_t i = 0; i < spinVariablesCount; ++i)
        spinVariables[i] = addLabeledSpinBox(paramsLayout, QString::fromStdString(spinVariableNames[i]), spinVariableDefValues[i], this);

    mainLayout->addLayout(paramsLayout);
}

void 
BaseWindow::drawRunButton() {

    runButton = new QPushButton(QString::fromStdString(runTitle), this);
    mainLayout->addWidget(runButton);
}

void 
BaseWindow::drawOutputBox() {
    // Create and configure the output box
    outputBox = new QTextEdit(this);
    outputBox->setReadOnly(true);

    // Add it to the main layout
    mainLayout->addWidget(outputBox);
}

void BaseWindow::setupWindow() {
    // Set central widget only ONCE
    setCentralWidget(central);

    // Make window larger by default
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Connect the run button to its slot
    connect(runButton, &QPushButton::clicked, this, &BaseWindow::runTest);
}

void 
BaseWindow::setTestCount(const uint16_t test_count) {
    testCount = test_count;
}

void 
BaseWindow::setTestNames(const std::vector<std::string>& test_names) {

    testNames = std::vector<std::string> (testCount);

    for (uint16_t i = 0; i < testCount; ++i)
        testNames[i] = test_names[i];
}

void 
BaseWindow::runTest()
{
    std::chrono::microseconds duration{0};

    for(uint16_t i = 0; i < testCount; ++i)
    {
        printToOutput(
            outputBox, 
            QString("%1 : %2 microseconds")
            .arg(QString::fromStdString(testNames[i]))
            .arg(duration.count(), 10)
        );
    }
}


