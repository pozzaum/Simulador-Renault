#include "condenser.h"

void Condenser::getDataFromFiles(){
    FileReader fileReader;

    fileReader.loadFile("./refrigerationSystem.dat");
    refrigerant = fileReader.readStringVariable("fluid");
    fileReader.unloadFile();

    fileReader.loadFile("condenser.dat");
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

    totalNumberOfTubes = 0;
    // 3 Constantes geométricas
    for (int i = 0; i < numberOfPasses; i++) {
        totalNumberOfTubes += numberOfTubes[i][0];
    }
    numberOfFins = (int)floor(tubeLength / finPitch);
    channelHydraulicDiameter = 2 * channelHeight * channelWidth / (channelHeight + channelWidth);
    channelHeatTransferArea = 2 * numberOfChannels * (channelWidth + channelHeight) * tubeLength;
    finHeatTransferArea = 2 * numberOfFins * (finPitch - finThickness + finHeight) * finDepth;
    channelThickness = (tubeWidth - numberOfChannels * channelWidth) / (numberOfChannels + 1.0);
}

void Condenser::simulate(double argAirMassFlowRate, double argAirInletTemperature, double argRefrigerantMassFlowRate, double argPressure, double argRefrigerantInletEnthalpy){
    // 1 inicializando as variaveis de interesse
    Xe.assign(numberOfPasses, 0.0);
    Xc.assign(numberOfPasses, 0.0);
    Xs.assign(numberOfPasses, 0.0);
    Qe.assign(numberOfPasses, 0.0);
    Qc.assign(numberOfPasses, 0.0);
    Qs.assign(numberOfPasses, 0.0);

    refrigerantOutletEnthalpy = 0.0;
    refrigerantOutletTemperature = 0.0;
    totalHeatTransfer = 0.0;

    // 2 verificando se o refrigerante vai resfriar
    double refrigerantInletTemperature = CoolProp::PropsSI("T", "P", argPressure, "H", argRefrigerantInletEnthalpy, refrigerant);
    if (argAirInletTemperature >= refrigerantInletTemperature) {
        std::cout << "The inlet temprature of the air is higher than or equal to the inlet temperature of the refrigerant in the condenser." << std::endl;
        return;
    }

    // 4 Constantes termodinâmicas e parâmetros adimensionais constanstes
    double refrigerantSaturatedTemperature = CoolProp::PropsSI("T", "P", argPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporEnthalpy = CoolProp::PropsSI("H", "P", argPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporViscosity = CoolProp::PropsSI("V", "P", argPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporSpecificHeat = CoolProp::PropsSI("C", "P", argPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporThermalConductivity = CoolProp::PropsSI("L", "P", argPressure, "Q", 1.0, refrigerant);
    double refrigerantVaporPrandtlNumber = refrigerantVaporViscosity * refrigerantVaporSpecificHeat / refrigerantVaporThermalConductivity;
    double refrigerantLiquidEnthalpy = CoolProp::PropsSI("H", "P", argPressure, "Q", 0.0, refrigerant);
    double refrigerantLiquidViscosity = CoolProp::PropsSI("V", "P", argPressure, "Q", 0.0, refrigerant);
    double refrigerantLiquidSpecificHeat = CoolProp::PropsSI("C", "P", argPressure, "Q", 0.0, refrigerant);
    double refrigerantLiquidThermalConductivity = CoolProp::PropsSI("L", "P", argPressure, "Q", 0.0, refrigerant);
    double refrigerantLiquidPrandtlNumber = refrigerantLiquidViscosity * refrigerantLiquidSpecificHeat / refrigerantLiquidThermalConductivity;
    double airViscosity = CoolProp::PropsSI("V", "P", 101325, "T", argAirInletTemperature, "air");
    double airSpecificHeat = CoolProp::PropsSI("C", "P", 101325, "T", argAirInletTemperature, "air");
    double airThermalConductivity = CoolProp::PropsSI("L", "P", 101325, "T", argAirInletTemperature, "air");
    double airPrandtlNumber = airViscosity * airSpecificHeat / airThermalConductivity;

    // 5 Parâmetros de troca de calor com o ar
    // A correlação de Chang and Wang (1997) é válida para 100 < Re < 3000
    double airReynoldsNumber = 4.0 * louverPitch * argAirMassFlowRate / (M_PI * channelHydraulicDiameter * channelHydraulicDiameter * airViscosity * totalNumberOfTubes * (numberOfFins - 1));
    double airConvectionCoefficient = pow(airReynoldsNumber, 0.51) * pow(airPrandtlNumber, 1.0/3.0) * pow(louverAngle/90, 0.27) * pow(finPitch / louverPitch, -0.14) * pow(finHeight/ louverPitch, -0.29) * pow(tubeWidth / louverPitch, -0.23) * pow(louverHeight/ louverPitch, 0.68) * pow(tubePitch / louverPitch, -0.28) * pow(finThickness / louverPitch, -0.05) * (airThermalConductivity / louverPitch);
    double airMl = (finHeight / 2.0) * pow(2.0 * airConvectionCoefficient / (airThermalConductivity * finThickness), 0.5);
    double airFinEfficiency = 1.0 - (finHeight / (finPitch - finThickness + finHeight)) * (1.0 - tanh(airMl) / airMl);

    // 6 Determinar o calor trocado em cada passe do condensador
    double Xl, Xu, Rl, Ru, R;
    double NTU, Effectiveness;
    double f, refrigerantConvectionCoefficient, refrigerantMl, refrigerantFinEfficiency, UA, Cr;
    double passInletEnthalpy, passInletTemperature;
    double refrigerantReynoldsNumber;

    for (int i = 0; i < numberOfPasses; i++) {
        // 6.1 inicializar a entalpia de entrada do passe
        if (i == 0) {
            passInletEnthalpy = argRefrigerantInletEnthalpy;
            passInletTemperature = refrigerantInletTemperature;
        } else {
            passInletEnthalpy = refrigerantOutletEnthalpy;
            passInletTemperature = refrigerantOutletTemperature;
        }

        // 6.2 Determinar o calor trocado na região de vapor superaquecido(só entra se for superquecido)
        if (passInletEnthalpy > refrigerantVaporEnthalpy) {
            // 6.2.1 Calcular a troca de calor necessária para que o fluido comece a condensar
            double Qdm = (argRefrigerantMassFlowRate / numberOfTubes[i][0]) * (passInletEnthalpy - refrigerantVaporEnthalpy);

            // 6.2.2 Calcular a troca de calor caso o fluido NÃO INICIE a condensação
            Xe[i] = 1.0;
            refrigerantReynoldsNumber = 4.0 * (argRefrigerantMassFlowRate / (numberOfTubes[i][0] * numberOfChannels)) / (M_PI * channelHydraulicDiameter * refrigerantVaporViscosity);
            if (refrigerantReynoldsNumber < 3000.0)
            {
                refrigerantConvectionCoefficient = (refrigerantVaporThermalConductivity / channelHydraulicDiameter) * 4.36;
            } else {
                f = pow((0.79 * log(refrigerantReynoldsNumber) - 1.64), -2.0);
                refrigerantConvectionCoefficient = (f / 8.0) * (refrigerantReynoldsNumber - 1000.0) * refrigerantVaporPrandtlNumber / (1.0 + 12.7 * pow((f / 8.0), 0.5) * (pow(refrigerantVaporPrandtlNumber, 2.0 / 3.0) - 1.0)) * (refrigerantVaporThermalConductivity / channelHydraulicDiameter);

            }
            refrigerantMl = (channelHeight / 2.0) * pow(2.0 * refrigerantConvectionCoefficient / (refrigerantVaporThermalConductivity * channelThickness), 0.5);
            refrigerantFinEfficiency = 1.0 - (channelHeight / (channelHeight + channelWidth) * (1.0 - tanh(refrigerantMl) / refrigerantMl));
            UA = 1.0 / (1.0 / (refrigerantFinEfficiency * refrigerantConvectionCoefficient * channelHeatTransferArea) + 1.0 / (airFinEfficiency * airConvectionCoefficient * finHeatTransferArea));
            Cr = std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) / std::max((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
            NTU = UA / std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
            Effectiveness = 1.0 - exp((1.0 / Cr) * pow(NTU, 0.22) * (exp(-Cr * pow(NTU, 0.78)) - 1.0));
            Qe[i] = std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) * Effectiveness * (passInletTemperature - argAirInletTemperature);

            if (Qe[i] <= Qdm) {
                refrigerantOutletEnthalpy = passInletEnthalpy - Qe[i] / (argRefrigerantMassFlowRate / numberOfTubes[i][0]);
                refrigerantOutletTemperature = CoolProp::PropsSI("T", "P", argPressure, "H", refrigerantOutletEnthalpy, refrigerant);
                continue;

            }

            // 6.2.3 Calcular a troca de calor caso o fluido INICIE a condensação
            Xl = 0.0;
            Xu = 1.0;
            Rl = -Qdm;
            Ru = Qe[i] - Qdm;

            while (abs(Xu - Xl) > tolerance) {
                Xe[i] = (Xu + Xl) / 2;
                UA = 1.0 / (1.0 / (refrigerantFinEfficiency * refrigerantConvectionCoefficient * Xe[i] * channelHeatTransferArea) + 1.0 / (airFinEfficiency * airConvectionCoefficient * Xe[i] * finHeatTransferArea));
                Cr = std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xe[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) / std::max((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xe[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
                NTU = UA / std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xe[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
                Effectiveness = 1.0 - exp((1.0 / Cr) * pow(NTU, 0.22) * (exp(-Cr * pow(NTU, 0.78)) - 1.0));
                Qe[i] = std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantVaporSpecificHeat, Xe[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) * Effectiveness * (passInletTemperature - argAirInletTemperature);
                R = Qe[i] - Qdm;

                if (R * Rl > 0) {
                    Xl = Xe[i];
                    Rl = R;
                }
                else if (R * Ru > 0) {
                    Xu = Xe[i];
                    Ru = R;
                }
                else
                {
                    continue;
                }
            }
        }

        // 6.3 Determinar o calor trocado na região bifásica(só entra se for bifásico)
        if (passInletEnthalpy > refrigerantLiquidEnthalpy) {
            // 6.3.1 Calcular a troca de calor necessária para que o refrigerante condense completamente
            double Qcm = (argRefrigerantMassFlowRate / numberOfTubes[i][0]) * std::min(refrigerantVaporEnthalpy - refrigerantLiquidEnthalpy, passInletEnthalpy - refrigerantLiquidEnthalpy);

            // 6.3.2 Calcular a troca de calor caso o refrigerante NÃO CONDENSE completamente
            Xc[i] = ( 1 - Xe[i]);
            UA = airFinEfficiency * airConvectionCoefficient * Xc[i] * finHeatTransferArea;
            NTU = UA / (Xc[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
            Effectiveness = 1.0 - exp(-NTU);
            Qc[i] = ( Xc[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat * Effectiveness * (refrigerantSaturatedTemperature - argAirInletTemperature));

            if (Qc[i] <= Qcm) {
                refrigerantOutletEnthalpy = std::min(refrigerantVaporEnthalpy, passInletEnthalpy) - Qc[i] * numberOfTubes[i][0] / argRefrigerantMassFlowRate;
                refrigerantOutletTemperature = refrigerantSaturatedTemperature;
                continue;
            }

            // 6.3.3 Calcular a troca de calor caso o refrigerante condense completamente
            Xl = 0;
            Xu = 1 - Xe[i];
            Rl = -Qcm;
            Ru = Qc[i] - Qcm;

            while (abs(Xu - Xl) > tolerance) {
                Xc[i] = (Xu + Xl) / 2;
                UA = airFinEfficiency * airConvectionCoefficient * Xc[i] * finHeatTransferArea;
                NTU = UA / (Xc[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
                Qc[i] = Xc[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat * Effectiveness * (refrigerantSaturatedTemperature - argAirInletTemperature);
                R = Qc[i] - Qcm;

                if (R * Rl > 0) {
                    Xl = Xc[i];
                    Rl = R;

                } else if (R * Ru > 0) {
                    Xu = Xc[i];
                    Ru = R;
                } else {
                    continue;
                }
            }
        }

        // 6.4 Determinar o calor trocado na região de líquido sub-resfriado
        Xs[i] = (1 - Xe[i] - Xc[i]);
        refrigerantReynoldsNumber = 4 * (argRefrigerantMassFlowRate / (numberOfTubes[i][0] * numberOfChannels)) / (M_PI * channelHydraulicDiameter * refrigerantLiquidViscosity);
        if (refrigerantReynoldsNumber < 3000.0) {
            refrigerantConvectionCoefficient = (refrigerantLiquidThermalConductivity / channelHydraulicDiameter) * 4.36;
        } else {
            f = pow((0.79 * log(refrigerantReynoldsNumber) - 1.64), -2.0);
            refrigerantConvectionCoefficient = (refrigerantLiquidThermalConductivity / channelHydraulicDiameter) * (f / 8.0) * (refrigerantReynoldsNumber - 1000.0) * refrigerantLiquidPrandtlNumber / (1.0 + 12.7 * pow((f / 8.0), 0.5) * (pow(refrigerantLiquidPrandtlNumber, 2.0 / 3.0) - 1.0));
        }
        refrigerantMl = (channelHeight / 2.0) * pow(2.0 * refrigerantConvectionCoefficient / (refrigerantLiquidThermalConductivity * channelThickness), 0.5);
        refrigerantFinEfficiency = 1.0 - (1 - tanh(refrigerantMl) / refrigerantMl) * channelHeight / (channelHeight + channelWidth);
        UA = 1.0 / (1.0 / (refrigerantFinEfficiency * refrigerantConvectionCoefficient * Xs[i] * channelHeatTransferArea) + 1.0 / (airFinEfficiency * airConvectionCoefficient * Xs[i] * finHeatTransferArea));
        Cr = std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantLiquidSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) / std::max((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantLiquidSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
        NTU = UA / std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantLiquidSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat);
        Effectiveness = 1.0 - exp((1.0 / Cr) * pow(NTU, 0.22) * (exp(-Cr * pow(NTU, 0.78)) - 1.0));
        Qs[i] = ( std::min((argRefrigerantMassFlowRate / numberOfTubes[i][0]) * refrigerantLiquidSpecificHeat, Xs[i] * (argAirMassFlowRate / totalNumberOfTubes) * airSpecificHeat) * Effectiveness * (std::min(refrigerantSaturatedTemperature, passInletTemperature) - argAirInletTemperature));
        refrigerantOutletEnthalpy = std::min(passInletEnthalpy, refrigerantLiquidEnthalpy) - Qs[i] / (argRefrigerantMassFlowRate / numberOfTubes[i][0]);
        refrigerantOutletTemperature = CoolProp::PropsSI("T", "P", argPressure, "H", refrigerantOutletEnthalpy, refrigerant);
    }

    double airInletEnthalpy = CoolProp::PropsSI("H", "P", 101325, "T", argAirInletTemperature, "air");
    double airOutletEnthalpy = (argRefrigerantMassFlowRate * (argRefrigerantInletEnthalpy - refrigerantOutletEnthalpy)) / argAirMassFlowRate + airInletEnthalpy;
    airOutletTemperature = CoolProp::PropsSI("T", "P", 101325, "H", airOutletEnthalpy, "air");

    for (int i = 0; i < numberOfPasses; i++) {
        totalHeatTransfer += numberOfTubes[i][0] * (Qe[i] + Qc[i] + Qs[i]);
    }
}
