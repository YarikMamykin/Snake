#!/bin/bash

git submodule init
git submodule update

mkdir -p build
rm -frv build/*
pushd ${PWD}
cd build
cmake ..
make 
popd

