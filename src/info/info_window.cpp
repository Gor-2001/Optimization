#include <QVBoxLayout>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

#include "info_window.h"
#include "../define.h"

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

