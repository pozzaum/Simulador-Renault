#ifndef EXPANSIONDEVICE_H
#define EXPANSIONDEVICE_H

#include "../externals/CoolProps/include/CoolProp.h"

#include "../filereader.h"

class ExpansionDevice{
private:
    std::string refrigerant;
    double flowArea, flowCoefficient, massFlowRate;
public:
    ExpansionDevice(){};

    /**
     * @brief simulate
     * Simulates an expansion device
     *
     * Simulates an expansion device with the characteristics given by the user through the UI or a .dat file.
     * @param argInletPressure Pressure of the fluid that arrives at the expansion device
     * @param outletPressure Desired pressure for the fluid when it comes out of the expansion device
     * @param argInletEnthalpy Enthalpy at the intake of the expansion device
     * @param argOpeningRatio Ratio at which the expansion device accepts the fluid
     */

    void simulate(double argInletPressure, double outletPressure, double argInletEnthalpy, double argOpeningRatio);

    //GETTERS
    double getMassFlowRate(void){return this->massFlowRate;}
    double getFlowCoefficient(void){return this->flowCoefficient;}
    double getFlowArea(void){return this->flowArea;}
    double getOriDiameter(){return  std::pow((this->flowArea * 4 / M_PI), 0.5);}

    //SETTERS
    void setMassFlowRate(double e_massFlowRate){this->massFlowRate = e_massFlowRate;}
    void setFlowCoefficient(double e_flowCoefficient){this->flowCoefficient = e_flowCoefficient;}
    void setFlowArea(double e_flowArea){this->flowArea = e_flowArea;}
    void setOrificeDiameter(double e_oridiameter){this->flowArea = M_PI * std::pow(e_oridiameter, 2.0) / 4.0;}

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
};

#endif // EXPANSIONDEVICE_H
