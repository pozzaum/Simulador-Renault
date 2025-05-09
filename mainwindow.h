/**
 * This is where the main processing happens
 * The main UI is created and set here
 * It uses preprocessing variables determined at generation time to compile only the necessary lines of code and includes
 * It is recommended to look at the CMakeLists.txt file to understand how it determines which variable is set
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QThread>
#include <fstream>
#include <QTimer>
#include <QMetaObject>

#include <filesystem>
#include "plotter.h"



#if defined(COMPRESSOR) || defined(ALL)

    #include "Compressor/compressor.h"
    #include "./externals/CoolProps/include/CoolProp.h"
#endif
#if defined(CONDENSER) || defined(ALL)
    #include "HeatExchanger/Condenser/condenser.h"
#endif

#if defined(EXPDEVICE) || defined(ALL)
    #include "ExpansionDevice/expansiondevice.h"
#endif

#if defined(CABIN) || defined(ALL)
    #include "Cabin/cabin.h"
/*#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>*/
#endif

#if defined(HXC) || defined(DOUBLEEVAP) || defined(ALL)
    #include "HeatExchanger/DoubleEvaporator/doubleevaporator.h"
#endif

#if defined(BATEVAP) || defined(ALL)
    #include "HeatExchanger/BatteryEvaporator/batteryevaporator.h"
#endif

#if defined(POWERTRAIN) || defined(ALL)
#include "PowerTrain/powertrain.h"
#endif


#if defined(MQTTCONNECT) || defined(ALL)
#include "MqttConnect/mqttconnect.h"
#endif


#ifdef USE_WEBSOCKETS
    #include "websocketworker.h"
#endif


#include <iomanip>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

#if defined(MQTTCONNECT) || defined(ALL)
    //MyMqtt* mymqtt = nullptr;
#endif

public slots:
#ifdef USE_WEBSOCKETS
    void ws_handler(const QString &message);
    void ws_handler(const QByteArray &message);
#endif

private:
    Ui::MainWindow *ui;

#ifdef USE_WEBSOCKETS
    WebSocketWorker worker;
    QWebSocket socket;
    //QThread mainThread;
#endif

#ifdef USE_MQTT
    QThread mqttThread;
    MyMqtt* mqttWorker;
    QThread mainThread;
#endif


#if defined(COMPRESSOR) || defined(ALL)
    Compressor compressor;
    void MostrarResComp(double Pe, double Pc, double N);
#endif

#if defined(CONDENSER) || defined(ALL)
    Condenser condenser;
    void MostrarResCond(int rpm);
#endif
#ifdef BATEVAP
    BatteryEvaporator batteryEvaporator;
#endif
#ifdef EXPDEVICE
    ExpansionDevice expansionDevice;
    std::vector<double> Te{ 10.0, 5.0, 0.0, -5.0, -10.0, -20.0, -30.0};
    std::vector<double> Tc{ 30.0, 35.0, 38.0, 40.0, 45.0, 50.0};
    double Qe;
#endif
#if defined(CABIN) || defined(ALL)
    Cabin cab;
#endif
#if defined(HXC) || defined(DOUBLEEVAP)
    DoubleEvaporator doubleEvaporator;
    double hin;
    void MostrarResHXC(int num);
#endif
#if defined(POWERTRAIN) || defined(ALL)
    PowerTrain powertrain;
#endif

#if defined(ALL)
    ExpansionDevice expansionDeviceCabin;
    ExpansionDevice expansionDeviceBattery;
    DoubleEvaporator doubleEvaporator; //Evaporator for the car cabin (previously evaporatorCabin)
    BatteryEvaporator batteryEvaporator; //Evaporator for the car battery (previously evaporatorBattery)
    double Te, Tc;
#endif
    std::string fluid;
    double dTsub, dTsup, tolerance;
    double mc, me1 = 1.0, me2 = 1.0, Pe, Pc, h1 = 1.0, h2, h3 = 1.0, h4;
    double N, mac, Tac, xb, xc, mae, Tae, wae, Tb;
    QString resText = "";
    QStringList list_numofPipes;

    /**
     * @brief getDataFromFiles
     * Loads data.
     *
     * Loads data for the refrigeration system and/or component from the respective .dat file.
     */
    void getDataFromFiles();

    /**
     * @brief getDataFromUI
     * Loads Data.
     *
     * Loads data for the refrigeration system and/or component from the input fields in the UI.
     */
    void getDataFromUI();

private slots:

    /**
     * @brief on_loadData_clicked
     * Calls a function to load data.
     *
     * Calls either the "getDataFromFiles()" or the "getDataFromUI()" function.
     */
    void on_loadData_clicked();

    /**
     * @brief on_simulate_clicked
     *
     * Start simulation.
     *
     * Starts the simulation of the whole system or a specific AC component.
     */
    void on_simulate_clicked(QJsonDocument dado = QJsonDocument::fromJson(""));

    void on_apply_data_changes_clicked();


    void on_btnConnectMqtt_clicked();
};
#endif // MAINWINDOW_H
