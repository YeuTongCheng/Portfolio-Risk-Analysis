#include <iostream>
#include <random>
#include <math.h>
#include <cmath>
#include "Assignment7.h"
using namespace std;

Portfolio::Portfolio(double percentEquity,double percentBond,double ret, double vol):PercentEquity(percentEquity), PercentBond(percentBond), Ret(ret), Vol(vol)
{
    percentCash=1.0-percentEquity-percentBond;
}
double Portfolio::getpercentEquity()
{
    return PercentEquity;
}
double Portfolio::getpercentBond()
{
    return PercentBond;
}
double Portfolio::getret()
{
    return Ret;
}
double Portfolio::getvol()
{
    return Vol;
}

// Market Class: 
// Run a number of simulations by using Cholesky decomposition. 
// The simulation then create correlated annual returns for equities and bonds and store the returns.

Market::Market(double corrEquityBond,double equityReturn,double equityVol,double bondReturn,double bondVol,double riskFreeRate,int numSimulations): CorrEquityBond(corrEquityBond), EquityReturn(equityReturn), EquityVol(equityVol), BondReturn(bondReturn), BondVol(bondVol), RiskFreeRate(riskFreeRate), NumSimulations(numSimulations)
{
    mt19937 mt_rand(12345);
    normal_distribution<double> dis_normal(0.0,1.0);
    
    for(int i=0;i<NumSimulations;i++)
    {
        double X1=dis_normal(mt_rand);
        double X2=dis_normal(mt_rand);
        double Z1=X1;
        double Z2=CorrEquityBond*X1+sqrt(1-CorrEquityBond*CorrEquityBond)*X2;
        r_equity.push_back((EquityReturn-(EquityVol*EquityVol)/2)+EquityVol*Z1);
        r_bond.push_back((BondReturn-(BondVol*BondVol)/2)+BondVol*Z2);
    }
    
}

// Portfolio Class: 
// Store the parameters in class properties and also store a percentCash property analyzePortfolio() uses the simulation results to calculate expected returns for the portfolio with the given percent equity and percent bonds. 
// For each simulated pair of equity and bond returns, calculate portfolio returns.

Portfolio Market::analyzePortfolio(double percentEquity,double percentBond)
{
    vector<double> ret;
    vector<double> ret_sqr;
    for(int i=0;i<NumSimulations;i++)
    {
        ret.push_back(-1.0+percentEquity*exp(r_equity.at(i))+percentBond*exp(r_bond.at(i))+(1-percentEquity-percentBond)*exp(RiskFreeRate));
    }
    double mean_return=accumulate(ret.begin(),ret.end(),0.0)/NumSimulations;
    for(int i=0;i<NumSimulations;i++)
    {
        ret_sqr.push_back(pow(ret.at(i),2));
    }
    double S1=accumulate(ret.begin(),ret.end(),0.0);
    double S2=accumulate(ret_sqr.begin(),ret_sqr.end(),0.0);
    double sim_volatility=sqrt(NumSimulations*S2-S1*S1)/NumSimulations;
    Portfolio portfolio1(percentEquity, percentBond,mean_return,sim_volatility);
    return portfolio1;
}

double Market::calculateTangent(double percentEquity)
{
    double equity_up=percentEquity+0.01;
    double equity_down=percentEquity-0.01;
    double bond_up=1-equity_up;
    double bond_down=1-equity_down;
    auto port_up=analyzePortfolio(equity_up,bond_up);
    auto port_down=analyzePortfolio(equity_down,bond_down);
    double return_up=port_up.getret();
    double return_down=port_down.getret();
    double vol_up=port_up.getvol();
    double vol_down=port_down.getvol();
    double tangent;
    return tangent=(return_up-return_down)/(vol_up-vol_down);
}
bool cmp(pair<double,double>a,pair<double,double>b)
{
    return a.first<b.first;
}
Portfolio Market::findTangencyPortfolio()
{
    vector<pair<double,double>> tangent;
    for(double percentEquity=0.01;percentEquity<=0.99;percentEquity+=0.0025)
    {
        tangent.push_back({calculateTangent(percentEquity),percentEquity});
    }
    sort(tangent.begin(),tangent.end(),cmp);
    auto opt_set=tangent.back();
    double Max_tang;
    double Equity_tang;
    tie(Max_tang,Equity_tang)=opt_set;
    double equity_opt=Equity_tang;
    double bond_opt=1-equity_opt;
    Portfolio tangent_port=analyzePortfolio(equity_opt,bond_opt);
    return tangent_port;
}

const double epsilon=1e-10;
bool Zero(double x)
{
    return fabs(x)<epsilon;
}
double Market::f(double percentEquity,double vol)
{
    double percentBond=1.0-percentEquity;
    auto port=analyzePortfolio(percentEquity,percentBond);
    return port.getvol()-vol;
}

Portfolio Market::findPortfolioForVol(double vol)
{
    double percentEquity=0;
    double percentBond=0;
    if(vol<tan_Volatility)
    {
        double vol_tp=tan_Volatility;
        double percentCash=((vol/vol_tp)-1)*-1;
        percentEquity+=(1-percentCash)*tan_PercentEquity;
        percentBond+=(1-percentCash)*tan_PercentBond;
    }
    if(vol>tan_Volatility)
    {
        double f0=f(tan_PercentEquity,vol);
        double a=tan_PercentEquity;
        double b=1.0;
        if(f0>0)
        {
            b=tan_PercentEquity;
            a=1.0;
        }
        double f1=1;
        double p=0;
        while(!Zero(f1))
        {
            p=0.5*(a+b);
            f1=f(p,vol);
            if(f1<0)
            {
                a=p;
            }
            else
            {
                b=p;
            }
        }
        percentEquity+=p;
        percentBond+=(1-percentEquity);
    }
    auto port=analyzePortfolio(percentEquity,percentBond);
    return port;
}

