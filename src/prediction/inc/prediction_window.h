// prediction_window.h

#ifndef PREDICTION_WINDOW_H
#define PREDICTION_WINDOW_H

#include "prediction_test.h"
#include "../../info/info_window.h"
#include "../../base_window.h"

class QPushButton;

class PredictionWindow : public BaseWindow {
    Q_OBJECT
public:
    PredictionWindow(QWidget *parent = nullptr);

private:
};

#endif // PREDICTION_WINDOW_H
