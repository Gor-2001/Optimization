/***************************************/
// base_window.h
/***************************************/
#ifndef BASE_WINDOW_H
#define BASE_WINDOW_H
/***************************************/
#include <vector>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <memory>
#include <any>
/***************************************/
#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QApplication>
#include <QSpinBox>
#include <QString>
/***************************************/
using namespace std::chrono;
/***************************************/
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600
/***************************************/

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
    void setSpinVariableValues(const std::vector<uint16_t>& values);
    std::vector<uint16_t> getSpinVariableValues() const;

    void setInfoTitle(const std::string& info_title);
    void setInfoPath(const std::string& info_path);
    void setRunTitle(const std::string& run_title);

    void setTestCount(const uint16_t test_count);
    void setRunCount(const uint16_t run_count);
    void setRunCountIndex(const uint16_t run_count_index);
    void setTestNames(const std::vector<std::string>& test_names);

    void drawInfoButton();
    void drawSpinVariableButtons();
    void drawRunButton();
    void drawOutputBox();
    void setupWindow();

    std::vector<uint16_t> 
    random_sample_generation(
        uint16_t vector_size,
        uint16_t range
    );

    template <typename T>
    void setParam(const T& param) {
        data = param;
    }

    template <typename T>
    void setInitFunction(const std::function<void(T&, const std::vector<uint16_t>&)>& f)
    {
        // Wrap type-safe function into a std::any-compatible version
        initFunc = [f](std::any& a, const std::vector<uint16_t>& values)
        {
            f(std::any_cast<T&>(a), values);
        };
    }

    template <typename T>
    void setGenFunction(const std::function<void(T&)>& f) {
        // Wrap f to work with std::any
        genFunc = [f](std::any& a) {
            f(std::any_cast<T&>(a));
        };
    }

    template <typename T>
    void setSubTestFunctions(const std::vector<std::function<void(T&)>>& funcs) {
        subTestFunc.clear();
        subTestFunc.reserve(funcs.size());

        for (auto& f : funcs) {
            subTestFunc.push_back([f](std::any& a) {
                f(std::any_cast<T&>(a));
            });
        }
    }


private slots:
    void runTest();

private:

    QPushButton *runButton;
    QPushButton *openButton;
    QTextEdit   *outputBox;

    QWidget     *central;
    QVBoxLayout *mainLayout;

    uint16_t spinVariablesCount;
    std::vector<QSpinBox*> spinVariables;
    std::vector<std::string> spinVariableNames;
    std::vector<uint16_t> spinVariableDefValues;
    std::string infoTitle;
    std::string infoPath;
    std::string runTitle;

    uint16_t testCount;
    uint16_t runCount;
    uint16_t runCountIndex;
    std::vector<std::string> testNames;

    void printToOutput(QTextEdit* outputBox, const QString& text);

    QSpinBox* addLabeledSpinBox(
        QBoxLayout* layout,
        const QString& labelText,
        int defaultValue,
        QWidget* parent,
        uint16_t min = 1,
        uint16_t max = 65535
    );

    std::any data;
    std::function<void(std::any&, const std::vector<uint16_t>&)> initFunc;
    std::function<void(std::any&)> genFunc;
    std::vector<std::function<void(std::any&)>> subTestFunc;

    void runInit(const std::vector<uint16_t>& spinVariables) {
        if (initFunc) initFunc(data, spinVariables);
    }

    void runGen() {
        if (genFunc) genFunc(data);
    }

    void runSubTest(uint16_t testIndex) {
        if (testIndex < subTestFunc.size() && subTestFunc[testIndex]) {
            subTestFunc[testIndex](data);
        } else {
            std::cerr << "Invalid subtest index: " << testIndex << "\n";
        }
    }

};


#endif // BASE_WINDOW_H

