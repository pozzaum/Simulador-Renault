#ifndef CAB_H
#define CAB_H

#include <fstream>
#include <vector>
#include <cmath>
#include "../externals/CoolProps/include/CoolProp.h"
#include "../externals/CoolProps/include/HumidAirProp.h"
#include "../externals/fparser/fparser.hh"
#include "../filereader.h"

class Cabin {
private:
    std::string refrigerant;
    double p, cpr, Mr, con, trtemp, tctemp, tm, wsup, wm, dw, hfg, rhamb, pwsamb, pwamb, wamb, cpe, dt, sc, lc;
    std::vector<double> tr, tc, rhc, rh, rhcab, wc, qamb, qins, qpl, qconv, qinsl, qtot;; //rhc: convertido
#if defined(CABIN) && !defined(USE_WEBSOCKETS)
    std::vector<double> ts, rhs, me;
#endif

#if defined(ALL) || defined(USE_WEBSOCKETS)
    double ts, rhs, me, miv;
#endif
    int iterations, uo, occ, ao, pac, tambcpamb, qsol, qps, qpsu, hc, mc, cc, ac, tamb, cpamb; //dt: time step

//================me================
    std::vector<double> meX, meY;

//================TS================
    std::vector<double> tsX, tsY;

//================RHSUP================
    std::vector<double> rhsX, rhsY;

    FunctionParser wamb_FP, con_FP;
    double linap(std::vector<double> X, std::vector<double> Y, int index);

public:
    Cabin(){};

    void getDataFromFiles();
    void getDataFromUI();

    std::vector<double> getTR(){return this->tr;}

    std::vector<double> getTC(){return this->tc;}
    double getDT(){return this->dt;}
    double getTM(){return this->tm;}
    std::vector<double> getRHCab(){return this->rhcab;}
    int getIterations(){return this->iterations;}
#if defined(CABIN) && !defined(USE_WEBSOCKETS)
    void setTS(double &e_TS){this->ts.push_back(e_TS);}
#elif defined(ALL) || defined(USE_WEBSOCKETS)
    void setTS(const double &e_TS){this->ts = e_TS;}
    void setRHS(const double &e_RHS){this->rhs = e_RHS; this->rhc.push_back(e_RHS);}
#endif



#if defined(CABIN) && !defined(USE_WEBSOCKETS)
    std::vector<double> getTS(){return this->ts;}
    void simulate();
#endif

#if defined(ALL) || defined(USE_WEBSOCKETS)
    double getTS(){return this->ts;}
    double getME(){return this->me;}
    double getSensibleRefrigerationCapacity(){return this -> sc;}
    double getLatentRefrigerationCapacity(){return this -> lc;}
    void simulate(double Te = 0, double rhe = 0, double mi = 0);
#endif

};

#endif // CAB_H
