#include "powertrain.h"



void PowerTrain::getDataFromFiles()
{
/*
    FileReader fileReader;

    // Definição do passo de tempo
    //mudar para o dT de Cabine
    fileReader.loadFile("../refrigerationSystem.dat");
    //timeStep = fileReader.readRealVariable("dt");
    timeStep = 20.0;
    fileReader.unloadFile();

    fileReader.loadFile("./cabin.dat");
    transmissionEfficiency = fileReader.readRealVariable("tr");
    fileReader.unloadFile();

    fileReader.loadFile("./powerTrain.dat");
    transmissionEfficiency = fileReader.readRealVariable("transmissionEfficiency");
    electricalEfficiency = fileReader.readRealVariable("electricalEfficiency");
    vehicleMass = fileReader.readRealVariable("vehicleMass");
    rotaryMassConversionCoefficient = fileReader.readRealVariable("rotaryMassConversionCoefficient");
    vehicleWindwardArea = fileReader.readRealVariable("vehicleWindwardArea");
    rollingResistanceCoefficient = fileReader.readRealVariable("rollingResistanceCoefficient");
    dragCoefficient = fileReader.readRealVariable("dragCoefficient");
    cellVoltage = fileReader.readRealVariable("cellVoltage");
    cellResistance = fileReader.readRealVariable("cellResistance");
    numberOfCellsInParallel = fileReader.readRealVariable("numberOfCellsInParallel");
    numberOfCellsInSeries = fileReader.readRealVariable("numberOfCellsInSeries");
    drivingCycle = fileReader.readRealMatrix("drivingCycle");

    volume = fileReader.readRealVariable("volume");
    c = fileReader.readRealVariable("c");
    initialTemperature = fileReader.readRealVariable("initialTemperature");
    fileReader.unloadFile();
*/

    c = 418.1638;
    volume = 0.09;
    transmissionEfficiency = 0.92;
    electricalEfficiency = 0.99;
    vehicleMass = 1710.0;
    rotaryMassConversionCoefficient = 1.4;
    vehicleWindwardArea = 2.38;
    rollingResistanceCoefficient = 0.015;
    dragCoefficient = 0.29;
    cellVoltage = 3.68;
    cellResistance = 0.93e-3;

    numberOfCellsInParallel = 1;
    numberOfCellsInSeries = 96;

    timeStep = 10.0;

    int segmentSize = numRows / 4;  // 1800 linhas divididas em 4 partes (450 cada)
    double startValue = 15.0;
    double endValue = 25.0;


    for (int i = 0; i < numRows; i++) {
        drivingCycle[i][0] = i;  // Índice de tempo

        // Fase 1: Aumenta de 10 para 20
        if (i < segmentSize) {
            drivingCycle[i][1] = startValue + (endValue - startValue) * (i / (double)segmentSize);
        }
        // Fase 2: Diminui de 10 para 20
        else if (i < 2 * segmentSize) {
            drivingCycle[i][1] = endValue - (endValue - startValue) * ((i - segmentSize) / (double)segmentSize);
        }
        // Fase 3: Aumenta de 10 para 20 novamente
        else if (i < 3 * segmentSize) {
            drivingCycle[i][1] = startValue + (endValue - startValue) * ((i - 2 * segmentSize) / (double)segmentSize);
        }
        // Fase 4: Diminui de 10 para 20 novamente
        else {
            drivingCycle[i][1] = endValue - (endValue - startValue) * ((i - 3 * segmentSize) / (double)segmentSize);
        }

    }


/*
    for (int i = 0; i < numRows; i++) {
        drivingCycle[i][0] = i;
        drivingCycle[i][1] = 23.90;
    }
*/

}

void PowerTrain::getDataFromUI(){

}

// Reference: Cen, J., Li, Z., & Jiang, F. (2018). Experimental investigation on using the electric vehicle air conditioning system for lithium-ion battery thermal management. Energy for sustainable development, 45, 88-95.
void PowerTrain::simulate(double argSpeed, double argAcceleration)
{
    outputPower = (1.0 / (transmissionEfficiency * electricalEfficiency)) *
                  (vehicleMass * 9.81 * rollingResistanceCoefficient +
                   0.5 * 1.2 * dragCoefficient * vehicleWindwardArea * pow(argSpeed, 2) +
                   rotaryMassConversionCoefficient * vehicleMass * argAcceleration) * argSpeed;

    moduleCurrent = outputPower / (numberOfCellsInSeries * cellVoltage);
    cellCurrent = moduleCurrent / numberOfCellsInParallel;

    // Cálculo da geração de calor (Qgen no outro código)
    moduleHeatRelease = (numberOfCellsInParallel * numberOfCellsInSeries) * (cellResistance * cellCurrent * cellCurrent);
    moduleHeatRelease_vec.push_back(moduleHeatRelease);

    return;
}

void PowerTrain::simulateCycle(double Tb, double totalHeatTransfer)
{
    std::ofstream outputFile;
    outputFile.open("output.dat");
    outputFile << "time [s]\tpower output [W]\theat released [W]\tcell current [A]\ttemperature [K]" << endl;

    //int timesteps = (drivingCycle.size());
    double temperature = Tb; // Temperatura inicial do arquivo .dat


    //for (int i = 0; i < timesteps; i++)
    //{
        double speed = drivingCycle[a][1];
        double acceleration;

        if (a == 0){
            acceleration = (drivingCycle[a + 1][1] - drivingCycle[a][1]) / (drivingCycle[a + 1][0] - drivingCycle[a][0]);
        }
        else
            acceleration = (drivingCycle[a][1] - drivingCycle[a - 1][1]) / (drivingCycle[a][0] - drivingCycle[a - 1][0]);

        simulate(speed, acceleration);

        // Variável Qloss sendo chamada de outra parte do código (battery evaporator)
        // double totalHeatTransfer = 0.0; // Placeholder (substituir pela chamada correta)



        // Atualização da temperatura (baseada no outro código)
        double delta_t = (moduleHeatRelease - totalHeatTransfer) / (volume * c);

        //double delta_t = (moduleHeatRelease - totalHeatTransfer) / (volume * C); C = kJ / Kg * K

        temperature += timeStep * delta_t;
        //Tb_vec.push_back(temperature);

        outputFile << drivingCycle[a][0] << "\t" << outputPower << "\t" << moduleHeatRelease << "\t" << cellCurrent << "\t" << temperature << endl;
    //}
        Tb_vec.push_back(temperature);
        a++;

    return;
}


