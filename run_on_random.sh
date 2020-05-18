#!/bin/bash

# SIMULATIONS WITH .VEC INPUT FILES ONLY
#threads=$1  

FD=$1
MODE=$2

Results="Rand_Results"

# ISCAS 89
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/Random/s27_rand.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s386.bench -I TESTS/Random/s386.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s510.bench -I TESTS/Random/s510.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s641.bench -I TESTS/Random/s641.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s838.1.bench -I TESTS/Random/s838.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s298.bench -I TESTS/Random/s298.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s382.bench -I TESTS/Random/s382.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s400.bench -I TESTS/Random/s400.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/Random/s526n.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/Random/s526.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s713.bench -I TESTS/Random/s713.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s344.bench -I TESTS/Random/s344.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s344.1.bench -I TESTS/Random/s344.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s420.1.bench -I TESTS/Random/s420.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s820.bench -I TESTS/Random/s820.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s953.bench -I TESTS/Random/s953.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/Random/s208.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s349.bench -I TESTS/Random/s349.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s444.bench -I TESTS/Random/s444.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s1238.bench -I TESTS/Random/s1238.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s1494.bench -I TESTS/Random/s1494.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s5378.bench -I TESTS/Random/s5378.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s832.bench -I TESTS/Random/s832.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s1423.bench -I TESTS/Random/s1423.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s1196.1.bench -I TESTS/Random/s1196.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s1488.bench -I TESTS/Random/s1488.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s9234.bench -I TESTS/Random/s9234.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s13207.bench -I TESTS/Random/s13207.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s15850.bench -I TESTS/Random/s15850.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s38417.bench -I TESTS/Random/s38417.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s38584.bench -I TESTS/Random/s38584.vec -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas89/s35932.bench -I TESTS/Random/s35932.vec -T s -S $FD $MODE >> $Results

# ISCAS 85
./simulator -C ISCAS/iscas85/c17.bench -I TESTS/Random/c17.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c880.bench -I TESTS/Random/c880.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c1355.bench -I TESTS/Random/c1355.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c1908.bench -I TESTS/Random/c1908.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c2670.bench -I TESTS/Random/c2670.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c3540.bench -I TESTS/Random/c3540.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c6288.bench -I TESTS/Random/c6288.txt -T s -S $FD $MODE >> $Results
./simulator -C ISCAS/iscas85/c7552.bench -I TESTS/Random/c7552.txt -T s -S $FD $MODE >> $Results

