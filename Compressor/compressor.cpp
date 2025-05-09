#include "compressor.h"


void Compressor::getDataFromFiles(){
    FileReader fileReader;

    fileReader.loadFile("./refrigerationSystem.dat");
    refrigerant = fileReader.readStringVariable("fluid");
    fileReader.unloadFile();

    fileReader.loadFile("compressor.dat");
    sweptVolume = fileReader.readRealVariable("sweptVolume");
    volumetricEfficiencyExpression = fileReader.readStringVariable("volumetricEfficiency");
    globalEfficiencyExpression = fileReader.readStringVariable("globalEfficiency");
    thermalConductance = fileReader.readRealVariable("thermalConductance");
    ambientTemperature = fileReader.readRealVariable("ambientTemperature") + 273.15;

    volumetricEfficiencyFP.Parse(volumetricEfficiencyExpression, "pe,pc,f");
    globalEfficiencyFP.Parse(globalEfficiencyExpression, "pe,pc,f");

    fileReader.unloadFile();
}

void Compressor::simulate(double argSuctionPressure, double argDischargePressure, double argSuctionLineEnthalpy, double argFrequency){
    double input[3] = {argSuctionPressure, argDischargePressure, argFrequency};
    double volumetricEfficiency = (argDischargePressure != INFINITY ? volumetricEfficiencyFP.Eval(input): INFINITY);
    double globalEfficiency = globalEfficiencyFP.Eval(input);

    // RefpropV10 refprop;

    // refprop.SetFluidsLib(refrigerant);
    // RefpropV10::LibInputs inputs;
    // inputs.hOut = "D";
    // inputs.hIn = "PH";
    // inputs.a = argSuctionPressure;
    // inputs.b = argSuctionLineEnthalpy;
    // inputs.z = {0.5 , 0.5};
    // inputs.iUnits = Units::DEFAULT;
    // inputs.iFlag = 0;
     double suctionLineDensity = CoolProp::PropsSI("D", "P", argSuctionPressure, "H", argSuctionLineEnthalpy, refrigerant);
    // RefpropV10::LibOutputs suctionLineDensity = refprop.AllPropsLib(inputs);
     std::cout << suctionLineDensity << "argSuctionPressure: " << argSuctionPressure << " - argSuctionLineEnthalpy: " << argSuctionLineEnthalpy << std::endl;
    massFlowRate = argFrequency * volumetricEfficiency * sweptVolume * suctionLineDensity;

    double suctionLineEntropy = CoolProp::PropsSI("S", "P", argSuctionPressure, "H", argSuctionLineEnthalpy, refrigerant);
    double isentropicDischargeLineEnthalpy = CoolProp::PropsSI("H", "P", argDischargePressure, "S", suctionLineEntropy, refrigerant);
    powerConsumption = massFlowRate * (isentropicDischargeLineEnthalpy - argSuctionLineEnthalpy) / globalEfficiency;

    double isentropicDischargeLineTemperature = CoolProp::PropsSI("T", "P", argDischargePressure, "S", suctionLineEntropy, refrigerant);
    heatTransferRate = thermalConductance * (isentropicDischargeLineTemperature - ambientTemperature);

    outletEnthalpy = argSuctionLineEnthalpy + (powerConsumption - heatTransferRate) / massFlowRate;
}
