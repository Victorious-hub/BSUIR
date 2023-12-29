#include "integral.hpp"
#include "implot.h"
#include "imgui_stdlib.h"
#include <math.h>

extern "C" double Simpson(double a, double b, int type);
extern "C" double function(double x, int type);

bool validateIntInput(const std::string& input)
{
    try 
    {
        std::stoi(input);
        return true;

    } catch (const std::exception&) 
    {
        return false;
    }
}

void Integral::start()
{
    
    ImGui::SetNextWindowSize(ImVec2(500,500));
    ImGui::Begin("Intergal calculation", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize); 
    static int selectedItem = 0;
    const char* items[] = {"sin(x)","cos(x)","x^2","x","sqrt(x)"};
    ImGui::Combo("Choose any function", &selectedItem, items, IM_ARRAYSIZE(items));
    static std::string inputLower, inputHigher;
    
    if (ImGui::InputText("Enter lower limit", &inputLower, ImGuiInputTextFlags_CharsDecimal) || ImGui::InputText("Enter higher limit", &inputHigher, ImGuiInputTextFlags_CharsDecimal))
    {
        xMin = atof(inputLower.c_str());
        xMax = atof(inputHigher.c_str());
    }

    if (ImGui::Button("Show function"))
    {
        functionSelected = true;
        type = selectedItem;
        
        if (inputLower.size() > 0 && inputHigher.size())
        {
            showFunctionSelection();
        }
    }
    
    if (errorInput)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
        ImGui::TextWrapped("Invalid input");
        ImGui::PopStyleColor();
    }
    ImGui::End();
    
}

bool Integral::isFunctionSelected()
{
    return functionSelected;
}

void Integral::showCalculation(bool& showPopup)
{

    ImGui::OpenPopup("Integral");
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Integral", 0, ImGuiWindowFlags_AlwaysAutoResize))
    {
        std::string getCalc = std::to_string(Simpson(xMin, xMax, type));
        ImGui::Text("%s", getCalc.c_str());

        if (ImGui::Button("Close"))
        {
            showPopup = false;
            ImGui::CloseCurrentPopup(); 
        }

        ImGui::EndPopup();
    }
    
} 

void Integral::showFunctionSelection()
{
   
   if (functionSelected)
   {    
        static std::vector<double> x(100);
        static std::vector<double> y(100);

        ImGui::SetNextWindowSize(ImVec2(500,500));
        ImGui::Begin("Function selection");
        ImGui::Text("Select function");
                
        double step = (xMax - xMin) / (100 - 1);
        
        if (!type)
        {
            if (ImPlot::BeginPlot("Sinus Plot"))
            {
                for (int i = 0; i < 100; ++i)
                {
                    x[i] = xMin + i * step;
                    y[i] = sin(x[i]);
                }
                const int numPoints = x.size();
                ImPlot::SetupAxesLimits(-4.0, 20.0, -10.0, 20.0);
                ImPlot::PlotLine("Sinus", x.data(), y.data(), numPoints);
                ImPlot::EndPlot();
            }
        }

        if (type == 1)
        {
            if (ImPlot::BeginPlot("Cosinus Plot"))
            {
                for (int i = 0; i < 100; ++i)
                {
                    x[i] = xMin + i * step;
                    y[i] = cos(x[i]);
                }
                const int numPoints = x.size();
                ImPlot::SetupAxesLimits(-4.0, 20.0, -10.0, 20.0);
                ImPlot::PlotLine("Cosinus", x.data(), y.data(), numPoints);
                ImPlot::EndPlot();
            }
        }


        if (type == 2)
        {
            if (ImPlot::BeginPlot("Parabola Plot"))
            {
                for (int i = 0; i < 100; ++i)
                {
                    x[i] = xMin + i * step;
                    y[i] = x[i] * x[i];
                }
                const int numPoints = x.size();
                ImPlot::SetupAxesLimits(-4.0, 20.0, -10.0, 20.0);
                ImPlot::PlotLine("Parabola", x.data(), y.data(), numPoints);
                ImPlot::EndPlot();
            }
        }
     
        if (type == 3)
        {
           if (ImPlot::BeginPlot("Line Plot"))
            {
                for (int i = 0; i < 100; ++i)
                {
                    x[i] = xMin + i * step;
                    y[i] = x[i];
                }

                const int numPoints = x.size();
                ImPlot::SetupAxesLimits(-4.0, 20.0, -10.0, 20.0);
                ImPlot::PlotLine("Line", x.data(), y.data(), numPoints);
                ImPlot::EndPlot();
            }
        }

        if (type == 4)
        {
            if (ImPlot::BeginPlot("Sqrt Plot"))
            {
                for (int i = 0; i < 100; ++i)
                {
                    x[i] = xMin + i * step;
                    if (x[i] < 0)
                    {
                        x[i] = 0;
                    }
                    y[i] = sqrt(x[i]);
                }

                const int numPoints = x.size();
                ImPlot::SetupAxesLimits(-4.0, 20.0, -10.0, 20.0);
                ImPlot::PlotLine("Sqrt", x.data(), y.data(), numPoints);
                ImPlot::EndPlot();
            }
        }

        if (ImGui::Button("Calculate integral at your point"))
        {
            showPopup = true;
        }

        if (showPopup)
        {
            showCalculation(showPopup);
        }

        if (ImGui::Button("Close graphics"))
        {
            functionSelected = false;
            type = 0;
            ImGui::CloseCurrentPopup(); 
        }

        ImGui::End();
   }

}

