// base_window.h

#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H

#include "info/info_window.h"

class QPushButton;

class BaseWindow : public QMainWindow {
    Q_OBJECT
public:
    BaseWindow(QWidget *parent = nullptr);

    void setCenter();
    void setMainLayout();

    void setSpinVariablesCount(uint16_t size);
    void setSpinVariables();
    void setSpinVariableNames(const std::vector<std::string>& names);
    void setSpinVariableDefValues(const std::vector<uint16_t>& values);

    void setInfoTitle(const std::string& info_title);
    void setInfoPath(const std::string& info_path);
    void setRunTitle(const std::string& run_title);

    void setTestCount(const uint16_t test_count);
    void setTestNames(const std::vector<std::string>& test_names);
    
    void drawInfoButton();
    void drawSpinVariableButtons();
    void drawRunButton();
    void drawOutputBox();
    void setupWindow();

private slots:
    void runTest();

private:

    QPushButton *runButton;
    QPushButton *openButton;
    QTextEdit   *outputBox;

    QWidget *central;
    QVBoxLayout *mainLayout;

    uint16_t spinVariablesCount;
    std::vector<QSpinBox*> spinVariables;
    std::vector<std::string> spinVariableNames;
    std::vector<uint16_t> spinVariableDefValues;
    std::string infoTitle;
    std::string infoPath;
    std::string runTitle;

    uint16_t testCount;
    std::vector<std::string> testNames;

};

#endif // BASE_WINDOW_H
