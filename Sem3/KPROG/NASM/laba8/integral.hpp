#include "imgui.h"
#include <map>
#include <iostream>
#include <vector>

class Integral
{
private:

    bool functionSelected = false;
    bool isCalcIntegral = false;
    bool showPopup = false;
    bool errorInput = false;
    int type = 0;
    double step;
    double xMin = 0;
    double xMax = 0;

public:

    void start();
    void showFunctionSelection();
    bool isFunctionSelected();
    void showCalculation(bool& showPopup);
};

