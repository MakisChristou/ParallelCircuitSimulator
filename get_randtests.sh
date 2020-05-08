#!/bin/bash

threads="-B -V" # This skips fault simulation
Results="Netlist_Stats"

rm $Results

# ISCAS 89 (Count Paths and Netlist Starts only)
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s386.bench -I TESTS/iscas89/test\ suite\ 1/s386.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s510.bench -I TESTS/iscas89/test\ suite\ 1/s510.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s641.bench -I TESTS/iscas89/test\ suite\ 1/s641.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s838.1.bench -I TESTS/iscas89/test\ suite\ 1/s838.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s298.bench -I TESTS/iscas89/test\ suite\ 1/s298.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s382.bench -I TESTS/iscas89/test\ suite\ 1/s382.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s400.bench -I TESTS/iscas89/test\ suite\ 1/s400.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526n.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s713.bench -I TESTS/iscas89/test\ suite\ 1/s713.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s344.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s344.1.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s420.1.bench -I TESTS/iscas89/test\ suite\ 1/s420.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s820.bench -I TESTS/iscas89/test\ suite\ 1/s820.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s953.bench -I TESTS/iscas89/test\ suite\ 1/s953.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s349.bench -I TESTS/iscas89/test\ suite\ 1/s349.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s444.bench -I TESTS/iscas89/test\ suite\ 1/s444.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s1238.bench -I TESTS/iscas89/test\ suite\ 1/s1238.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s1494.bench -I TESTS/iscas89/test\ suite\ 1/s1494.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s5378.bench -I TESTS/iscas89/test\ suite\ 1/s5378.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s832.bench -I TESTS/iscas89/test\ suite\ 1/s832.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s1423.bench -I TESTS/iscas89/test\ suite\ 1/s1423.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s1196.1.bench -I TESTS/iscas89/test\ suite\ 1/s1196.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s1488.bench -I TESTS/iscas89/test\ suite\ 1/s1488.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s9234.bench -I TESTS/iscas89/test\ suite\ 1/s9234.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s13207.bench -I TESTS/iscas89/test\ suite\ 1/s13207.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas89/s15850.bench -I TESTS/iscas89/test\ suite\ 1/s15850.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s38417.bench -I TESTS/iscas89/test\ suite\ 1/s38417.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s38584.bench -I TESTS/iscas89/test\ suite\ 1/s38584.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas89/s35932.bench -I TESTS/iscas89/test\ suite\ 1/s35932.vec -T s -S -P $threads -D 

# ISCAS 85 (Count Paths and Netlist Starts only)
./simulator -C ISCAS/iscas85/c17.bench -I TESTS/iscas85/test\ suite\ 2/c17.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c880.bench -I TESTS/iscas85/test\ suite\ 2/c880.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c1355.bench -I TESTS/iscas85/test\ suite\ 2/c1355.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c1908.bench -I TESTS/iscas85/test\ suite\ 2/c1908.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c2670.bench -I TESTS/iscas85/test\ suite\ 2/c2670.vec -T s -S -P $threads -D
./simulator -C ISCAS/iscas85/c3540.bench -I TESTS/iscas85/test\ suite\ 2/c3540.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c5315.bench -I TESTS/iscas85/test\ suite\ 2/c5315.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c6288.bench -I TESTS/iscas85/test\ suite\ 2/c6288.vec -T s -S -P $threads -D 
./simulator -C ISCAS/iscas85/c7552.bench -I TESTS/iscas85/test\ suite\ 2/c7552.vec -T s -S -P $threads -D
