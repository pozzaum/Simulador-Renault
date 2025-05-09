#ifndef BATTERYEVAPORATOR_H
#define BATTERYEVAPORATOR_H

#include "../heatexchanger.h"

class BatteryEvaporator : public HeatExchanger{
private:
    double moduleWidth, moduleHeight, moduleLength, moduleThermalConductivity;
    std::vector<double> TotalHeatTransfer_vec;

public:
    BatteryEvaporator() {
        TotalHeatTransfer_vec.resize(1, 0.0);  // Garante que o primeiro valor seja 0.0
        totalHeatTransfer = 0.0;
    }

    /**
     * @brief getDataFromFiles
     * Loads data.
     *
     * Loads data for the component from the respective .dat file.
     */
    void getDataFromFiles();
    /**
     * @brief getDataFromUI
     * Loads Data.
     *
     * Loads data for the component from the input fields in the UI.
     */
    void getDataFromUI();

    /**
     * @brief simulate
     * Simulates the battery evaporator
     *
     * Simulates the evaporator that is used to cool the battery of the car with the characteristics given by the user through the UI or a .dat file.
     *
     * @param argBatteryTemperature Initial tempeture on the battery
     * @param argRefrigerantMassFlowRate Quantity of mass that flows through the battery evaporator over time
     * @param argRefrigerantPressure Pressure of the fluid that goes through the evaporator
     * @param argRefrigerantInletEnthalpy Enthalpy of the fluid used in the evaporator at entry
     */


    //GETTERS
    double getModuleWidth(){ return this->moduleWidth;}
    double getModuleHeight(){ return this->moduleHeight;}
    double getModuleLength(){ return this->moduleLength;}
    double getModTherConductivity(){ return this->moduleThermalConductivity;}
    double getHeatTransfer(){return this -> totalHeatTransfer;}
    std::vector<double> getTotalHeatTransfer(){return this->TotalHeatTransfer_vec;}

    //SETTERS
    void setModuleWidth(double e_moduleWidth){this->moduleWidth = e_moduleWidth;}
    void setModuleHeight(double e_moduleHeight){this->moduleHeight = e_moduleHeight;}
    void setModuleLength(double e_moduleLength){this->moduleLength = e_moduleLength;}
    void setModTherConductivity(double e_moduleThermalConductivity){this->moduleThermalConductivity = e_moduleThermalConductivity;}

    void simulate(double argBatteryTemperature, double argRefrigerantMassFlowRate, double argRefrigerantPressure, double argRefrigerantInletEnthalpy);
};

#endif // BATTERYEVAPORATOR_H
