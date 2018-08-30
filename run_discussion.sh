#!/usr/bin/env bash
file="discussion"

cd src
mpicc ${file}.c -o ${file}
mpirun -np 4 -hostfile ~/hostfile ${file}
