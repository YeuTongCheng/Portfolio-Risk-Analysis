# Portfolio-Risk-Analysis

Assignment from "UCB MFE C++ Preprogram"

Market Class:
Run a number of simulations by using Cholesky decomposition 
The simulation then create correlated annual returns for equities and bonds and store the returns.

Portfolio Class:
Store the parameters in class properties and also store a percentCash property
analyzePortfolio() uses the simulation results to calculate expected returns for the portfolio with the
given percent equity and percent bonds. For each simulated pair of equity and bond returns, calculate portfolio returns.

Market object 
Create a loop for equity percent that goes from 0 to 1 in increments of 0.01.
For each equity percent, bond percent pair, analyzePortfolio() stores the percentEquity, percentBond, portfolioReturn,
portfolioVol values in a csv file.

In Market, create a method called calculateTangent
This method should call analyzePortfolio() using equity_up = percentEquity + 0.01 and
equity_down = percentEquity – 0.01 to calculate expected returns and vols for these equity
percentages 

In Market create a method called findPortfolioForVol that finds the unlevered portfolio 
with volatility matching the requested volatility and either lies on the efficient frontier or
is a mixture of cash and the tangency portfolio.


