#ifndef DOUBLEEVAPORATOR_H
#define DOUBLEEVAPORATOR_H

#include "../heatexchanger.h"
#include <cmath>

class DoubleEvaporator{
private:
    HeatExchanger evaporator1, evaporator2;
    double tolerance;

public:
    DoubleEvaporator(){};

    /**
     * @brief simulate
     * Simulates a double evaporator
     *
     * Simulates a set of two evaporator with the characteristics given by the user through the UI or a .dat file.
     *
     * @param argAirMassFlowRate Mass of air going through the evaporators over time
     * @param argAirInletTemperature Temperature of the air that goes through the evaporators
     * @param argAirInletRelativeHumidity Relative humidity of the air that goes through the evaporators
     * @param argRefrigerantMassFlowRate Mass of fluid crossing the evaporators over time
     * @param argRefrigerantPressure Pressure on the fluid crossing the evaporators
     * @param argRefrigerantInletEnthalpy Enthalpy at entry of the fluid used at the evaporators
     */
    void simulate(double argAirMassFlowRate, double argAirInletTemperature, double argAirInletRelativeHumidity, double argRefrigerantMassFlowRate, double argRefrigerantPressure, double argRefrigerantInletEnthalpy);

    //GETTERS
    std::vector<std::vector<int>> getNumofPipes(){return this->evaporator1.getNumofPipes();}
    int getNumofChannels(){return this->evaporator1.getNumofChannels();}
    double getTubeLength(){return this->evaporator1.getTubeLength();}
    double getTubeWidth(){return this->evaporator1.getTubeWidth();}
    double getTubePitch(){return this->evaporator1.getTubePitch();}
    double getChannelHeight(){return this->evaporator1.getChannelHeight();}
    double getChannelWidth(){return this->evaporator1.getChannelWidth();}
    double getFinDepth(){return this->evaporator1.getFinDepth();}
    double getFinHeight(){return this->evaporator1.getFinHeight();}
    double getFinPitch(){return this->evaporator1.getFinPitch();}
    double getFinThickness(){return this->evaporator1.getFinThickness();}
    double getLouverHeight(){return this->evaporator1.getLouverHeight();}
    double getLouverPitch(){return this->evaporator1.getLouverPitch();}
    double getLouverAngle(){return this->evaporator1.getLouverAngle();}
    double getTolerance(){return this->evaporator1.getTolerance();}
    double getRefrigerantOutletEnthalpyEvaporator1(){ return this->evaporator1.getRefrigerantOutletEnthalpy(); };
    double getRefrigerantOutletEnthalpyEvaporator2(){ return this->evaporator2.getRefrigerantOutletEnthalpy(); };
    // double getRefrigerantPressureLoss(){ };
    // double getRefrigerantPressureLossEvaporator1(){  };
    // double getRefrigerantPressureLossEvaporator2();
    double getRefrigerantOutletTemperature(){ return this->evaporator2.getRefrigerantOutletTemperature(); };
    double getAirOutletTemperatureEvaporator1(){ return this->evaporator1.getAirOutletTemperature(); };
    double getAirOutletTemperatureEvaporator2(){ return this->evaporator2.getAirOutletTemperature(); };
    double getAirOutletRelativeHumidityEvaporator1(){  return this->evaporator1.getAirOutletRelativeHumidity(); };
    double getAirOutletRelativeHumidityEvaporator2(){ return this->evaporator2.getAirOutletRelativeHumidity(); };
    double getHeatTransfer(){ return this->evaporator1.getHeatTransfer() + this->evaporator2.getHeatTransfer(); };
    double getHeatTransferEvaporator1(){ return this->evaporator1.getHeatTransfer(); };
    double getHeatTransferEvaporator2(){ return this->evaporator2.getHeatTransfer(); };

    //SETTERS
    void setNumofPipes(std::vector<std::vector<int>> e_numofpipes){
        evaporator1.setNumofPipes(e_numofpipes);
        evaporator2.setNumofPipes(e_numofpipes);
    }
    void setNumofChannels(int e_numofchannels){
        evaporator1.setNumofChannels(e_numofchannels);
        evaporator2.setNumofChannels(e_numofchannels);
    }
    void setTubeLength(double e_tubelength){
        evaporator1.setTubeLength(e_tubelength);
        evaporator2.setTubeLength(e_tubelength);
    }
    void setTubeWidth(double e_tubewidth){
        evaporator1.setTubeWidth(e_tubewidth);
        evaporator2.setTubeWidth(e_tubewidth);
    }
    void setTubePitch(double e_tubepitch){
        evaporator1.setTubePitch(e_tubepitch);
        evaporator2.setTubePitch(e_tubepitch);
    }
    void setChannelHeight(double e_channelheight){
        evaporator1.setChannelHeight(e_channelheight);
        evaporator2.setChannelHeight(e_channelheight);
    }
    void setChannelWidth(double e_channelwidth){
        evaporator1.setChannelWidth(e_channelwidth);
        evaporator2.setChannelWidth(e_channelwidth);
    }
    void setFinDepth(double e_findepth){
        evaporator1.setFinDepth(e_findepth);
        evaporator2.setFinDepth(e_findepth);
    }
    void setFinHeight(double e_finheight){
        evaporator1.setFinHeight(e_finheight);
        evaporator2.setFinHeight(e_finheight);
    }
    void setFinPitch(double e_finpitch){
        evaporator1.setFinPitch(e_finpitch);
        evaporator2.setFinPitch(e_finpitch);
    }
    void setFinThickness(double e_finthick){
        evaporator1.setFinThickness(e_finthick);
        evaporator2.setFinThickness(e_finthick);
    }
    void setLouverHeight(double e_louverheight){
        evaporator1.setLouverHeight(e_louverheight);
        evaporator2.setLouverHeight(e_louverheight);
    }
    void setLouverPitch(double e_louverpitch){
        evaporator1.setLouverPitch(e_louverpitch);
        evaporator2.setLouverPitch(e_louverpitch);
    }
    void setLouverAngle(double e_louverangle){
        evaporator1.setLouverAngle(e_louverangle);
        evaporator2.setLouverAngle(e_louverangle);
    }
    void setTolerance(double e_tolerance){
        this->tolerance = e_tolerance;
        evaporator1.setTolerance(e_tolerance);
        evaporator2.setTolerance(e_tolerance);
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
};

#endif // DOUBLEEVAPORATOR_H
