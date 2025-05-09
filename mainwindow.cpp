#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    getDataFromFiles();

/*
    QThread workerThread;
    WebSocketWorker worker;
    worker.moveToThread(&workerThread);
    worker.start(QUrl("ws://localhost:12345"));

    QObject::connect(&worker, &WebSocketWorker::messageReceived, this, &MainWindow::ws_handler);
    QObject::connect(&worker, &WebSocketWorker::binaryReceived, this, &MainWindow::ws_handler);
    workerThread.start();
*/
#ifdef ALL
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
#endif

#ifdef CABIN
    ui->inputs_comp->setEnabled(false);
    ui->inputs_comp->setVisible(false);
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
    ui->inputs_batevap->setEnabled(false);
    ui->inputs_batevap->setVisible(false);
    ui->inputs_cond->setEnabled(false);
    ui->inputs_cond->setVisible(false);
    ui->inputs_doubevap->setEnabled(false);
    ui->inputs_doubevap->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif

#ifdef POWERTRAIN
    ui->inputs_comp->setEnabled(false);
    ui->inputs_comp->setVisible(false);
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
    ui->inputs_batevap->setEnabled(false);
    ui->inputs_batevap->setVisible(false);
    ui->inputs_cond->setEnabled(false);
    ui->inputs_cond->setVisible(false);
    ui->inputs_doubevap->setEnabled(false);
    ui->inputs_doubevap->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif

#ifdef COMPRESSOR
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
    ui->inputs_batevap->setEnabled(false);
    ui->inputs_batevap->setVisible(false);
    ui->inputs_cond->setEnabled(false);
    ui->inputs_cond->setVisible(false);
    ui->inputs_doubevap->setEnabled(false);
    ui->inputs_doubevap->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif
#ifdef EXPDEVICE
    ui->inputs_comp->setEnabled(false);
    ui->inputs_comp->setVisible(false);
    ui->inputs_batevap->setEnabled(false);
    ui->inputs_batevap->setVisible(false);
    ui->inputs_cond->setEnabled(false);
    ui->inputs_cond->setVisible(false);
    ui->inputs_doubevap->setEnabled(false);
    ui->inputs_doubevap->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif
#ifdef BATEVAP
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
    ui->inputs_comp->setEnabled(false);
    ui->inputs_comp->setVisible(false);
    ui->inputs_cond->setEnabled(false);
    ui->inputs_cond->setVisible(false);
    ui->inputs_doubevap->setEnabled(false);
    ui->inputs_doubevap->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif
#ifdef CONDENSER
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
    ui->inputs_comp->setEnabled(false);
    ui->inputs_comp->setVisible(false);
    ui->inputs_batevap->setEnabled(false);
    ui->inputs_batevap->setVisible(false);
    ui->inputs_doubevap->setEnabled(false);
    ui->inputs_doubevap->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif
#if defined(HXC) || defined(DOUBLEEVAP)
    ui->inputs_expdev->setEnabled(false);
    ui->inputs_expdev->setVisible(false);
    ui->inputs_batevap->setEnabled(false);
    ui->inputs_batevap->setVisible(false);
    ui->inputs_cond->setEnabled(false);
    ui->inputs_cond->setVisible(false);
    ui->inputs_comp->setEnabled(false);
    ui->inputs_comp->setVisible(false);
    ui->inputs_all_expdev->setEnabled(false);
    ui->inputs_all_expdev->setVisible(false);
#endif
}



void MainWindow::getDataFromFiles(){
    FileReader fileReader;

    if(!fileReader.loadFile("../refrigerationSystem.dat")){
        QMessageBox message(ui->centralwidget);
        message.addButton(QMessageBox::Ok);
        message.setText("Arquivo 'refrigerationSystem.dat' não encontrado");
        message.setFixedSize(300,100);
        message.exec();
    }
    fluid = fileReader.readStringVariable("fluid");
    dTsub = fileReader.readRealVariable("dTsub");
    dTsup = fileReader.readRealVariable("dTsup");
    tolerance = fileReader.readRealVariable("tolerance");
    N = fileReader.readRealVariable("N");
    mac = fileReader.readRealVariable("mac");
    Tac = fileReader.readRealVariable("Tac") + 273.15;
    //ALTERACAO
    mae = fileReader.readRealVariable("mae");
    //mae = fileReader.readRealVariable("mae") / 2;

    Tae = fileReader.readRealVariable("Tae") + 273.15;
    wae = fileReader.readRealVariable("wae");

    //ALTERACAO
    xc = fileReader.readRealVariable("xc");  //percentual de abertura
    //xc = 0.58;
    //xc = 0.41;

    //ALTERACAO
    //xb = fileReader.readRealVariable("xb");
    xb = 0.0;

    Tb = fileReader.readRealVariable("Tb") + 273.15;
    ui->refsystem_fluid->setText(QString::fromUtf8(fluid));
    ui->refsystem_dtsub->setText(QString::number(dTsub));
    ui->refsystem_dtsup->setText(QString::number(dTsup));
    ui->refsystem_tolerance->setText(QString::number(tolerance));
    ui->refsystem_n->setText(QString::number(N));
    ui->refsystem_mac->setText(QString::number(mac));
    ui->refsystem_tac->setText(QString::number(Tac));
    ui->refsystem_mae->setText(QString::number(mae));
    ui->refsystem_tae->setText(QString::number(Tae));
    ui->refsystem_wae->setText(QString::number(wae));
    ui->refsystem_xc->setText(QString::number(xc));
    ui->refsystem_xb->setText(QString::number(xb));
    ui->refsystem_tb->setText(QString::number(Tb));

    //QString string_numofPipes = "";
    std::vector<std::vector<int>> vector_numofPipes;

#ifdef ALL
    Te = fileReader.readRealVariable("Te") + 273.15;
    Tc = fileReader.readRealVariable("Tc") + 273.15;
    fileReader.unloadFile();
    ui->refsystem_te->setText(QString::number(Te));
    ui->refsystem_tc->setText(QString::number(Tc));
    cab.getDataFromFiles();
    //powertrain.getDataFromFiles();
    //batteryEvaporator.getDataFromFiles();
    //doubleEvaporator.getDataFromFiles();
    expansionDeviceBattery.getDataFromFiles();
    expansionDeviceCabin.getDataFromFiles();
    ui->cabexpdev_oridiameter->setText(QString::number(expansionDeviceCabin.getOriDiameter()));
    ui->cabexpdev_flowcoeff->setText(QString::number(expansionDeviceCabin.getFlowCoefficient()));
    ui->batexpdev_oridiameter->setText(QString::number(expansionDeviceBattery.getOriDiameter()));
    ui->batexpdev_flowcoeff->setText(QString::number(expansionDeviceBattery.getFlowCoefficient()));
#endif

#if defined(HXC) || defined(DOUBLEEVAP) || defined(ALL)
    doubleEvaporator.getDataFromFiles();
    list_numofPipes.clear();
    vector_numofPipes = doubleEvaporator.getNumofPipes();
    for(size_t i = 0; i < vector_numofPipes.size(); i++){
        for(size_t j = 0; j < vector_numofPipes.at(i).size(); j++){
            list_numofPipes << QString::number(vector_numofPipes.at(i).at(j));
        }
    }
    ui->doubevap_numtubes->setText(list_numofPipes.join(" | "));
    ui->doubevap_numchannels->setText(QString::number(doubleEvaporator.getNumofChannels()));
    ui->doubevap_tubelength->setText(QString::number(doubleEvaporator.getTubeLength()));
    ui->doubevap_tubewidth->setText(QString::number(doubleEvaporator.getTubeWidth()));
    ui->doubevap_tubepitch->setText(QString::number(doubleEvaporator.getTubeWidth()));
    ui->doubevap_chanheight->setText(QString::number(doubleEvaporator.getChannelHeight()));
    ui->doubevap_chanwidth->setText(QString::number(doubleEvaporator.getChannelWidth()));
    ui->doubevap_findepth->setText(QString::number(doubleEvaporator.getFinDepth()));
    ui->doubevap_finheight->setText(QString::number(doubleEvaporator.getFinDepth()));
    ui->doubevap_finpitch->setText(QString::number(doubleEvaporator.getFinPitch()));
    ui->doubevap_finthick->setText(QString::number(doubleEvaporator.getFinThickness()));
    ui->doubevap_louverheight->setText(QString::number(doubleEvaporator.getLouverHeight()));
    ui->doubevap_louverpitch->setText(QString::number(doubleEvaporator.getLouverPitch()));
    ui->doubevap_louverangle->setText(QString::number(doubleEvaporator.getLouverAngle()));
    ui->doubevap_tolerance->setText(QString::number(doubleEvaporator.getTolerance()));
#endif

#if defined(COMPRESSOR) || defined(ALL)
    compressor.getDataFromFiles();
    ui->comp_sweptvol->setText(QString::number(compressor.getSweptVolume()));
    ui->comp_volefficiency->setText(QString::fromUtf8(compressor.getVolEfficiency()));
    ui->comp_globefficiency->setText(QString::fromUtf8(compressor.getGlobalEfficiency()));
    ui->comp_therconduc->setText(QString::number(compressor.getThermalConductance()));
    ui->comp_ambtemp->setText(QString::number(compressor.getAmbientTemperature()));
#endif

#if defined(CONDENSER) || defined(ALL)
    condenser.getDataFromFiles();
    list_numofPipes.clear();
    vector_numofPipes.clear();
    vector_numofPipes = condenser.getNumofPipes();
    for(size_t i = 0; i < vector_numofPipes.size(); i++){
        for(size_t j = 0; j < vector_numofPipes.at(i).size(); j++){
            list_numofPipes << QString::number(vector_numofPipes.at(i).at(j));
        }
    }
    ui->cond_numtubes->setText(list_numofPipes.join(" | "));
    ui->cond_numchannels->setText(QString::number(condenser.getNumofChannels()));
    ui->cond_tubelength->setText(QString::number(condenser.getTubeLength()));
    ui->cond_tubewidth->setText(QString::number(condenser.getTubeWidth()));
    ui->cond_tubepitch->setText(QString::number(condenser.getTubeWidth()));
    ui->cond_chanheight->setText(QString::number(condenser.getChannelHeight()));
    ui->cond_chanwidth->setText(QString::number(condenser.getChannelWidth()));
    ui->cond_findepth->setText(QString::number(condenser.getFinDepth()));
    ui->cond_finheight->setText(QString::number(condenser.getFinDepth()));
    ui->cond_finpitch->setText(QString::number(condenser.getFinPitch()));
    ui->cond_finthick->setText(QString::number(condenser.getFinThickness()));
    ui->cond_louverheight->setText(QString::number(condenser.getLouverHeight()));
    ui->cond_louverpitch->setText(QString::number(condenser.getLouverPitch()));
    ui->cond_louverangle->setText(QString::number(condenser.getLouverAngle()));
    ui->cond_tolerance->setText(QString::number(condenser.getTolerance()));
#endif

#if defined(BATEVAP) || defined(ALL)
    batteryEvaporator.getDataFromFiles();

    list_numofPipes.clear();
    vector_numofPipes.clear();
    vector_numofPipes = batteryEvaporator.getNumofPipes();
    for(size_t i = 0; i < vector_numofPipes.size(); i++){
        for(size_t j = 0; j < vector_numofPipes.at(i).size(); j++){
            list_numofPipes << QString::number(vector_numofPipes.at(i).at(j));
        }
    }
    ui->batevap_numtubes->setText(list_numofPipes.join(" | "));
    ui->batevap_numchannels->setText(QString::number(batteryEvaporator.getNumofChannels()));
    ui->batevap_tubelength->setText(QString::number(batteryEvaporator.getTubeLength()));
    ui->batevap_tubewidth->setText(QString::number(batteryEvaporator.getTubeWidth()));
    ui->batevap_chanheight->setText(QString::number(batteryEvaporator.getChannelHeight()));
    ui->batevap_chanwidth->setText(QString::number(batteryEvaporator.getChannelWidth()));
    ui->batevap_modwidth->setText(QString::number(batteryEvaporator.getModuleWidth()));
    ui->batevap_modlength->setText(QString::number(batteryEvaporator.getModuleLength()));
    ui->batevap_modheight->setText(QString::number(batteryEvaporator.getModuleHeight()));
    ui->batevap_modtherconductivity->setText(QString::number(batteryEvaporator.getModTherConductivity()));
    ui->batevap_tolerance->setText(QString::number(batteryEvaporator.getTolerance()));
#endif

#ifdef EXPDEVICE
    expansionDevice.getDataFromFiles();
    ui->expdev_oridiameter->setText(QString::number(std::pow((expansionDevice.getFlowArea() * 4 / M_PI), 0.5)));
    ui->expdev_flowcoeff->setText(QString::number(expansionDevice.getFlowCoefficient()));
    // Te = fileReader.readRealVariable("Te") + 273.15;
    // Tc = fileReader.readRealVariable("Tc") + 273.15;
#endif

#ifdef CABIN
    cab.getDataFromFiles();
#endif

#if defined(POWERTRAIN) || defined(ALL)
    powertrain.getDataFromFiles();
#endif
}

#if defined(MQTTCONNECT) || defined(ALL)

#endif


MainWindow::~MainWindow()
{
#if defined(MQTTCONNECT) || defined(ALL)
    delete mqttWorker;
#endif
    delete ui;
}


void MainWindow::on_loadData_clicked() {
    getDataFromFiles();
}

void MainWindow::on_apply_data_changes_clicked(){

}


void MainWindow::on_btnConnectMqtt_clicked()
{
    mqttWorker = new MyMqtt(); // criado na main thread
    mqttWorker->setParent(this);
    mqttWorker->createClient();    // também chamado na main thread!
    mqttWorker->connectToBroker(); // main thread com QApplication ativa

}


void MainWindow::on_simulate_clicked(QJsonDocument dado) {
#ifdef COMPRESSOR
    double Pe, Pc, Tsl, N, h1;

    std::cout << std::fixed;
    std::cout.precision(2);

    N = 1035.0;
    Pe = 2.99e5;
    Pc = 9.99e5;
    Tsl = 25.71;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 1530.0;
    Pe = 3.01e5;
    Pc = 10.00e5;
    Tsl = 25.30;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 3015.0;
    Pe = 3.00e5;
    Pc = 10.00e5;
    Tsl = 25.16;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 4995.0;
    Pe = 3.00e5;
    Pc = 10.00e5;
    Tsl = 25.36;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 1035.0;
    Pe = 3.00e5;
    Pc = 14.99e5;
    Tsl = 25.28;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 1530.0;
    Pe = 3.02e5;
    Pc = 14.98e5;
    Tsl = 26.45;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 3015.0;
    Pe = 3.00e5;
    Pc = 15.01e5;
    Tsl = 25.20;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 4995.0;
    Pe = 3.00e5;
    Pc = 15.01e5;
    Tsl = 25.19;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

    N = 7020.0;
    Pe = 3.00e5;
    Pc = 15.00e5;
    Tsl = 25.31;
    h1 = CoolProp::PropsSI("H", "P", Pe, "T", Tsl + 273.15, "R134a");
    compressor.simulate(Pe, Pc, h1, N / 60.0);
    MostrarResComp(Pe, Pc, N);

#endif

#ifdef CONDENSER
    h1 = CoolProp::PropsSI("H", "P", 11.55e5, "T", 273.15 + 96.4, "R134a");
    condenser.simulate(0.576, 273.15 + 30.1, 5.80e-3, 11.55e5, h1);
    MostrarResCond(1000);

    h1 = CoolProp::PropsSI("H", "P", 11.75e5, "T", 273.15 + 101.5, "R134a");
    condenser.simulate(0.576, 273.15 + 30.9, 6.2e-3, 11.75e5, h1);
    MostrarResCond(1200);

    h1 = CoolProp::PropsSI("H", "P", 12.01e5, "T", 273.15 + 108.1, "R134a");
    condenser.simulate(0.576, 273.15 + 32.1, 6.5e-3, 12.01e5, h1);
    MostrarResCond(1400);

    h1 = CoolProp::PropsSI("H", "P", 12.45e5, "T", 273.15 + 110.7, "R134a");
    condenser.simulate(0.576, 273.15 + 33.3, 6.85e-3, 12.45e5, h1);
    MostrarResCond(1600);

#endif

#ifdef BATEVAP
    double hin = CoolProp::PropsSI("H", "P", 305.0e3, "Q", 0.383, "R134a");
    batteryEvaporator.simulate(35.0 + 273.15, 0.03, 305.0e3, hin);

    batteryEvaporator.simulate(35.0 + 273.15, 0.0, 305.0e3, hin);
#endif

#ifdef EXPDEVICE
    std::cout << std::fixed;
    std::cout.precision(2);

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            Pe = CoolProp::PropsSI("P", "T", Te[i] + 273.15, "Q", 0.0, "R134a");
            Pc = CoolProp::PropsSI("P", "T", Tc[j] + 273.15, "Q", 0.0, "R134a");
            h1 = CoolProp::PropsSI("H", "P", Pe, "Q", 1.0, "R134a");
            h3 = CoolProp::PropsSI("H", "P", Pc, "Q", 0.0, "R134a");

            expansionDevice.simulate(Pc, Pe, h3, 1.0);
            Qe = expansionDevice.getMassFlowRate() * (h1 - h3);

            resText.append("Te = " + QString::number(Te[i]) + " C\n" + "Tc = " + QString::number(Tc[j]) + " C\n");
            resText.append("Qe = " + QString::number(Qe / 1000.0) + " kW\n\n");
            std::cout << "Te = " << Te[i] << " C" << std::endl << "Tc = " << Tc[j] << " C" << std::endl;
            std::cout << "Qe = " << Qe / 1000.0 << " kW" << std::endl << std::endl;

            ui->resultado->setText(resText);
        }
    }
#endif

#if defined(CABIN)
    cab.setTS(dado["ts"].toDouble());
    cab.setRHS(dado["rhs"].toDouble());

    cab.simulate();

    resText.clear();

    resText.append("RHCAB " + QString::number(cab.getRHCab().back()) + " \n");
#ifdef USE_WEBSOCKETS
    resText.append("TS: " + QString::number(cab.getTS()) + " C\n");
#else
    resText.append("TS: " + QString::number(cab.getTS().back()) + " C\n\n");
#endif
    resText.append("TR: " + QString::number(cab.getTR().back()) + " C\n\n");

    QJsonObject msgTR_obj;
    msgTR_obj.insert("tipo", "dado");
    msgTR_obj.insert("TR", cab.getTR().back());
    msgTR_obj.insert("RHR", cab.getRHCab().back());

    QJsonDocument msgTR_doc;
    msgTR_doc.setObject(msgTR_obj);

    worker.sendBinaMessage(msgTR_doc.toJson());

    ui->resultado->setText(resText);

    /*std::cout << "rhcab: " << cab.getRHCab().back() << std::endl;
#ifdef USE_WEBSOCKETS
    std::cout << "ts: " << cab.getTS() << std::endl;
#else
    std::cout << "ts: " << cab.getTS().back() << std::endl;
#endif
    std::cout << "tr: " << cab.getTR().back() << std::endl;*/
    /*QChart chartTxT;
    QChart chartRC;
    QLineSeries seriesTC;
    QLineSeries seriesTS;
    QLineSeries seriesTR;
    QLineSeries seriesRC;
    QValueAxis eixoTemp;
    QValueAxis eixoTime;
    QValueAxis eixoRC;

    for(int i = 0; i < cab.getTC().size(); i++){
        seriesTC.append(QPointF(cab.getTC().at(i), cab.getTime().at(i)));
    }
    for(int i = 0; i < cab.getTS().size(); i++){
        seriesTS.append(QPointF(cab.getTS().at(i), cab.getTime().at(i)));
    }
    for(int i = 0; i < cab.getTR().size(); i++){
        seriesTR.append(QPointF(cab.getTR().at(i), cab.getTime().at(i)));
    }
    for(int i = 0; i < cab.getRHCab().size(); i++){
        seriesRC.append(QPointF(cab.getRHCab().at(i), cab.getTime().at(i)));
    }

    /*chartTxT.addSeries(seriesTC);
    chartTxT.addSeries(seriesTS);
    chartTxT.addSeries(seriesTR);
    chartTxT.setTitle("Temperatura x  Tempo");

    chartRC.addSeries(seriesRC);
    chartRC.setTitle("RH Cabine x Tempo");

    eixoRC.setTitleText("RH Cabine");
    eixoTemp.setTitleText("Temperatura (ºC)");
    eixoTime.setTitleText("Tempo (min)");

    chartTxT.addAxis(eixoTemp, Qt::AlignLeft);
    chartTxT.addAxis(eixoTime, Qt::AlignBottom);
    chartRC.addAxis(eixoRC, Qt::AlignLeft);
    chartRC.addAxis(eixoTime, Qt::AlignBottom);*/


#endif

#if defined(HXC) || defined(DOUBLEEVAP)
    std::cout << std::fixed << std::setprecision(2);

    hin = CoolProp::PropsSI("H", "P", 305.0e3, "Q", 0.383, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.40e-2, 290.5e3, hin);
    MostrarResHXC(4245);

    hin = CoolProp::PropsSI("H", "P", 300.0e3, "Q", 0.3842, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.19e-2, 289.0e3, hin);
    MostrarResHXC(4000);

    hin = CoolProp::PropsSI("H", "P", 315.0e3, "Q", 0.3804, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.41e-2, 295.5e3, hin);
    MostrarResHXC(4244);

    hin = CoolProp::PropsSI("H", "P", 306.0e3, "Q", 0.383, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.00e-2, 292.5e3, hin);
    MostrarResHXC(3749);

    hin = CoolProp::PropsSI("H", "P", 305.0e3, "Q", 0.3824, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.97e-2, 290.5e3, hin);
    MostrarResHXC(4960);

    hin = CoolProp::PropsSI("H", "P", 300.0e3, "Q", 0.3965, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.85e-2, 288.5e3, hin);
    MostrarResHXC(4723);

    hin = CoolProp::PropsSI("H", "P", 310.0e3, "Q", 0.3853, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.80e-2, 292.5e3, hin);
    MostrarResHXC(4709);

    hin = CoolProp::PropsSI("H", "P", 322.0e3, "Q", 0.3834, "R134a");
    doubleEvaporator.simulate(0.15, 273.15 + 27.0, 0.5, 3.34e-2, 300.0e3, hin);
    MostrarResHXC(4115);

#endif

#if defined(POWERTRAIN)

#endif

#if defined(MQTTCONNECT)|| defined(ALL)

#endif

#ifdef ALL

    // laço iterativo
    double Tc_old, hsub, Rh3 = 0.0, Rh3_old;
    double Te_old, Rm = 0.0, Rm_old;
    double dTsup_old, Rh1 = 0.0, Rh1_old;
    double thermalLoad1, thermalLoad2;

    resText.append("INITIAL GUESS\n");
    resText.append("Tc = " + QString::number(Tc - 273.15) + "\n");
    resText.append("Te = " + QString::number(Te - 273.15) + "\n");
    resText.append("dTsup = " + QString::number(dTsup) + "\n");
    std::cout << "INITIAL GUESS" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Tc = " << Tc - 273.15 << std::endl;
    std::cout << "Te = " << Te - 273.15 << std::endl;
    std::cout << "dTsup = " << dTsup << std::endl;

    ui->resultado->setText(resText);

    int i_Total = 0;
    int i_dTsup = 0;
    int i_cabin = 0;
    //ALTERACAO
    //int quant_iterations = cab.getIterations();
    int quant_iterations = 500;

    //PLOTTER


    Plotter plotter("../OutputData/TESTE.csv");
    plotter.clearFile("../OutputData/TESTE.csv");
/*
    Plotter plotterBatt("../OutputData/TESTEbatt.csv");
    plotterBatt.clearFile("../OutputData/TESTEbatt.csv");
*/
    plotter.writeHeaders({"Iteracao;Tempo (s);Inlet Temperature;Outlet Temperature;RH Inlet;RH Outlet;T Evap;T Cond;Capacidade Evaporator1;Capacidade Evaporator2;W Compressor;Sensible Refri Cap;Latent Refri Cap;Mixture Temperature"});

//    plotterBatt.writeHeaders({"Iteracao;Tempo (s);T bat;THeat;MHeat;Inlet Temperature;RH Inlet"});

    cab.simulate(Tae, wae, mae);

    //powertrain.batterysimulate(Qbat{powertrain.simulate}, DADOS{.dat}, dT) -->> COMEÇAR ASSIM

    //cab.simulate(Tae, wae, mae, dT, Qloss{battery.simulate}, );


    // loop 1 - Cabin ------------------------------------------------------------------
    do{
        i_cabin++;
        // loop 2 - dTsup ------------------------------------------------------------------
        do {
            i_dTsup++;
            double dTsup_aux;
            switch (i_dTsup) {
            case 1:
                //dTsup -= 1.0;
                break;
            case 2:
                dTsup_old = dTsup;
                dTsup += 1.0;
                Rh1_old = Rh1;
                break;
            default:
                dTsup_aux = dTsup - Rh1 * (dTsup - dTsup_old) / (Rh1 - Rh1_old);
                dTsup_old = dTsup;
                dTsup = dTsup_aux;
                Rh1_old = Rh1;
            }

            // loop 3 - Te --------------------------------------------------------------------*/
            //Te = Te_guess;
            int i_Te = 0;
            do {
                i_Te++;
                double Te_aux;
                switch (i_Te) {
                case 1:
                    //Te -= 1.0;
                    break;
                case 2:
                    Te_old = Te;
                    Te += 1.0;
                    Rm_old = Rm;
                    break;
                default:
                    Te_aux = Te - Rm * (Te - Te_old) / (Rm - Rm_old);
                    Te_old = Te;
                    Te = Te_aux;
                    Rm_old = Rm;
                }

                Pe = CoolProp::PropsSI("P", "Q", 1, "T", Te, fluid);
                h1 = CoolProp::PropsSI("H", "P", Pe, "T", Te + dTsup, fluid);

                // loop 4 - Tc -----------------------------------------------------------------*/
                //Tc = Tc_guess;
                int i_Tc = 0;
                do
                {
                    i_Tc++;
                    i_Total++;
                    double Tc_aux;
                    switch (i_Tc) {
                    case 1:
                        //Tc -= 1.0;
                        break;
                    case 2:
                        Tc_old = Tc;
                        Tc += 1.0;
                        Rh3_old = Rh3;
                        break;
                    default:
                        Tc_aux = Tc - Rh3 * (Tc - Tc_old) / (Rh3 - Rh3_old);
                        Tc_old = Tc;
                        Tc = Tc_aux;
                        Rh3_old = Rh3;
                    }

                    Pc = CoolProp::PropsSI("P", "Q", 1, "T", Tc, fluid);

                    compressor.simulate(Pe, Pc, h1, N);
                    mc = compressor.getMassFlowRate();
                    h2 = compressor.getOutletEnthalpy();
                    condenser.simulate(mac, Tac, mc, Pc, h2);
                    h3 = condenser.getRefrigerantOutletEnthalpy();
                    hsub = CoolProp::PropsSI("H", "P", Pc, "T", Tc - dTsub, fluid);
                    Rh3 = h3 - hsub;

                    resText.append("\nIteration" + QString::number(i_Total) + "\n");
                    resText.append("Tc = " + QString::number(Tc - 273.15) + "\t residual = " + QString::number(std::abs(Rh3 / h3)) + "\n");


                    if (std::isnan(std::abs(Rh3 / h3))) {
                        std::cerr << "Residual (Rh3 / h3) value is NaN at iteration: " << i_Total << std::endl;
                        return;
                    }

                    std::cout << std::endl << "Iteration " << i_Total << std::endl;
                    std::cout << std::fixed << std::setprecision(2) << "Tc = " << Tc - 273.15 << std::scientific << std::setprecision(5) << "\t residual = " << std::abs(Rh3 / h3) << std::endl;

                    ui->resultado->setText(resText);

                } while (i_Tc == 1 || abs(Rh3 / h3) > tolerance);
                //-----------------------------------------------------------------------------------------

                expansionDeviceCabin.simulate(Pc, Pe, h3, xc);
                me1 = expansionDeviceCabin.getMassFlowRate();
                expansionDeviceBattery.simulate(Pc, Pe, h3, xb);
                me2 = expansionDeviceBattery.getMassFlowRate();
                Rm = (me1 + me2) - mc;
                resText.append("Te = " + QString::number(Te - 273.15) + "\t residual = " + QString::number(std::abs(Rm / (me1 + me2))) + "\n");

                //MUDANCA 1
                if (std::isnan(std::abs(Rm / (me1 + me2)))) {
                    std::cerr << "Residual (Rm / (me1 + me2)) value is NaN!" << std::endl;
                    return;
                }

                std::cout << std::fixed << std::setprecision(2) << "Te = " << Te - 273.15 << std::scientific << std::setprecision(5) << "\t residual = " << std::abs(Rm / (me1 + me2)) << std::endl;

                ui->resultado->setText(resText);

            } while (i_Te == 1 || abs(Rm / (me1 + me2)) > tolerance);
            //---------------------------------------------------------------------------------------------

            doubleEvaporator.simulate(mae, cab.getTR().back() + 273.15, cab.getRHCab().back(), me1, Pe, h3);

            std::cout << "Air Inlet Temperature: " << cab.getTR().back() << std::endl;


            batteryEvaporator.simulate(powertrain.getTb().back(), me2, Pe, h3);

            thermalLoad1 = doubleEvaporator.getHeatTransfer();
            //thermalLoad2 = batteryEvaporator.getTotalHeatTransfer().back();

            powertrain.simulateCycle(powertrain.getTb().back(), batteryEvaporator.getTotalHeatTransfer().back());

            //PROBLEMA
            //Tb = powertrain.getTb().back();
            std::cout << "Tb: " << Tb << std::endl;

            //Tb --> VAI VIR DO powertrain.batterysimulate();
            //batteryEvaporator.simulate(Tb, me2, Pe, h3);
            //thermalLoad2 = batteryEvaporator
            thermalLoad2 = 0.0;
            //batteryEvaporator.simulate(me2, Pe, h3, 25.0 + 273.15);
            //thermalLoad2 = batteryEvaporator.getHeatTransfer();

            Rh1 = ((thermalLoad1 + thermalLoad2) / (me1 + me2) + h3) - h1;
            resText.append("dTsup = " + QString::number(dTsup) + "\t residual = " + QString::number(std::abs(Rh1 / h1)) + "\n");

            //MUDANCA 2
            if (std::isnan((std::abs(Rh1 / h1)))) {
                std::cerr << "Residual (Rh1 / h1) value is NaN!" << std::endl;
                return;
            }

            std::cout << std::fixed << std::setprecision(2) << "dTsup = " << dTsup << std::scientific << std::setprecision(5) << "\t residual = " << std::abs(Rh1 / h1) << std::endl;

            ui->resultado->setText(resText);
        } while (i_dTsup == 1 || abs(Rh1 / h1) > tolerance);

        //battery.simulate(); --> ADICIONAR
        cab.simulate(doubleEvaporator.getAirOutletTemperatureEvaporator1(), doubleEvaporator.getAirOutletRelativeHumidityEvaporator1(), mae);

        plotter.addDataRow({static_cast<double>(i_Total),
                            i_cabin * cab.getDT(),                                          //TEMPO
                            cab.getTR().back(),                                             //T INLET EVAPORATOR
                            doubleEvaporator.getAirOutletTemperatureEvaporator1(),          //T OUTLET EVAPORATOR 1
                            cab.getRHCab().back(),                                          //RH INLET EVAPORATOR
                            doubleEvaporator.getAirOutletRelativeHumidityEvaporator1(),     //RH OUTLET EVAPORATOR / ENTRADA DE CABINE
                            Te,                                                             //T EVAP
                            Tc,                                                             //T COND
                            doubleEvaporator.getHeatTransferEvaporator1(),                  //TRANSFER RATE EVAPORATOR 1
                            doubleEvaporator.getHeatTransferEvaporator2(),                  //TRANSFER RATE EVAPORATOR 2
                            compressor.getPowerConsumption(),                               //POWER CONSUMPTION
                            cab.getSensibleRefrigerationCapacity(),                         //SENSIBLE REFRI CAPACITY
                            cab.getLatentRefrigerationCapacity(),                           //LATENT REFRI CAPACITY
                            cab.getTM()});
/*
        plotterBatt.addDataRow({static_cast<double>(i_Total),
                                i_cabin * cab.getDT(),                                          //TEMPO
                                powertrain.getTb().back(),                                      //BATTERY TEMPERATURE
                                batteryEvaporator.getTotalHeatTransfer().back(),                //TOTAL HEAT
                                powertrain.getModuleHeatRelease().back(),                       //MODULE HEAT
                                cab.getTR().back(),                                             //T INLET EVAPORATOR
                                cab.getRHCab().back()});                                        //RH INLET EVAPORATOR
*/

/*
        QObject::connect(mqttWorker, &MyMqtt::connected, this, [this]() {
            qDebug() << "MQTT conectado!";
            mqttWorker->publishTemperature(cab.getTR().back());  // Agora pode chamar com segurança
        });
*/


    } while(i_cabin < quant_iterations);
    //---------------------------------------------------------------------------------------------*/


    resText.append("\nSOLUTION CONVERGED\n\n");
    std::cout << std::endl << "SOLUTION CONVERGED" << std::endl << std::endl;

    resText.append("Te [C] = " + QString::number(Te - 273.15) + "\n");
    resText.append("Tc [C] = " + QString::number(Tc - 273.15) + "\n");
    resText.append("   dTsup [C] = " + QString::number(dTsup) + "\n");
    resText.append("   dTsub [C] = " + QString::number(dTsub) + "\n");
    std::cout << std::fixed << std::setprecision(2) << "Te [C] = " << Te - 273.15 << std::endl;
    std::cout << "Tc [C] = " << Tc - 273.15 << std::endl;
    std::cout << "   dTsup [C] = " << dTsup << std::endl;
    std::cout << "   dTsub [C] = " << dTsub << std::endl << std::endl;

    resText.append("Condenser air outlet temperature [C] = " + QString::number(condenser.getAirOutletTemperature() - 273.15) + "\n");
    resText.append("Evaporator air outlet temperature [C] = " + QString::number(doubleEvaporator.getAirOutletTemperatureEvaporator1() - 273.15) + "\n\n");
    std::cout << "Condenser air outlet temperature [C] = " << condenser.getAirOutletTemperature() - 273.15 << std::endl;
    std::cout << "Evaporator air outlet temperature [C] = " << doubleEvaporator.getAirOutletTemperatureEvaporator1() - 273.15 << std::endl << std::endl;

    resText.append("Compressor mass flow rate [kg/h] = " + QString::number(compressor.getMassFlowRate() * 3600) + "\n");
    resText.append("   Cabin evaporator mass flow rate [kg/h] = " + QString::number(expansionDeviceCabin.getMassFlowRate() * 3600) + " (" + QString::number(expansionDeviceCabin.getMassFlowRate() / compressor.getMassFlowRate() * 100) + "%)\n");
    resText.append("   Battery evaporator mass flow rate [kg/h] = " + QString::number(expansionDeviceBattery.getMassFlowRate() * 3600) + " (" + QString::number(expansionDeviceBattery.getMassFlowRate() / compressor.getMassFlowRate() * 100) + "%)\n\n");
    std::cout << "Compressor mass flow rate [kg/h] = " << compressor.getMassFlowRate() * 3600 << std::endl;
    std::cout << "   Cabin evaporator mass flow rate [kg/h] = " << expansionDeviceCabin.getMassFlowRate() * 3600 << " (" << expansionDeviceCabin.getMassFlowRate() / compressor.getMassFlowRate() * 100 << "%)" << std::endl;
    std::cout << "   Battery evaporator mass flow rate [kg/h] = " << expansionDeviceBattery.getMassFlowRate() * 3600 << " (" << expansionDeviceBattery.getMassFlowRate() / compressor.getMassFlowRate() * 100 << "%)" << std::endl << std::endl;

    resText.append("Total evaporator heat transfer [W] = " + QString::number(thermalLoad1 + thermalLoad2) + "\n");
    resText.append("   Cabin evaporator heat transfer [W] = " + QString::number(thermalLoad1) + " (" + QString::number(thermalLoad1 / (thermalLoad1 + thermalLoad2) * 100) + "%)\n");
    resText.append("   Battery evaporator heat transfer [W] = " + QString::number(thermalLoad2) + " (" + QString::number(thermalLoad2 / (thermalLoad1 + thermalLoad2) * 100) + "%)\n");
    resText.append("Condenser heat transfer [W] = " + QString::number(condenser.getHeatTransfer()) + "\n");
    resText.append("Compressor power consumption [W] = " + QString::number(compressor.getPowerConsumption()) + "\n");
    resText.append("Energy imbalance [W] = " + QString::number(compressor.getPowerConsumption() + thermalLoad1 + thermalLoad2 - condenser.getHeatTransfer()) + "\n\n");
    std::cout << "Total evaporator heat transfer [W] = " << thermalLoad1 + thermalLoad2 << std::endl;
    std::cout << "   Cabin evaporator heat transfer [W] = " << thermalLoad1 << " (" << thermalLoad1 / (thermalLoad1 + thermalLoad2) * 100 << "%)" << std::endl;
    std::cout << "   Battery evaporator heat transfer [W] = " << thermalLoad2 << " (" << thermalLoad2 / (thermalLoad1 + thermalLoad2) * 100 << "%)" << std::endl;
    std::cout << "Condenser heat transfer [W] = " << condenser.getHeatTransfer() << std::endl;
    std::cout << "Compressor power consumption [W] = " << compressor.getPowerConsumption() << std::endl;
    std::cout << "Energy imbalance [W] = " << compressor.getPowerConsumption() + thermalLoad1 + thermalLoad2 - condenser.getHeatTransfer() << std::endl << std::endl;

    resText.append("COP = " + QString::number((thermalLoad1 + thermalLoad2) / compressor.getPowerConsumption()) + "\n");
    std::cout << "COP = " << (thermalLoad1 + thermalLoad2) / compressor.getPowerConsumption() << std::endl << std::endl;

    ui->resultado->setText(resText);

#endif
}
#if defined(HXC) || defined(DOUBLEEVAP)
void MainWindow::MostrarResHXC(int num){
    //resText.append("Condition VII\n");
    resText.append("T_ro = " + QString::number(doubleEvaporator.getRefrigerantOutletTemperature() - 273.15) + " C\n");
    resText.append("T_ao = " + QString::number(doubleEvaporator.getAirOutletTemperatureEvaporator1() - 273.15) + " C\n");
    resText.append("T_ao = " + QString::number(doubleEvaporator.getAirOutletTemperatureEvaporator2() - 273.15) + " C + " + QString::number(doubleEvaporator.getAirOutletTemperatureEvaporator1() - 273.15) + " C\n");
    resText.append("w_ao = " + QString::number(doubleEvaporator.getAirOutletRelativeHumidityEvaporator1()) + "\n");
    resText.append("w_ao = " + QString::number(doubleEvaporator.getAirOutletRelativeHumidityEvaporator2()) + " + " + QString::number(doubleEvaporator.getAirOutletRelativeHumidityEvaporator1()) + "\n");
    resText.append("Q_e = " + QString::number(doubleEvaporator.getHeatTransfer()) + " W\n");
    resText.append("Q_e = " + QString::number(doubleEvaporator.getHeatTransferEvaporator1()) + " W + " + QString::number(doubleEvaporator.getHeatTransferEvaporator2()) + " W\n");
    resText.append("Error = " +  QString::number((doubleEvaporator.getHeatTransfer() - num) / num * 100) + " %\n\n");
    std::cout << "Condition VII" << std::endl;
    std::cout << "T_ro = " << doubleEvaporator.getRefrigerantOutletTemperature() - 273.15 << " C" << std::endl;
    std::cout << "T_ao = " << doubleEvaporator.getAirOutletTemperatureEvaporator1() - 273.15 << " C" << std::endl;
    std::cout << "T_ao = " << doubleEvaporator.getAirOutletTemperatureEvaporator2() - 273.15 << " C + " << doubleEvaporator.getAirOutletTemperatureEvaporator1() - 273.15 << " C" << std::endl;
    std::cout << "w_ao = " << doubleEvaporator.getAirOutletRelativeHumidityEvaporator1() << std::endl;
    std::cout << "w_ao = " << doubleEvaporator.getAirOutletRelativeHumidityEvaporator2() << " + " << doubleEvaporator.getAirOutletRelativeHumidityEvaporator1() << std::endl;
    std::cout << "Q_e = " << doubleEvaporator.getHeatTransfer() << " W" << std::endl;
    std::cout << "Q_e = " << doubleEvaporator.getHeatTransferEvaporator1() << " W + " << doubleEvaporator.getHeatTransferEvaporator2() << " W" << std::endl;
    std::cout << "Error = " << (doubleEvaporator.getHeatTransfer() - num) / num * 100 << " %" << std::endl;
    //std::cout << "Dp = " << doubleEvaporator.getRefrigerantPressureLoss() << " Pa" << std::endl;
    //std::cout << "Dp = " << doubleEvaporator.getRefrigerantPressureLossEvaporator1() << " Pa + " << doubleEvaporator.getRefrigerantPressureLossEvaporator2() << " Pa" << std::endl;
    //std::cout << "Error = " << (doubleEvaporator.getRefrigerantPressureLoss() - 35000.0) / 35000.0 * 100.0 << " %" << std::endl << std::endl;

    ui->resultado->setText(resText);
}
#endif

#ifdef COMPRESSOR
void MainWindow::MostrarResComp(double Pe, double Pc, double N){
    resText.append("N = " + QString::number(N) + " rpm\n" + "Pe = " + QString::number(Pe / 1e5) + " bar\n" + "Pc = " + QString::number(Pc / 1e5) + " bar\n");
    resText.append("m = " + QString::number(compressor.getMassFlowRate() * 3600) + " kg/h\n");
    resText.append("W = " + QString::number(compressor.getPowerConsumption() / 1000) + " kW\n\n");
    std::cout << "N = " << N << " rpm" << std::endl << "Pe = " << Pe / 1e5 << " bar" << std::endl << "Pc = " << Pc / 1e5 << " bar" << std::endl;
    std::cout << "m = " << compressor.getMassFlowRate() * 3600 << " kg/h" << std::endl;
    std::cout << "W = " << compressor.getPowerConsumption() / 1000 << " kW" << std::endl << std::endl;

    ui->resultado->setText(resText);
}
#endif

#ifdef CONDENSER
void MainWindow::MostrarResCond(int rpm){
    resText.append("Condition ");
    resText.append(QString::number(rpm));
    resText.append(" rpm\n");
    resText.append("T_ao = " + QString::number(condenser.getAirOutletTemperature() - 273.15) + " C\n");
    resText.append("Q_c = " + QString::number(condenser.getHeatTransfer()) + " W\n\n");
    std::cout << "Condition " << rpm << " rpm" << std::endl;
    std::cout << "T_ao = " << condenser.getAirOutletTemperature() - 273.15 << " C" << std::endl;
    std::cout << "Q_c = " << condenser.getHeatTransfer() << " W" << std::endl << std::endl;

    ui->resultado->setText(resText);
}
#endif


#if defined(USE_WEBSOCKETS)
void MainWindow::ws_handler(const QString &message){
    QString msg_aux = message;
    msg_aux.replace("\\\"", "\"");
    msg_aux.replace("\\\\", "\\");
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg_aux.toUtf8(), &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "Erro ao processar JSON:" << parseError.errorString();
    }
    //qDebug() << msg_aux << jsonDoc["ts"].toDouble();
    on_simulate_clicked(jsonDoc);
}
#endif



