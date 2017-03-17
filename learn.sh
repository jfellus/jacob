#!/bin/bash

sensors=`tino_arms_sensors -p 20 2>/dev/null | head -n 1 | tr $'\t' ' '`
echo $sensors >> RBF.txt
