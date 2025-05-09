#include "evaporator.h"

void Evaporator::getDatafromFiles(){
    FileReader fileReader;

    fileReader.loadFile("refrigerationSystem.dat");
    refrigerant = fileReader.readStringVariable("fluid");
    fileReader.unloadFile();

    fileReader.loadFile("evaporator.dat");
    numberOfTubes = fileReader.readIntegerMatrix("numberOfPipes");
    numberOfPasses = (int)numberOfTubes.size();
    numberOfChannels = fileReader.readIntegerVariable("numberOfChannels");
    tubeLength = fileReader.readRealVariable("tubeLength");
    tubeWidth = fileReader.readRealVariable("tubeWidth");
    tubePitch = fileReader.readRealVariable("tubePitch");
    channelHeight = fileReader.readRealVariable("channelHeight");
    channelWidth = fileReader.readRealVariable("channelWidth");
    finDepth = fileReader.readRealVariable("finDepth");
    finHeight = fileReader.readRealVariable("finHeight");
    finPitch = fileReader.readRealVariable("finPitch");
    finThickness = fileReader.readRealVariable("finThickness");
    louverHeight = fileReader.readRealVariable("louverHeight");
    louverPitch = fileReader.readRealVariable("louverPitch");
    louverAngle = fileReader.readRealVariable("louverAngle");
    tolerance = fileReader.readRealVariable("tolerance");
    fileReader.unloadFile();

    // 3 Constantes geométricas
    for (int i = 0; i <= numberOfPasses - 1; i++)
    {
        totalNumberOfTubes += numberOfTubes[i][0];
    }
    numberOfFins = (int)floor(tubeLength / finPitch);
    channelHydraulicDiameter = 2 * channelHeight * channelWidth / (channelHeight + channelWidth);
    channelHeatTransferArea = 2 * numberOfChannels * (channelWidth + channelHeight) * tubeLength;
    finHeatTransferArea = 2 * numberOfFins * (finPitch - finThickness + finHeight) * finDepth;
    channelThickness = (tubeWidth - numberOfChannels * channelWidth) / (numberOfChannels + 1.0);
}





void Evaporator::simulate(double argAirMassFlowRate,
                          double argAirInletTemperature,
                          double argAirInletRelativeHumidity,
                          double argRefrigerantMassFlowRate,
                          double argRefrigerantPressure,
                          double argRefrigerantInletEnthalpy){
    // 1 inicializando as variaveis de interesse
    Xe.assign(numberOfPasses, 0.0);
    Xs.assign(numberOfPasses, 0.0);
    Qe.assign(numberOfPasses, 0.0);
    Qs.assign(numberOfPasses, 0.0);

    refrigerantOutletEnthalpy = 0.0;
    refrigerantOutletTemperature = 0.0;
    totalHeatTransfer = 0.0;

    // 2 verificando se o refrigerante vai aquecer
    double refrigerantInletTemperature ;// CoolProp::PropsSI("T", "P", argRefrigerantPressure, "H", argRefrigerantInletEnthalpy, refrigerant);
    if (argAirInletTemperature <= refrigerantInletTemperature){
        std::cout << "The inlet temperature of the air is lower than or equal to the inlet temperature of the refrigerant in the evaporator." << std::endl;
        return;
    }

    // 4 Constantes termodin�micas e par�metros adimensionais constanstes
    double waterVaporPressure = argAirInletRelativeHumidity * CoolProp::PropsSI("P", "T", argAirInletTemperature, "Q", 1.0, "water");
    double dewPoint = CoolProp::PropsSI("T", "P", waterVaporPressure, "Q", 1.0, "water");
    double refrigerantSaturatedTemperature = CoolProp::PropsSI("T", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporEnthalpy = CoolProp::PropsSI("H", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporViscosity = CoolProp::PropsSI("V", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporSpecificHeat = CoolProp::PropsSI("C", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporThermalConductivity = CoolProp::PropsSI("L", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporPrandtlNumber = refrigerantVaporViscosity * refrigerantVaporSpecificHeat / refrigerantVaporThermalConductivity;
    double airViscosity = HumidAir::HAPropsSI("M", "P", 101325, "T", argAirInletTemperature, "R", argAirInletRelativeHumidity);
    double airSpecificHeat = HumidAir::HAPropsSI("C", "P", 101325, "T", argAirInletTemperature, "R", argAirInletRelativeHumidity);
    double airThermalConductivity = HumidAir::HAPropsSI("K", "P", 101325, "T", argAirInletTemperature, "R", argAirInletRelativeHumidity);
    double airPrandtlNumber = airViscosity * airSpecificHeat / airThermalConductivity;

    // 5 Parâmetros de troca de calor com o ar
    // A correlação de Chang and Wang (1997) é válida para 100 < Re < 3000
    double airReynoldsNumber = 4.0 * louverPitch * argAirMassFlowRate / (M_PI * channelHydraulicDiameter * channelHydraulicDiameter * airViscosity * totalNumberOfTubes * (numberOfFins - 1));
    double airConvectionCoefficient = 0.0;
    /*if (refrigerantSaturatedTemperature < dewPoint && airReynoldsNumber < 300.0)
        airConvectionCoefficient = pow(airReynoldsNumber, 0.488) * pow(airPrandtlNumber, 1.0/3.0) * pow(louverAngle/90, 0.25) * pow(finPitch / louverPitch, -0.171) * pow(finHeight/ louverPitch, -0.29) * pow(tubeWidth / louverPitch, -0.248) * pow(louverHeight/ louverPitch, 0.68) * pow(tubePitch / louverPitch, -0.275) * pow(finThickness / louverPitch, -0.05) * (airThermalConductivity / louverPitch);
    else*/
    airConvectionCoefficient = pow(airReynoldsNumber, 0.51) * pow(airPrandtlNumber, 1.0 / 3.0) * pow(louverAngle / 90, 0.27) * pow(finPitch / louverPitch, -0.14) * pow(finHeight / louverPitch, -0.29) * pow(tubeWidth / louverPitch, -0.23) * pow(louverHeight / louverPitch, 0.68) * pow(tubePitch / louverPitch, -0.28) * pow(finThickness / louverPitch, -0.05) * (airThermalConductivity / louverPitch);
    double airMl = (finHeight / 2.0) * pow(2.0 * airConvectionCoefficient / (airThermalConductivity * finThickness), 0.5);
    double airFinEfficiency = 1.0 - (finHeight / (finPitch - finThickness + finHeight)) * (1.0 - tanh(airMl) / airMl);

    // 6 Determinar o calor trocado em cada passe do condensador
    double Xl, Xu, Rl, Ru, R;
    double NTU, Effectiveness;
    double f, refrigerantConvectionCoefficient, refrigerantMl, refrigerantFinEfficiency, UA, Cr;
    double passInletEnthalpy, passInletTemperature;
    double refrigerantReynoldsNumber;

    for (int i = 0; i <= numberOfPasses - 1; i++)
    {
        // 6.1 inicializar a entalpia de entrada do passe
        if (i == 0)
        {
            passInletEnthalpy = argRefrigerantInletEnthalpy;
            passInletTemperature = refrigerantInletTemperature;
        }
        else
        {
            passInletEnthalpy = refrigerantOutletEnthalpy;
            passInletTemperature = refrigerantOutletTemperature;
        }

        // 6.2 Determinar o calor trocado na região bifásica (só entra se for bifásico)
        if (passInletEnthalpy < refrigerantVaporEnthalpy)
        {
            // 6.2.1 Calcular a troca de calor necessária para que o refrigerante evapore completamente
            double Qem = (argRefrigerantMassFlowRate / numberOfTubes[i][0]) * (refrigerantVaporEnthalpy - passInletEnthalpy);

            // 6.2.2 Calcular a troca de calor caso o refrigerante NÃO EVAPORE completamente
            Xe[i] = 1.0;
            UA = airFinEfficiency * airConvectionCoefficient * finHeatTransferArea;
            NTU = UA / ((argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
            Effectiveness = 1.0 - exp(-NTU);
            Qe[i] = (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat * Effectiveness * (argAirInletTemperature - refrigerantSaturatedTemperature);

            if (Qe[i] <= Qem) {
                refrigerantOutletEnthalpy = passInletEnthalpy + Qe[i] * numberOfTubes[i][0] / argRefrigerantMassFlowRate;
                refrigerantOutletTemperature = CoolProp::PropsSI("T", "P", argRefrigerantPressure, "Q", 1.0, refrigerant);
                continue;
            }

            // 6.2.3 Calcular a troca de calor caso o refrigerante evapore completamente
            Xl = 0.0;
            Xu = 1.0;
            Rl = -Qem;
            Ru = Qe[i] - Qem;

            while (abs(Xu - Xl) > tolerance)
            {
                Xe[i] = (Xu + Xl) / 2.0;
                UA = airFinEfficiency * airConvectionCoefficient * Xe[i] * finHeatTransferArea;
                NTU = UA / (Xe[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
                Qe[i] = Xe[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat * Effectiveness * (argAirInletTemperature - refrigerantSaturatedTemperature);
                R = Qe[i] - Qem;

                if (R * Rl > 0)
                {
                    Xl = Xe[i];
                    Rl = R;

                }
                else if (R * Ru > 0)
                {
                    Xu = Xe[i];
                    Ru = R;
                }
                else
                {
                    continue;
                }
            }
        }

        // 6.3 Determinar o calor trocado na região de vapor superaquecido
        Xs[i] = (1.0 - Xe[i]);
        refrigerantReynoldsNumber = 4.0 * (argRefrigerantMassFlowRate / (numberOfTubes[i][0] * numberOfChannels)) / (M_PI * channelHydraulicDiameter * refrigerantVaporViscosity);
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
        UA = 1.0 / (1.0 / (refrigerantFinEfficiency * refrigerantConvectionCoefficient * Xs[i] * channelHeatTransferArea) + 1.0 / (airFinEfficiency * airConvectionCoefficient * Xs[i] * finHeatTransferArea));
        Cr = std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) / std::max((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
        NTU = UA / std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
        Effectiveness = 1.0 - exp((1.0 / Cr) * pow(NTU, 0.22) * (exp(-Cr * pow(NTU, 0.78)) - 1.0));
        Qs[i] = ( std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) * Effectiveness * (argAirInletTemperature - std::max(refrigerantSaturatedTemperature, passInletTemperature)));
        refrigerantOutletEnthalpy = std::max(passInletEnthalpy, refrigerantVaporEnthalpy) + Qs[i] / (argRefrigerantMassFlowRate / numberOfTubes[i][0]);
        refrigerantOutletTemperature = CoolProp::PropsSI("T", "P", argRefrigerantPressure, "H", refrigerantOutletEnthalpy, refrigerant);
    }

    for (int i = 0; i < numberOfPasses; i++)
    {
        totalHeatTransfer += numberOfTubes[i][0] * (Qe[i] + Qs[i]);
    }

    double airInletEnthalpy = HumidAir::HAPropsSI("H", "P", 101325, "T", argAirInletTemperature, "R", argAirInletRelativeHumidity);

    // só entra se houver desumidificação
    if (refrigerantSaturatedTemperature < dewPoint)
    {
        double waterLatentHeat = CoolProp::PropsSI("H", "T", argAirInletTemperature, "Q", 0.0, "water");
        double we = HumidAir::HAPropsSI("W", "P", 101325, "T", refrigerantSaturatedTemperature, "R", 1.0);
        double Te = refrigerantSaturatedTemperature;
        double w1 = HumidAir::HAPropsSI("W", "P", 101325, "T", argAirInletTemperature, "R", argAirInletRelativeHumidity);
        double T1 = argAirInletTemperature;
        double wl, wu, w;

        wl = we;
        airOutletEnthalpy = HumidAir::HAPropsSI("H", "P", 101325, "T", Te, "W", we);
        Rl = argAirMassFlowRate * ((airInletEnthalpy - airOutletEnthalpy) - (w1 - we) * waterLatentHeat) - totalHeatTransfer;
        wu = w1;
        airOutletEnthalpy = HumidAir::HAPropsSI("H", "P", 101325, "T", T1, "W", w1);
        Ru = argAirMassFlowRate * (airInletEnthalpy - airOutletEnthalpy) - totalHeatTransfer;

        while (std::abs(wu - wl) / wl > tolerance){
            w = (wu + wl) / 2.0;
            airOutletTemperature = (T1 - Te) / (w1 - we) * (w - we) + Te;
            airOutletEnthalpy = HumidAir::HAPropsSI("H", "P", 101325, "T", airOutletTemperature, "W", w);
            R = argAirMassFlowRate * ((airInletEnthalpy - airOutletEnthalpy) - (w1 - w) * waterLatentHeat) - totalHeatTransfer;
            if (R * Rl > 0)
            {
                wl = w;
                Rl = R;
            }
            else if (R * Ru > 0)
            {
                wu = w;
                Ru = R;
            }
            else
            {
                continue;
            }
        }

        airOutletRelativeHumidity = HumidAir::HAPropsSI("R", "P", 101325, "H", airOutletEnthalpy, "W", w);
    }
    else {
        double w = HumidAir::HAPropsSI("W", "P", 101325, "T", argAirInletTemperature, "R", argAirInletRelativeHumidity);
        airOutletEnthalpy = airInletEnthalpy - totalHeatTransfer / argAirMassFlowRate;
        airOutletRelativeHumidity = HumidAir::HAPropsSI("R", "P", 101325, "H", airOutletEnthalpy, "W", w);
    }
}

void Evaporator::getDatafromUI(){

}
