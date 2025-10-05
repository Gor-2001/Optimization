/***************************************/
// base_window.cpp
/***************************************/
#include "base_window.h"
/***************************************/

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

void 
BaseWindow::setSpinVariableValues(const std::vector<uint16_t>& values) {

    spinVariableDefValues = std::vector<uint16_t> (spinVariablesCount);

    for(uint16_t i = 0; i < values.size(); ++i)
        spinVariableDefValues[i] = values[i];
}

std::vector<uint16_t> 
BaseWindow::getSpinVariableValues() const
{
    std::vector<uint16_t> values;
    values.reserve(spinVariables.size());

    for (const auto* spin : spinVariables)
    {
        if (spin)
            values.push_back(static_cast<uint16_t>(spin->value()));
    }

    return values;
}

void
BaseWindow::drawSpinVariableButtons() {

    auto *paramsLayout = new QHBoxLayout();

    for(uint16_t i = 0; i < spinVariablesCount; ++i)
        spinVariables[i] = addLabeledSpinBox(paramsLayout, QString::fromStdString(spinVariableNames[i]), spinVariableDefValues[i], this);

    mainLayout->addLayout(paramsLayout);
}

QSpinBox* 
BaseWindow::addLabeledSpinBox(
    QBoxLayout* layout,
    const QString& labelText,
    int defaultValue,
    QWidget* parent,
    uint16_t min,
    uint16_t max
) 
{
    auto* label = new QLabel(labelText, parent);
    auto* spin  = new QSpinBox(parent);

    spin->setRange(min, max);
    spin->setValue(defaultValue);

    layout->addWidget(label);
    layout->addWidget(spin);

    return spin;
}

void 
BaseWindow::setInfoTitle(const std::string& info_title) {
    infoTitle = std::move(info_title);
}

void 
BaseWindow::setInfoPath(const std::string& info_path) {
    infoPath = std::move(info_path);
}

void BaseWindow::drawInfoButton() {

    openButton = new QPushButton("Open Info Window", this);
    mainLayout->addWidget(openButton);

    connect(openButton, &QPushButton::clicked, this, [this]() {
        // Create a new dialog window
        QDialog* infoDialog = new QDialog(this);
        infoDialog->setWindowTitle(QString::fromStdString(infoTitle));
        infoDialog->resize(WINDOW_WIDTH, WINDOW_HEIGHT);

        QVBoxLayout* layout = new QVBoxLayout(infoDialog);

        QTextEdit* textBox = new QTextEdit(infoDialog);
        textBox->setReadOnly(true);
        layout->addWidget(textBox);

        // Load file content if path is provided
        if (!infoPath.empty()) {
            QFile file(QString::fromStdString(infoPath));
            QFileInfo fi(file);

            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                textBox->setPlainText(in.readAll());
            } else {
                QString errMsg = "Failed to open file:\n" + fi.absoluteFilePath()
                                 + "\nReason: " + file.errorString();
                textBox->setPlainText(errMsg);
                qDebug() << errMsg;
            }
        }

        infoDialog->exec(); // show as modal window
    });
}

void 
BaseWindow::setRunTitle(const std::string& run_title) {
    runTitle = std::move(run_title);
}

void 
BaseWindow::drawRunButton() {

    runButton = new QPushButton(QString::fromStdString(runTitle), this);
    mainLayout->addWidget(runButton);
}

void 
BaseWindow::drawOutputBox() {

    outputBox = new QTextEdit(this);
    outputBox->setReadOnly(true);

    mainLayout->addWidget(outputBox);
}

void BaseWindow::setupWindow() {

    setCentralWidget(central);
    resize(WINDOW_WIDTH, WINDOW_HEIGHT);
    connect(runButton, &QPushButton::clicked, this, &BaseWindow::runTest);
}

void 
BaseWindow::setTestCount(const uint16_t test_count) {
    testCount = test_count;
}

void 
BaseWindow::setRunCount(const uint16_t run_count) {
    runCount = run_count;
}

void 
BaseWindow::setRunCountIndex(const uint16_t run_count_index) {
    runCountIndex = run_count_index;
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

    high_resolution_clock::time_point start;
    high_resolution_clock::time_point stop;

    std::vector<uint16_t> spinVariables = getSpinVariableValues();
    setRunCount(spinVariables[runCountIndex]);
    runInit(spinVariables);

    for(uint16_t i = 0; i < testCount; ++i)
    {
        microseconds duration{0};

        for(uint16_t j = 0; j < runCount; ++j)
        {
            runGen();
            start = high_resolution_clock::now();
            runSubTest(i);
            stop = high_resolution_clock::now();
            duration += duration_cast<microseconds>(stop - start);
        }

        printToOutput(
            outputBox, 
            QString("%1 : %2 microseconds")
            .arg(QString::fromStdString(testNames[i]))
            .arg(duration.count(), 10)
        );
    }
}

void
BaseWindow::printToOutput(
    QTextEdit* outputBox,
    const QString& text
)
{
    if (!outputBox)
        return;

    outputBox->append(text);
    qDebug() << text;
}

std::vector<uint16_t> 
BaseWindow::random_sample_generation(
    uint16_t vector_size,
    uint16_t range
)
{
    std::vector<uint16_t> result(vector_size, 0);

    for (auto& it : result)
        it = static_cast<uint16_t>(rand() % range);

    return result;
}