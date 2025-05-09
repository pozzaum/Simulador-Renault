#ifndef EVAPORATOR_H
#define EVAPORATOR_H


#include <CoolProp.h>
#include <HumidAirProp.h>

#include <math.h>
#include <vector>
#include <iostream>
#include "filereader.h"

class Evaporator {
protected:
    std::string refrigerant;
    //geometria do condensador
    int numberOfChannels;
    std::vector<std::vector<int>> numberOfTubes;
    double tubeLength, tubeWidth, tubePitch, channelHeight, channelWidth, channelThickness, finDepth, finHeight, finPitch, finThickness, louverHeight, louverPitch, louverAngle;
    //tolerancia
    double tolerance;

    // derivados
    int numberOfPasses, totalNumberOfTubes, numberOfFins;
    double channelHydraulicDiameter, channelHeatTransferArea, finHeatTransferArea;

    // integral
    double totalHeatTransfer;

    //informações do condensador
    std::vector<double> Xe;
    std::vector<double> Xs;
    std::vector<double> Qe;
    std::vector<double> Qs;
    double refrigerantOutletEnthalpy;
    double refrigerantOutletTemperature, airOutletTemperature;
    double airOutletEnthalpy, airOutletRelativeHumidity;

public:

    Evaporator(void){};
    ~Evaporator(){};

    void simulate(double argAirMassFlowRate, double argAirInletTemperature, double argAirInletRelativeHumidity, double argRefrigerantMassFlowRate, double argRefrigerantInletPressure, double argRefrigerantInletEnthalpy);
    void getDatafromUI();
    void getDatafromFiles();

    double getRefrigerantOutletEnthalpy(void){return this->refrigerantOutletEnthalpy;};
    double getRefrigerantOutletTemperature(void){return this->refrigerantOutletTemperature;};
    double getAirOutletTemperature(void){return this->airOutletTemperature;};
    double getAirOutletRelativeHumidity(void){return this->airOutletRelativeHumidity;};
    double getHeatTransfer(void){return this->totalHeatTransfer;};
};

#endif // EVAPORATOR_H
