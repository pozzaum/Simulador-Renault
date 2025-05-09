#ifndef HEATEXCHANGER_H
#define HEATEXCHANGER_H

#include "../externals/CoolProps/include/CoolProp.h"
#include "../externals/CoolProps/include/HumidAirProp.h"

#include <cmath>
#include <vector>
#include <iostream>
#include "../filereader.h"

class HeatExchanger{
protected:
    std::string refrigerant;
    //geometria do trocador de calor
    int numberOfChannels;
    std::vector<std::vector<int>> numberOfTubes;
    double tubeLength, tubeWidth, tubePitch, channelHeight, channelWidth, channelThickness, finDepth, finHeight, finPitch, finThickness, louverHeight, louverPitch, louverAngle;
    //tolerância
    double tolerance;

    // derivados
    int numberOfPasses = 0, totalNumberOfTubes, numberOfFins;
    double channelHydraulicDiameter, channelHeatTransferArea, finHeatTransferArea;

    // integral
    std::vector<double> totalHeatTransferArg;
    double totalHeatTransfer;

    //informações do trocador de calor
    std::vector<double> Xe;
    std::vector<double> Xs;
    std::vector<double> Qe;
    std::vector<double> Qs;
    double refrigerantOutletEnthalpy;
    double refrigerantOutletTemperature, airOutletTemperature;
    double airOutletEnthalpy, airOutletRelativeHumidity;

public:
    HeatExchanger(){};

    /**
     * @brief simulate
     * Simulates a generic heat exchanger
     *
     * Simulates a generic heat exchanger with the characteristics given by the user through the UI or a .dat file.
     *
     * @param argAirMassFlowRate Mass of air going through the heat exchanger over time
     * @param argAirInletTemperature Temperature of the air that goes through the heat exchanger
     * @param argAirInletRelativeHumidity Relative humidity of the air that goes through the heat exchanger
     * @param argRefrigerantMassFlowRate Mass of fluid crossing the heat exchanger over time
     * @param argRefrigerantPressure Pressure on the fluid crossing the heat exchanger
     * @param argRefrigerantInletEnthalpy Enthalpy at entry of the fluid used at the heat exchanger
     */
    void simulate(double argAirMassFlowRate, double argAirInletTemperature, double argAirInletRelativeHumidity, double argRefrigerantMassFlowRate, double argRefrigerantInletPressure, double argRefrigerantInletEnthalpy);

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

    //GETTERS

    std::vector<std::vector<int>> getNumofPipes(){return this->numberOfTubes;}
    int getNumofPasses(){return this->numberOfPasses;}
    int getNumofChannels(){return this->numberOfChannels;}
    double getTubeLength(){return this->tubeLength;}
    double getTubeWidth(){return this->tubeWidth;}
    double getTubePitch(){return this->tubePitch;}
    double getChannelHeight(){return this->channelHeight;}
    double getChannelWidth(){return this->channelWidth;}
    double getFinDepth(){return this->finDepth;}
    double getFinHeight(){return this->finHeight;}
    double getFinPitch(){return this->finPitch;}
    double getFinThickness(){return this->finThickness;}
    double getLouverHeight(){return this->louverHeight;}
    double getLouverPitch(){return this->louverPitch;}
    double getLouverAngle(){return this->louverAngle;}
    double getTolerance(){return this->tolerance;}
    double getRefrigerantOutletEnthalpy(){return this->refrigerantOutletEnthalpy;}
    double getRefrigerantOutletTemperature(){return this->refrigerantOutletTemperature;}
    double getAirOutletTemperature(){return this->airOutletTemperature;};
    double getAirOutletRelativeHumidity(){return this->airOutletRelativeHumidity;}
    double getHeatTransfer(){return this->totalHeatTransfer;}


    //SETTERS

    void setNumofPipes(std::vector<std::vector<int>> e_numberOfTubes){this->numberOfTubes = e_numberOfTubes;}
    void setNumofPasses(int e_numberOfPasses){this->numberOfPasses = e_numberOfPasses;}
    void setNumofChannels(int e_numberOfChannels){this->numberOfChannels = e_numberOfChannels;}
    void setTubeLength(double e_tubeLength){this->tubeLength = e_tubeLength;}
    void setTubeWidth(double e_tubeWidth){this->tubeWidth = e_tubeWidth;}
    void setTubePitch(double e_tubePitch){this->tubePitch = e_tubePitch;}
    void setChannelHeight(double e_channelHeight){this->channelHeight = e_channelHeight;}
    void setChannelWidth(double e_channelWidth){this->channelWidth = e_channelWidth;}
    void setFinDepth(double e_finDepth){this->finDepth = e_finDepth;}
    void setFinHeight(double e_finHeight){this->finHeight = e_finHeight;}
    void setFinPitch(double e_finPitch){this->finPitch = e_finPitch;}
    void setFinThickness(double e_finThickness){this->finThickness = e_finThickness;}
    void setLouverHeight(double e_louverHeight){this->louverHeight = e_louverHeight;}
    void setLouverPitch(double e_louverPitch){this->louverPitch = e_louverPitch;}
    void setLouverAngle(double e_louverAngle){this->louverAngle = e_louverAngle;}
    void setTolerance(double e_tolerance){this->tolerance = e_tolerance;}

};

#endif // HEATEXCHANGER_H
