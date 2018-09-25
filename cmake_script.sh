#!/bin/bash
#
# A simple helper script to run the proper cmake for G4Emma

# Clean up any files remaining from older builds
rm -rf EMMAapp Makefile CMakeCache.txt CmakeFiles/ cmake_install.cmake

# ********************************
# REQUIRES ATTENTION
# ********************************
# You must modify this to the path in which the Geant4Config.cmake file can be found
GEANT4_DIR=~/GEANT4/geant4.9.6-install/lib/Geant4-9.6.4/
# I didn't take time to find a way to make this detection automatic yet

cmake -DGeant4_DIR=/opt/geant4/geant4.9.6.p04-build . 

#Assumes you have a quad core processor
make -j4
