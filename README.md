# Portfolio-Risk-Analysis

Market Class:
The constructor should store the parameters in class properties and then run the specified
number of simulations using a Cholesky decomposition 
The simulation should create correlated annual returns for equities and bonds and should store the returns in
two vectors.

Portfolio Class:
The constructor should store the parameters in class properties and also store a
percentCash property
In the Market class, create a public method called Portfolio analyzePortfolio, which uses the
simulation results  to calculate expected returns for the portfolio with the
given percent equity and percent bonds. For each simulated pair of equity and bond
returns, calculate portfolio returns.

Create a Market object 
In main(), create a loop for equity percent that goes from 0 to 1 in increments of 0.01.
Let bondPercent = 1 – equityPercent. For each equity percent, bond percent pair, call
analyzePortfolio and store the percentEquity, percentBond, portfolioReturn,
portfolioVol values in a csv file.

In Market, create a protected method: calculateTangent
This method should call analyzePortfolio() using equity_up = percentEquity + 0.01 and
equity_down = percentEquity – 0.01 to calculate expected returns and vols for these equity
percentages 

In Market create a public method: findPortfolioForVol
that finds the unlevered portfolio with volatility matching the requested volatility and either lies
on the efficient frontier or is a mixture of cash and the
tangency portfolio.

If vol > tangency portfolio vol, then consider searching on percentEquity using the bisection
root-finding method. Use the tangency portfolio’s percent equity as the lower bound and
1.0 as the upper bound on percent equity. Then, search for percent equity such that
portfolio vol (from analyzeVol()) matches the desired vol
