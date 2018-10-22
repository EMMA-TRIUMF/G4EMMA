rm -rf EMMAapp Makefile CMakeCache.txt CmakeFiles/ cmake_install.cmake

GEANT4_DIR=~/GEANT4/geant4.9.6-install/lib/Geant4-9.6.4/

cmake -g -DGeant4_DIR=/opt/geant4/geant4.9.6.p04-build . 

make -j4
