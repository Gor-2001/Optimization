// info_window.cpp

#include "info_window.h"

InfoWindow::InfoWindow(const QString &title,
                       const QString &filePath,
                       QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(title);
    setMinimumSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);

    outputBox = new QTextEdit(this);
    outputBox->setReadOnly(true);
    layout->addWidget(outputBox);

    // if file path provided, load file content
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        QFileInfo fi(file);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            outputBox->setPlainText(in.readAll());
        } else {
            QString errMsg = "Failed to open file:\n" + fi.absoluteFilePath()
                            + "\nReason: " + file.errorString();
            outputBox->setPlainText(errMsg);

            // also log to console
            qDebug() << errMsg;
        }
    }

    setCentralWidget(central);
}

QSpinBox* 
addLabeledSpinBox(
    QBoxLayout* layout,
    const QString& labelText,
    int defaultValue,
    QWidget* parent,
    uint16_t min,
    uint16_t max
) {
    auto* label = new QLabel(labelText, parent);
    auto* spin  = new QSpinBox(parent);

    spin->setRange(min, max);
    spin->setValue(defaultValue);

    layout->addWidget(label);
    layout->addWidget(spin);

    return spin;
}

void
printToOutput(
    QTextEdit* outputBox,
    const QString& text
)
{
    if (!outputBox)
        return;

    outputBox->append(text);
    qDebug() << text;
}

