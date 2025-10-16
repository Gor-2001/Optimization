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

class QPushButton;

class BaseWindow : public QMainWindow {
    Q_OBJECT
public:

    /************************************************************************/
    BaseWindow(QWidget *parent = nullptr);
    /************************************************************************/
    static const uint16_t window_width = 800;
    static const uint16_t window_height = 600;
    /************************************************************************/
    void 
    setSpinVariables(
        const std::vector<std::tuple<std::string,
        uint16_t>>& spinData);
    /************************************************************************/
    void setInfoTitle(const std::string& info_title);
    void setInfoPath(const std::string& info_path);
    void setRunTitle(const std::string& run_title);
    /************************************************************************/
    void setRunCount(const uint16_t run_count);
    void setRunCountIndex(const uint16_t run_count_index);
    /************************************************************************/
    void setupWindow();
    /************************************************************************/
    template <typename T>
    void setParam(const T& param) {
        data = param;
    }
    /************************************************************************/
    template <typename T>
    void setInitFunction(const std::function<void(T&, const std::vector<uint16_t>&)>& f)
    {
        // Wrap type-safe function into a std::any-compatible version
        initFunc = [f](std::any& a, const std::vector<uint16_t>& values)
        {
            f(std::any_cast<T&>(a), values);
        };
    }
    /************************************************************************/
    template <typename T>
    void setGenFunction(const std::function<void(T&)>& f) {
        // Wrap f to work with std::any
        genFunc = [f](std::any& a) {
            f(std::any_cast<T&>(a));
        };
    }
    /************************************************************************/
    template <typename T>
    void setTestFunctions(
        const std::vector<std::tuple<std::string, std::function<void(T&)>>>& funcs)
    {
        uint16_t test_count = static_cast<uint16_t>(funcs.size());
        subTestFunc.clear();
        subTestFunc.reserve(test_count);
        testNames.resize(test_count);

        for (uint16_t i = 0; i < test_count; ++i) {
            const auto& [name, func] = funcs[i];
            testNames[i] = name;
            subTestFunc.push_back([func](std::any& a) {
                func(std::any_cast<T&>(a));
            });
        }
    }
    /************************************************************************/
    static std::vector<uint16_t> 
    random_sample_generation16(
        const uint16_t vector_size,
        const uint16_t range
    );

    static std::vector<uint8_t> 
    random_sample_generation8(
        const uint16_t vector_size,
        const uint16_t range
    );
    /************************************************************************/
    
private slots:
    void runTest();
    void cleanOutput();
    
private:

    /************************************************************************/
    QPushButton *runButton;
    QPushButton *cleanButton;
    QPushButton *openButton;
    QTextEdit   *outputBox;

    QWidget     *central;
    QVBoxLayout *mainLayout;
    /************************************************************************/
    std::vector<QSpinBox*> spinVariables;
    std::vector<std::string> spinVariableNames;
    /************************************************************************/
    std::any data;
    std::function<void(std::any&, const std::vector<uint16_t>&)> initFunc;
    std::function<void(std::any&)> genFunc;
    /************************************************************************/
    std::vector<std::string> testNames;
    std::vector<std::function<void(std::any&)>> subTestFunc;
    /************************************************************************/  
    uint16_t runCount;
    uint16_t runCountIndex;
    /************************************************************************/
    std::string infoTitle;
    std::string infoPath;
    std::string runTitle;
    /************************************************************************/
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
    /************************************************************************/
    void printToOutput(QTextEdit* outputBox, const QString& text);
    void drawInfoButton();
    void drawSpinVariableButtons();
    void drawRunButton();
    void drawCleanButton();
    void drawOutputBox();

    std::vector<uint16_t> getSpinVariableValues() const;
    /************************************************************************/

};


#endif // BASE_WINDOW_H

