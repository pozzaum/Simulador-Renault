#include "batteryevaporator.h"

void BatteryEvaporator::getDataFromFiles(){
    FileReader fileReader;

    fileReader.loadFile("./refrigerationSystem.dat");
    refrigerant = fileReader.readStringVariable("fluid");
    fileReader.unloadFile();

    fileReader.loadFile("batteryEvaporator.dat");
    std::vector<int> valor;
    valor.push_back(fileReader.readIntegerVariable("numberOfTubes"));
    numberOfTubes.push_back(valor);
    numberOfChannels = fileReader.readIntegerVariable("numberOfChannels");
    tubeLength = fileReader.readRealVariable("tubeLength");
    tubeWidth = fileReader.readRealVariable("tubeWidth");
    channelHeight = fileReader.readRealVariable("channelHeight");
    channelWidth = fileReader.readRealVariable("channelWidth");
    moduleWidth = fileReader.readRealVariable("moduleWidth");
    moduleHeight = fileReader.readRealVariable("moduleHeight");
    moduleLength = fileReader.readRealVariable("moduleLength");
    moduleThermalConductivity = fileReader.readRealVariable("moduleThermalConductivity");
    tolerance = fileReader.readRealVariable("tolerance");
    fileReader.unloadFile();

    // 3 Constantes geométricas
    channelHydraulicDiameter = 2 * channelHeight * channelWidth / (channelHeight + channelWidth);
    channelHeatTransferArea = 2 * numberOfChannels * (channelWidth + channelHeight) * tubeLength;
    channelThickness = (tubeWidth - numberOfChannels * channelWidth) / (numberOfChannels + 1.0);
}

void BatteryEvaporator::simulate(double argBatteryTemperature, double argRefrigerantMassFlowRate, double argRefrigerantPressure, double argRefrigerantInletEnthalpy){
    // 1 inicializando as variaveis de interesse
    Xe.push_back(0.0);
    Xs.push_back(0.0);
    Qe.push_back(0.0);
    Qs.push_back(0.0);

    refrigerantOutletEnthalpy = 0.0;
    refrigerantOutletTemperature = 0.0;
    totalHeatTransfer = 0.0;
    //TotalHeatTransfer_vec.push_back(totalHeatTransfer);

    // This allows to close the EXV without simulating the batteryEvaporator - ADDED
    if (argRefrigerantMassFlowRate == 0.0){
        TotalHeatTransfer_vec.push_back(totalHeatTransfer);
        return;
    }

    // 2 verificando se o refrigerante vai aquecer
    double refrigerantInletTemperature = CoolProp::PropsSI("T", "P", argRefrigerantPressure, "H", argRefrigerantInletEnthalpy, refrigerant);
    if (argBatteryTemperature <= refrigerantInletTemperature)
    {
        TotalHeatTransfer_vec.push_back(totalHeatTransfer);
        std::cout << "The temperature of the battery is lower than or equal to the inlet temperature of the refrigerant in the evaporator." << std::endl;
        return;
    }

    // 4 Constantes termodinâmicas e parâmetros adimensionais constanstes
    double refrigerantSaturatedTemperature = CoolProp::PropsSI("T", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporEnthalpy = CoolProp::PropsSI("H", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporViscosity = CoolProp::PropsSI("V", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporSpecificHeat = CoolProp::PropsSI("C", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporThermalConductivity = CoolProp::PropsSI("L", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporPrandtlNumber = refrigerantVaporViscosity * refrigerantVaporSpecificHeat / refrigerantVaporThermalConductivity;

    // 6 Determinar o calor trocado em cada passe do condensador
    double Xl, Xu, Rl, Ru, R;
    double f, refrigerantConvectionCoefficient, refrigerantMl, refrigerantFinEfficiency, UA;
    double refrigerantReynoldsNumber;

    // 6.2 Determinar o calor trocado na região bifásica (só entra se for bifásico)
    // 6.2.1 Calcular a troca de calor necess�ria para que o refrigerante evapore completamente
    double Qem = argRefrigerantMassFlowRate * (refrigerantVaporEnthalpy - argRefrigerantInletEnthalpy);

    // 6.2.2 Calcular a troca de calor caso o refrigerante NÃO EVAPORE completamente
    Xe.at(0) = 1.0;
    UA = 1.0 / (moduleHeight / (moduleThermalConductivity * moduleLength * moduleWidth));
    Qe.at(0) = UA * (argBatteryTemperature - refrigerantSaturatedTemperature);

    if (Qe.at(0) <= Qem)
    {
        refrigerantOutletEnthalpy = argRefrigerantInletEnthalpy + Qe.at(0) / argRefrigerantMassFlowRate;
        refrigerantOutletTemperature = refrigerantSaturatedTemperature;
        totalHeatTransfer = Qe.at(0);
        TotalHeatTransfer_vec.push_back(totalHeatTransfer);
        return;
    }

    // 6.2.3 Calcular a troca de calor caso o refrigerante evapore completamente
    Xl = 0.0;
    Xu = 1.0;
    Rl = -Qem;
    Ru = Qe.at(0) - Qem;

    while (abs(Xu - Xl) > tolerance)
    {
        Xe.at(0) = (Xu + Xl) / 2.0;
        Qe.at(0) = (argBatteryTemperature - refrigerantSaturatedTemperature) / (moduleHeight / (moduleThermalConductivity * moduleLength * Xe.at(0) * moduleWidth));
        R = Qe.at(0) - Qem;

        if (R * Rl > 0)
        {
            Xl = Xe.at(0);
            Rl = R;

        }
        else if (R * Ru > 0)
        {
            Xu = Xe.at(0);
            Ru = R;
        }
        else
        {
            continue;
        }
    }

    // 6.3 Determinar o calor trocado na região de vapor superaquecido
    Xs.at(0) = (1.0 - Xe.at(0));
    refrigerantReynoldsNumber = 4.0 * (argRefrigerantMassFlowRate / (numberOfTubes.at(0).at(0) * numberOfChannels)) / (M_PI * channelHydraulicDiameter * refrigerantVaporViscosity);
    if (refrigerantReynoldsNumber < 3000.0)
    {
        refrigerantConvectionCoefficient = (refrigerantVaporThermalConductivity / channelHydraulicDiameter) * 4.36;
    }
    else
    {
        f = pow((0.79 * log(refrigerantReynoldsNumber) - 1.64), -2.0);
        refrigerantConvectionCoefficient = (refrigerantVaporThermalConductivity / channelHydraulicDiameter) * (f / 8.0) * (refrigerantReynoldsNumber - 1000.0) * refrigerantVaporPrandtlNumber / (1.0 + 12.7 * pow((f / 8.0), 0.5) * (pow(refrigerantVaporPrandtlNumber, 2.0 / 3.0) - 1.0));

    }
    refrigerantMl = (channelHeight / 2.0) * pow(2.0 * refrigerantConvectionCoefficient / (refrigerantVaporThermalConductivity * channelThickness), 0.5);
    refrigerantFinEfficiency = 1.0 - (1.0 - tanh(refrigerantMl) / refrigerantMl) * channelHeight / (channelHeight + channelWidth);
    UA = 1.0 / (moduleHeight / (moduleThermalConductivity * moduleLength * Xs.at(0) * moduleWidth) + 1.0 / (refrigerantFinEfficiency * refrigerantConvectionCoefficient * Xs.at(0) * channelHeatTransferArea * numberOfTubes.at(0).at(0)));
    Qs.at(0) = UA * (argBatteryTemperature - refrigerantSaturatedTemperature);
    refrigerantOutletEnthalpy = refrigerantVaporEnthalpy + Qs.at(0) / argRefrigerantMassFlowRate;
    refrigerantOutletTemperature = CoolProp::PropsSI("T", "P", argRefrigerantPressure, "H", refrigerantOutletEnthalpy, refrigerant);
    totalHeatTransfer = Qe.at(0) + Qs.at(0);
    TotalHeatTransfer_vec.push_back(totalHeatTransfer);

}
