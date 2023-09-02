# StockSim
## Overview

Stock Sim is a paper trading simulator.  It allows you to log in to portfolios ( no passwords yet) and buy, sell, or view your account, which will be updated on the SQLite database and loaded at runtime to the user.
The goal of this is to create a simple market simulator that will eventually load in historical data from yahoo finance so you can see how your portfolio would perform over time
Currently the only supported OS is ubuntu, and the only supported stock tickers are NFLX, AAPL, GME, which all will have static values.

## Build

To build go to parent directory
```
cd StockSim
bash ci/build.sh
```
## Run
```
cd StockSim
bash ci/run.sh
```
Then you can enter your name and you're ready to go

## Dependencies
cmake
ninja-build
libsqlite3-dev
