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

#include "../main_utils.h"

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

#endif // INFO_WINDOW_H
