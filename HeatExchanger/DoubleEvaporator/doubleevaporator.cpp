#include "doubleevaporator.h"

void DoubleEvaporator::simulate(double argAirMassFlowRate, double argAirInletTemperature, double argAirInletRelativeHumidity, double argRefrigerantMassFlowRate, double argRefrigerantPressure, double argRefrigerantInletEnthalpy){
    double evaporator1AirInletTemperature = argAirInletTemperature;
    double evaporator1AirInletRelativeHumidity = argAirInletRelativeHumidity;
    double evaporator1AirOutletRelativeHumidity;
    double evaporator1AirInletTemperature_0;
    double evaporator1RefrigerantOutletEnthalpy = 0.0;
    double evaporator1RefrigerantOutletEnthalpy_0 = 0.0;

    do{
        this->evaporator1.getDataFromFiles();
        this->evaporator1.simulate(argAirMassFlowRate, evaporator1AirInletTemperature, evaporator1AirInletRelativeHumidity, argRefrigerantMassFlowRate, argRefrigerantPressure, argRefrigerantInletEnthalpy);
        evaporator1RefrigerantOutletEnthalpy_0 = evaporator1RefrigerantOutletEnthalpy;
        evaporator1RefrigerantOutletEnthalpy = this->evaporator1.getRefrigerantOutletEnthalpy();
        this->evaporator2.getDataFromFiles();
        this->evaporator2.simulate(argAirMassFlowRate, argAirInletTemperature, argAirInletRelativeHumidity, argRefrigerantMassFlowRate, argRefrigerantPressure, evaporator1RefrigerantOutletEnthalpy);
        evaporator1AirInletTemperature = this->evaporator2.getAirOutletTemperature();
        evaporator1AirInletRelativeHumidity = this->evaporator2.getAirOutletRelativeHumidity();
    } while (std::abs(evaporator1RefrigerantOutletEnthalpy - evaporator1RefrigerantOutletEnthalpy_0) / evaporator1RefrigerantOutletEnthalpy > tolerance);

}

void DoubleEvaporator::getDataFromFiles(){
    FileReader fileReader;

    fileReader.loadFile("evaporator.dat");
    evaporator1.setNumofPipes(fileReader.readIntegerMatrix("numberOfPipes"));
    evaporator1.setNumofPasses((int)evaporator1.getNumofPipes().size());
    evaporator1.setNumofChannels(fileReader.readIntegerVariable("numberOfChannels"));
    evaporator1.setTubeLength(fileReader.readRealVariable("tubeLength"));
    evaporator1.setTubeWidth(fileReader.readRealVariable("tubeWidth"));
    evaporator1.setTubePitch(fileReader.readRealVariable("tubePitch"));
    evaporator1.setChannelHeight(fileReader.readRealVariable("channelHeight"));
    evaporator1.setChannelWidth(fileReader.readRealVariable("channelWidth"));
    evaporator1.setFinDepth(fileReader.readRealVariable("finDepth"));
    evaporator1.setFinHeight(fileReader.readRealVariable("finHeight"));
    evaporator1.setFinPitch(fileReader.readRealVariable("finPitch"));
    evaporator1.setFinThickness(fileReader.readRealVariable("finThickness"));
    evaporator1.setLouverHeight(fileReader.readRealVariable("louverHeight"));
    evaporator1.setLouverPitch(fileReader.readRealVariable("louverPitch"));
    evaporator1.setLouverAngle(fileReader.readRealVariable("louverAngle"));
    evaporator1.setTolerance(fileReader.readRealVariable("tolerance"));
    evaporator2.setNumofPipes(evaporator1.getNumofPipes());
    evaporator2.setNumofPasses(evaporator1.getNumofPasses());
    evaporator2.setNumofChannels(evaporator1.getNumofChannels());
    evaporator2.setTubeLength(evaporator1.getTubeLength());
    evaporator2.setTubeWidth(evaporator1.getTubeWidth());
    evaporator2.setTubePitch(evaporator1.getTubePitch());
    evaporator2.setChannelHeight(evaporator1.getChannelHeight());
    evaporator2.setChannelWidth(evaporator1.getChannelWidth());
    evaporator2.setFinDepth(evaporator1.getFinDepth());
    evaporator2.setFinHeight(evaporator1.getFinHeight());
    evaporator2.setFinPitch(evaporator1.getFinPitch());
    evaporator2.setFinThickness(evaporator1.getFinThickness());
    evaporator2.setLouverHeight(evaporator1.getLouverHeight());
    evaporator2.setLouverPitch(evaporator1.getLouverPitch());
    evaporator2.setLouverAngle(evaporator1.getLouverAngle());
    evaporator2.setTolerance(evaporator1.getTolerance());
    tolerance = evaporator1.getTolerance();
    fileReader.unloadFile();
}

void DoubleEvaporator::getDataFromUI(){

}
