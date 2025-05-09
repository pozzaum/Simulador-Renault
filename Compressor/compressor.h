#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "../externals/CoolProps/include/CoolProp.h"
//#include "Refprop/fluid_codes.h"
//#include "Refprop/refprop_v10.h"
#include "fparser.hh"


#include "../filereader.h"

class Compressor{
public:
    Compressor(){};

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
     * Simulates a compressor
     *
     * Simulates a compressor with the characteristics given by the user through the UI or a .dat file.
     *
     * @param argSuctionPressure Suction pressure applied by the compressor
     * @param argDischargePressure Compressor's discharge pressure
     * @param argSuctionLineEnthalpy Enthalpy at the compressor's suction line
     * @param argFrequency Frequency at which the compressor operates
     */
    void simulate(double argSuctionPressure, double argDischargePressure, double argSuctionLineEnthalpy, double argFrequency);

    //GETTERS

    double getSweptVolume(){ return this->sweptVolume;}
    double getThermalConductance(){ return this->thermalConductance;}
    double getAmbientTemperature(){ return this->ambientTemperature;}
    double getOutletEnthalpy(){ return this->outletEnthalpy;}
    double getMassFlowRate(){ return this->massFlowRate;}
    double getPowerConsumption(){ return this->powerConsumption;}
    double getHeatTransferRate(){ return this->heatTransferRate;}
    std::string getVolEfficiency(){ return this->volumetricEfficiencyExpression;}
    std::string getGlobalEfficiency(){ return this->globalEfficiencyExpression;}

    //SETTERS

    void setSweptVolume(double e_sweptVolume){ this->sweptVolume = e_sweptVolume; }
    void setThermalConductance(double e_thermalConductance){ this->thermalConductance = e_thermalConductance; }
    void setAmbientTemperature(double e_ambientTemperature){ this->ambientTemperature = e_ambientTemperature; }
    void setOutletEnthalpy(double e_outletEnthalpy){ this->outletEnthalpy = e_outletEnthalpy; }
    void setMassFlowRate(double e_massFlowRate){ this->massFlowRate = e_massFlowRate; }
    void setPowerConsumption(double e_powerConsumption){ this->powerConsumption = e_powerConsumption; }
    void setHeatTransferRate(double e_heatTransferRate){ this->heatTransferRate = e_heatTransferRate; }
    void setVolEfficiency(std::string e_volumetricEfficiencyExpression){
        this->volumetricEfficiencyExpression = e_volumetricEfficiencyExpression;
        this->volumetricEfficiencyFP.Parse(volumetricEfficiencyExpression, "pe,pc,f");
    }
    void setGlobalEfficiency(std::string e_globalEfficiencyExpression){
        this->globalEfficiencyExpression = e_globalEfficiencyExpression;
        this->globalEfficiencyFP.Parse(globalEfficiencyExpression, "pe,pc,f");
    }

private:
    // data from input file
    std::string refrigerant, volumetricEfficiencyExpression, globalEfficiencyExpression;
    double sweptVolume, thermalConductance, ambientTemperature;

    FunctionParser volumetricEfficiencyFP, globalEfficiencyFP;

    // simulated data
    double outletEnthalpy, massFlowRate, powerConsumption, heatTransferRate;
};

#endif // COMPRESSOR_H
