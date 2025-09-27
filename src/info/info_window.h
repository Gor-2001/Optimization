// info_window.h

#ifndef INFO_WINDOW_H
#define INFO_WINDOW_H

#include <QMainWindow>
#include <QTextEdit>

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
