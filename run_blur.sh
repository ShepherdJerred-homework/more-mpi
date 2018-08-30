#!/usr/bin/env bash
file="blur"

mpicc src/${file}.c -o out/${file}
#mpirun -np 4 -hostfile ~/hostfile out/${file} < blur_test_1_input.txt > blur_test_1_output.txt
#diff blur_test_1_output.txt blur_test_1_expected_output.txt

#mpirun -np 64 -hostfile ~/hostfile out/${file} < blur_test_2_input.txt > blur_test_2_output.txt
#diff blur_test_2_output.txt blur_test_2_expected_output.txt

#mpirun -np 64 -hostfile ~/hostfile out/${file} < blur_test_3_input.txt > blur_test_3_output.txt
#diff blur_test_3_output.txt blur_test_3_expected_output.txt

mpirun -np 4 -hostfile ~/hostfile out/${file}
