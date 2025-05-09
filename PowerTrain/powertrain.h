#ifndef POWERTRAIN_H
#define POWERTRAIN_H

#include <fstream>
#include <vector>
#include <iostream>
#include <math.h>
#include "../externals/fparser/fparser.hh"
#include "../filereader.h"
using namespace std;


class PowerTrain{
private:
    double transmissionEfficiency, electricalEfficiency;
    double vehicleMass, rotaryMassConversionCoefficient, vehicleWindwardArea;
    double rollingResistanceCoefficient, dragCoefficient;

    double cellVoltage, cellResistance, numberOfCellsInParallel, numberOfCellsInSeries;

    //vector<vector<double>> drivingCycle;
    int numRows;
    std::vector<std::vector<double>> drivingCycle;


    double outputPower, moduleCurrent, cellCurrent, cellHeatRelease, moduleHeatRelease;

    double c, volume, timeStep;

    int a = 0;


    std::vector<double> Tb_vec, moduleHeatRelease_vec;

public:

    PowerTrain() : drivingCycle(1800, std::vector<double>(2, 0.0)) {
        numRows = 1800;  // Atribuir diretamente no corpo do construtor
        Tb_vec.resize(1, 318.15);
        moduleHeatRelease_vec.resize(1, 0.0);  // Garante que o primeiro valor seja 0.0
    }

    void getDataFromFiles();
    void getDataFromUI();

    void simulate(double argSpeed = 0.0, double ArgAcceleration = 0.0);
    void simulateCycle(double Tb, double totalHeatTransfer);

    std::vector<double> getTb(){return this->Tb_vec;}
    std::vector<double> getModuleHeatRelease(){return this->moduleHeatRelease_vec;}

};


/*
class Battery{
private:
    double volume, hc, c, tamb, area;
    std::vector<double> time, temperature, current, voltage, soc, ocv, Qgen, Qloss, delta_t;

public:
    Battery(){};
    double linap(double soc);
    void getDataFromFiles();
    void simulate();



};
*/

#endif //POWERTRAIN_H


