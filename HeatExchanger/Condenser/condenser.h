#ifndef CONDENSER_H
#define CONDENSER_H

#include "../heatexchanger.h"

class Condenser : public HeatExchanger{
private:
    std::vector<double> Xc;
    std::vector<double> Qc;
//Xd foi substituído pelo Xe da classe HeatExchanger

public:
    Condenser(){};

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
     * Simulates a condenser
     *
     * Simulates a condenser device with the characteristics given by the user through the UI or a .dat file.
     *
     * @param argAirMassFlowRate Mass of air that goes through the condenser
     * @param argAirInletTemperature Temperature of the air that goes through the condenser
     * @param argRefrigerantMassFlowRate Mass of the fluid crossing the condenser over time
     * @param argPressure Pressure on the condenser
     * @param argRefrigerantInletEnthalpy Enthalpy of the fluid used in the condenser
     */
    void simulate(double argAirMassFlowRate, double argAirInletTemperature, double argRefrigerantMassFlowRate, double argPressure, double argRefrigerantInletEnthalpy);
};

#endif // CONDENSER_H
