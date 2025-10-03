// info_window.h

#ifndef INFO_WINDOW_H
#define INFO_WINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QDebug>
#include <QMainWindow>
#include <QTextEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QApplication>
#include <QFile>
#include <QFileInfo>

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

class InfoWindow : public QMainWindow {
    Q_OBJECT
public:
    // constructor with title and optional file path
    explicit InfoWindow(const QString &title,
                        const QString &filePath = QString(),
                        QWidget *parent = nullptr);

private:
    QTextEdit *outputBox;
};

QSpinBox* addLabeledSpinBox(
    QBoxLayout* layout,
    const QString& labelText,
    int defaultValue,
    QWidget* parent,
    uint16_t min = 1,
    uint16_t max = 65535
);

#endif // INFO_WINDOW_H
