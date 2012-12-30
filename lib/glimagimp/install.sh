#!/bin/bash

echo "=========== FIXING ENV VARIABLE =================="
DIR_LIB=`pwd`
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DIR_LIB/lib/
export LD_LIBRARY_PATH
echo $LD_LIBRARY_PATH

echo "============== COMPILING SAMPLE =================="
cd sample/
make
cd ../
