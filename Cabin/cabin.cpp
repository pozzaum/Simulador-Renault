#include "cabin.h"

void Cabin::getDataFromFiles(){
    FileReader fileReader;
    fileReader.loadFile("../refrigerationSystem.dat");
    double mae = fileReader.readRealVariable("mae");
    refrigerant = fileReader.readStringVariable("fluid");
    fileReader.unloadFile();

    fileReader.loadFile("./cabin.dat");
    p = fileReader.readIntegerVariable("p");
    tr = fileReader.readRealMatrix("tr").at(0);
    tc = fileReader.readRealMatrix("tc").at(0);
    iterations = fileReader.readIntegerVariable("iterations");
    uo = fileReader.readIntegerVariable("uo");
    occ = fileReader.readIntegerVariable("occ");
    ao = fileReader.readIntegerVariable("ao");
    pac = fileReader.readIntegerVariable("pac");
    tamb = fileReader.readIntegerVariable("tamb");
    cpr = fileReader.readIntegerVariable("cpr");
    cpamb = fileReader.readIntegerVariable("cpamb");
#ifdef CABIN
    me = fileReader.readRealMatrix("me").at(0);
    ts = fileReader.readRealMatrix("ts").at(0);
    rhs = fileReader.readRealMatrix("rhs").at(0);
#endif
    //ALTERACAO
    qsol = fileReader.readIntegerVariable("qsol");
    //qsol = 1500;

    qps = fileReader.readIntegerVariable("qps");
    qpsu = fileReader.readIntegerVariable("qpsu");

    //ALTERACAO
    miv = fileReader.readRealVariable("miv");
    //miv = 0.05 * mae;

    Mr = fileReader.readRealVariable("Mr");
    hc = fileReader.readIntegerVariable("hc");
    mc = fileReader.readIntegerVariable("mc");
    cc = fileReader.readIntegerVariable("cc");
    ac = fileReader.readIntegerVariable("ac");

    //ALTERACAO
    //dt = fileReader.readRealVariable("dt");
    dt = 10.0;

    rhc = fileReader.readRealMatrix("rhc").at(0);
    rh = fileReader.readRealMatrix("rh").at(0);
    rhcab = fileReader.readRealMatrix("rhcab").at(0);
    hfg = fileReader.readRealVariable("hfg");
    rhamb = fileReader.readRealVariable("rhamb");
    pwsamb = CoolProp::PropsSI("P","T", 273.15 + tamb, "Q", 1, "Water");
    pwamb = rhamb*pwsamb;
    std::string wamb_expression = fileReader.readStringVariable("wamb");
    wamb_FP.Parse(wamb_expression, "p, pwamb");
    con = -uo * ao / (Mr * cpr); //DISCUTIR SE É INTERESSANTE PASSAR ESTA FUNÇÃO COMO ENTRADA OU SE PODE SER POR CÓDIGO
    std::string con_expression = fileReader.readStringVariable("con");
    con_FP.Parse(con_expression, "uo, ao, Mr, cpr");
    double input_wamb[2] = {p, pwamb};
    double input_con[4] = {(double)uo, (double)ao, Mr, cpr};
    wamb = wamb_FP.Eval(input_wamb);
    con = con_FP.Eval(input_con);
    tsX = fileReader.readRealMatrix("tsX").at(0);
    tsY = fileReader.readRealMatrix("tsY").at(0);
    rhsX = fileReader.readRealMatrix("rhsX").at(0);
    rhsY = fileReader.readRealMatrix("rhsY").at(0);
    meX = fileReader.readRealMatrix("meX").at(0);
    meY = fileReader.readRealMatrix("meY").at(0);

    fileReader.unloadFile();
}

void Cabin::getDataFromUI(){

}

double Cabin::linap(std::vector<double> X, std::vector<double> Y, int index){
    double A = 0;
    double B = 0;
    double dx = 1;
    double dy = 0;
    double fx;
    int vp = 0;
    /*if(X.size() > 1){
        while ((vp < X.size() - 1) && index < X.at(vp) || index > X.at(vp - 1)) {
            vp = vp + 1;
        }
        dx = (X.at(vp) - X.at(vp - 1));
        dy = (Y.at(vp) - Y.at(vp - 1));
    }*/
    while (index < X.at(vp) || index > X.at(vp + 1)) {
        vp = vp + 1;
    }
    dx = (X.at(vp + 1) - X.at(vp));
    dy = (Y.at(vp + 1) - Y.at(vp));
    if(dx != 0) A = dy / dx;
    else A = dy;
    B = Y.at(vp) - A * X.at(vp);
    fx = A * index + B;
    return fx;
}
#ifdef CABIN
void Cabin::simulate(){
#elif defined(ALL)
void Cabin::simulate(double Te, double rhe, double mi){
#endif
    /*p = 101e3;
    iterations = 600 * 18;
    uo = 4;
    occ = 1;
    ao = 30;
    pac = 3000;
    tamb = 30;
    cpamb = 1004;
    cpr = 1010.89;
    qsol = 950;
    qps = 70;
    qpsu = 35;
    miv = 0;
    Mr = 8 * 0.942932;
    hc = 100;
    mc = 200;
    cc = 400;
    ac = 3;
    dt = 0.1;
    hfg = 2256.4e3;
    rhamb = 0.5;
    pwamb = rhamb * pwsamb;
    wamb = 0.621945 * (pwamb) / (p - pwamb);
    con = -uo * ao / (Mr * cpr);*/
    cpe = cpr;

    wc.push_back(HumidAir::HAPropsSI("W", "P", p, "T", tr.back() + 273.15, "R", rhc.back()));

#ifdef CABIN
    for (int i = 0; i < iterations; i++) {

        ts.push_back(linap(tsX, tsY, i));
        rhs.push_back(linap(rhsX, rhsY, i)/100);
        me.push_back(linap(meX, meY, i) / 1000);
#endif

#ifdef ALL
        ts = Te - 273.15;
        rhs = rhe;
        me = mi;
#endif
#ifdef CABIN
        tm = (miv * cpamb * tamb + (me.back() - miv) * cpr * tr.back()) / (me.back() * cpamb);
        trtemp = (uo * ao * (tamb - tr.back()) - me.back() * cpe * (tm - ts.back()) + qsol + qps + miv * cpamb * (tamb - tr.back()) + hc * ac * (tc.back() - tr.back())) / (Mr * cpr);
#endif
#ifdef ALL
        tm = (miv * cpamb * tamb + (me - miv) * cpr * tr.back()) / (me * cpamb);
        trtemp = (uo * ao * (tamb - tr.back()) - me * cpe * (tm - ts) + qsol + qps + miv * cpamb * (tamb - tr.back()) + hc * ac * (tc.back() - tr.back())) / (Mr * cpr);
        sc = me * cpe * (tm - ts); //Sensible refrigeration
#endif
        tctemp = (-hc * ac * (tc.back() - tr.back())) / (mc * cc);
        //MUDANCA

        //tc --> temperatura dos componentes
        //tr --> Outlet da cabine / Inlet do evaporator
        tr.push_back(tr.back() + trtemp * dt);
        tc.push_back(tc.back() + tctemp * dt);

#ifdef CABIN
        wsup = HumidAir::HAPropsSI("W", "P", p, "T", ts.back()+273.15, "R", rhs.back());

        wm = ((me.back() - miv) * wc.back() + miv * wamb) / me.back();
        dw = (-me.back() * hfg * (wm - wsup) + qpsu + miv * hfg * (wamb - wc.back())) /Mr/hfg;
#endif
#ifdef ALL
        wm = ((me - miv) * wc.back() + miv * wamb) / me;
        dw = (-me * hfg * (wm - wsup) + qpsu + miv * hfg * (wamb - wc.back())) /Mr/hfg;
        lc = me * hfg * (wm - wsup); //Latent refirgeration capacity
#endif
        wc.push_back(wc.back() + dw * dt);
        rhcab.push_back(HumidAir::HAPropsSI("R", "P", p, "T", tr.back() + 273.15, "W", wc.back()));

#ifdef CABIN
    };

    std::map<const std::string, std::vector<double>> mapa;
    mapa.insert(std::make_pair("RHCAB", rhcab));
    mapa.insert(std::make_pair("TR", tr));
    mapa.insert(std::make_pair("TS", ts));
    FileReader fileReader;
    fileReader.writetoCSV(mapa);
#endif
// ARMAZENAR OS VALORES DE SAÍDA (VETORES) EM UM ARQUIVO DE SAÍDA TIPO CSV
    /*for(int i = 0; i < iterations; i++){
        //================me================
        double meo = 0;
        if (0.6 > totaltime) meo = meb.at(0) + mea.at(0) * totaltime;
        else if (1.6 > totaltime) meo = meb.at(1) + mea.at(1) * totaltime;
        else if(3 > totaltime) meo = meb.at(2) + mea.at(2) * totaltime;
        else if(5 > totaltime) meo = meb.at(3) + mea.at(3) * totaltime;
        else if(7.5 > totaltime) meo = meb.at(4) + mea.at(4) * totaltime;
        else if(10.4 > totaltime) meo = meb.at(5) + mea.at(5) * totaltime;
        else if(11.7 > totaltime) meo = meb.at(6) + mea.at(6) * totaltime;
        else if(12 > totaltime) meo = meb.at(7) + mea.at(7) * totaltime;
        else if(12.3 > totaltime) meo = meb.at(8) + mea.at(8) * totaltime;
        else if(12.7 > totaltime) meo = meb.at(9) + mea.at(9) * totaltime;
        else if(14.36 > totaltime) meo = meb.at(10) + mea.at(10) * totaltime;
        else if(16.46 > totaltime) meo = meb.at(11) + mea.at(11) * totaltime;
        else if(18.4 > totaltime) meo = meb.at(12) + mea.at(12) * totaltime;
        else if(18.7 > totaltime) meo = meb.at(13) + mea.at(13) * totaltime;
        me.push_back(meo / 1000);

        //================TS================
        double tso = 0;
        if (0.43 > totaltime) tso = b.at(0) + a.at(0) * totaltime;
        else if (0.94 > totaltime) tso = b.at(1) + a.at(1) * totaltime;
        else if(2 > totaltime) tso = b.at(2) + a.at(2) * totaltime;
        else if(3.16 > totaltime) tso = b.at(3) + a.at(3) * totaltime;
        else if(7.61 > totaltime) tso = b.at(4) + a.at(4) * totaltime;
        else if(11.87 > totaltime) tso = b.at(5) + a.at(5) * totaltime;
        else if(14.35 > totaltime) tso = b.at(6) + a.at(6) * totaltime;
        else if(17.6 > totaltime) tso = b.at(7) + a.at(7) * totaltime;
        else if(18.6 > totaltime) tso = b.at(8) + a.at(8) * totaltime;
        ts.push_back(tso);

        //================RHINT================
        double rho = 0;
        if (0.9 > totaltime) rho = rhb.at(0) + rha.at(0) * totaltime;
        else if (2.35 > totaltime) rho = rhb.at(1) + rha.at(1) * totaltime;
        else if(3.31 > totaltime) rho = rhb.at(2) + rha.at(2) * totaltime;
        else if(5.27 > totaltime) rho = rhb.at(3) + rha.at(3) * totaltime;
        else if(9.7 > totaltime) rho = rhb.at(4) + rha.at(4) * totaltime;
        else if(15 > totaltime) rho = rhb.at(5) + rha.at(5) * totaltime;
        else if(18.71 > totaltime) rho = rhb.at(6) + rha.at(6) * totaltime;
        rh.push_back(rho);

        //================RHSUP================
        double rhso = 0;
        if (0.71 > totaltime) rhso = rhsb.at(0) + rhsa.at(0) * totaltime;
        else if (3 > totaltime) rhso = rhsb.at(1) + rhsa.at(1) * totaltime;
        else if(4.8 > totaltime) rhso = rhsb.at(2) + rhsa.at(2) * totaltime;
        else if(8.12 > totaltime) rhso = rhsb.at(3) + rhsa.at(3) * totaltime;
        else if(11.54 > totaltime) rhso = rhsb.at(4) + rhsa.at(4) * totaltime;
        else if(12 > totaltime) rhso = rhsb.at(5) + rhsa.at(5) * totaltime;
        else if(12.3 > totaltime) rhso = rhsb.at(6) + rhsa.at(6) * totaltime;
        else if(14.15 > totaltime) rhso = rhsb.at(7) + rhsa.at(7) * totaltime;
        else if(15.9 > totaltime) rhso = rhsb.at(8) + rhsa.at(8) * totaltime;
        else if(18 > totaltime) rhso = rhsb.at(9) + rhsa.at(9) * totaltime;
        rhs.push_back(rhso);

        double tro = tr.at(i);
        double tco = tc.at(i);
        //cpe = cpr[i];
        double tm = (miv * cpamb * tamb + (me.at(i) - miv) * cpr * tr.at(i)) / (me.at(i) * cpamb);
        //mr = me;


        //tclib = lib.Temperature(tc.at(i), "C");
        //tslib = lib.Temperature(ts.at(i), "C");
        pwssup = CoolProp::PropsSI("P","T", 273.15 + ts.at(i), "Q", 1, "Water");
        pwsup = rhs.at(i) * pwssup;
        ws.push_back(0.621945 * (pwsup / (p - pwsup)));
        double wm = ((me.at(i) - miv) * w.at(i) + miv * wamb) / me.at(i);
        double dw = (-me.at(i) * hfg * (wm - ws.at(i)) + qpsu + miv * hfg * (wamb - w.at(i))) / (Mr * hfg);
        w.push_back(w.at(i) + dw * dt);
        pwscab = CoolProp::PropsSI("P","T", 273.15 + tc.at(i), "Q", 1, "Water");
        pwcab = (p / ((0.62198 / w.at(i)) + 1));
        rhcab.push_back(pwcab / pwscab);
        double trtemp = (uo * ao * (tamb - tro) - me.at(i) * cpr *(tm - tso) + qsol + qps + miv * cpamb * (tamb - tro) + hc * ac * (tco - tro)) / (Mr * cpr);
        double tctemp = (-hc*ac * (tco - tro)) / (mc * cc);
        tr.push_back(tr.at(i) + trtemp * dt);
        tc.push_back(tc.at(i) + tctemp * dt);
        if (tr.at(i) <=  tamb) miv = 0;
        //cpr.push_back(1004);
        totaltime += dt/60;
        time.push_back(totaltime);
    }*/
}
