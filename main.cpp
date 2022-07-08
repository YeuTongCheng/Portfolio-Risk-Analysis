#include <iostream>
#include <fstream>
#include <vector>
#include "Assignment7.h"
using namespace std;

int main()
{
    double corrEquityBond1= -0.3;
    double equityReturn1= 0.1;
    double equityVol1= 0.2;
    double bondReturn1= 0.03;
    double bondVol1= 0.07;
    double riskFreeRate1= 0.01;
    int numSimulations1= 100000;
    
    Market market1(corrEquityBond1, equityReturn1, equityVol1, bondReturn1, bondVol1, riskFreeRate1, numSimulations1);
    
    vector<double> percent_Equity;
    vector<double> percent_Bond;
    vector<double> portfolioRetrun;
    vector<double> portfolioVol;
    
    for(double percentEquity=0.0f;percentEquity<=1.0f;percentEquity+=0.01f)
    {
        double percentBond=1-percentEquity;
        
        percent_Equity.push_back(market1.analyzePortfolio(percentEquity,percentBond).getpercentEquity());
        percent_Bond.push_back(market1.analyzePortfolio(percentEquity,percentBond).getpercentBond());
        portfolioRetrun.push_back(market1.analyzePortfolio(percentEquity,percentBond).getret());
        portfolioVol.push_back(market1.analyzePortfolio(percentEquity,percentBond).getvol());
    }
    
    ofstream File;
    File.open("EF.csv");
    File<<" percentEquity,percentBond,portfolioRetrun,portfolioVol"<<endl;
    for(int i=0;i<percent_Equity.size();i++)
    {
        File<<percent_Equity.at(i)<<","<<percent_Bond.at(i)<<","<<
        portfolioRetrun.at(i)<<","<<portfolioVol.at(i)<< endl;
    }
    File.close();
    
    double corrEquityBond2= -0.1;
    double equityReturn2= 0.09;
    double equityVol2= 0.20;
    double bondReturn2= 0.03;
    double bondVol2= 0.02;
    double riskFreeRate2= 0.02;
    int numSimulations2= 100000;
    
    Market market2(corrEquityBond2,equityReturn2,equityVol2, bondReturn2,bondVol2,riskFreeRate2,numSimulations2);
    
    auto max_vol=market2.analyzePortfolio(1,0).getvol();
    vector<double> equity_percent;
    vector<double> bond_percent;
    vector<double> cash_percent;
    vector<double> expected_return;
    vector<double> expected_vol;
   
    for(double i=0;i<=max_vol;i+=0.0025)
    {
        equity_percent.push_back(market2.findPortfolioForVol(i).getpercentEquity());
        bond_percent.push_back(market2.findPortfolioForVol(i).getpercentBond());
        cash_percent.push_back(1.0-market2.findPortfolioForVol(i).getpercentEquity()-market2.findPortfolioForVol(i).getpercentBond());
        expected_return.push_back(market2.findPortfolioForVol(i).getret());
        expected_vol.push_back(market2.findPortfolioForVol(i).getvol());
    }
    for(int j=0;j<equity_percent.size();j++)
        {
            cout<<"j="<<j<<endl<<"Equity percent: "<<equity_percent.at(j)<<endl<<"Bond percent: "<<bond_percent.at(j)<<endl<<"Cash percent: "<<
                cash_percent.at(j)<<endl<<"Expected return: "<<
            expected_return.at(j)<<endl<<"Expected vol: "<<expected_vol.at(j)<<'\n';
        }
    return 0;
}
