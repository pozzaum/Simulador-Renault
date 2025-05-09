#include "expansiondevice.h"

void ExpansionDevice::getDataFromFiles(){
    FileReader fileReader;

    fileReader.loadFile("./refrigerationSystem.dat");
    refrigerant = fileReader.readStringVariable("fluid");
    fileReader.unloadFile();

    fileReader.loadFile("expansionDevice.dat");
    flowArea = M_PI * pow(fileReader.readRealVariable("orificeDiameter"), 2.0) / 4.0;
    flowCoefficient = fileReader.readRealVariable("flowCoefficient");
    fileReader.unloadFile();
}


void ExpansionDevice::simulate(double argInletPressure, double argOutletPressure, double argInletEnthalpy, double argOpeningRatio){
    double inletDensity = CoolProp::PropsSI("D", "P", argInletPressure, "H", argInletEnthalpy, refrigerant);
    massFlowRate = argOpeningRatio * flowCoefficient * flowArea * pow(2.0 * inletDensity * (argInletPressure - argOutletPressure), 0.5);
}
