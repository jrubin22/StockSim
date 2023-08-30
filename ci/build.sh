#!/usr/bin/bash

#build.sh for StockSim

BUILD_TYPE=Debug
ENV=historical
CMAKE_DEFS="-DCMAKE_BUILD_TYPE=$BUILD_TYPE -DENV=$ENV"
pushd .
mkdir -p ./build
cd build
cmake -G Ninja $CMAKE_DEFS ..
cmake --build .
popd