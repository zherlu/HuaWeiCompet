#!/bin/bash

CASE_PATH=../../test-case/case
BIN_PATH=../bin


echo "-----------------build-----------------"
../batch.sh


echo "-----------------exe-------------------"
$BIN_PATH/future_net $CASE_PATH/topo.csv $CASE_PATH/demand.csv $CASE_PATH/result.csv


echo "-----------------result----------------"
cat $CASE_PATH/result.csv
