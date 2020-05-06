#!/bin/bash

threads=8

rm Results

# ISCAS 89 (Serial No Fault Drop)
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s386.bench -I TESTS/iscas89/test\ suite\ 1/s386.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s510.bench -I TESTS/iscas89/test\ suite\ 1/s510.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s641.bench -I TESTS/iscas89/test\ suite\ 1/s641.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s838.1.bench -I TESTS/iscas89/test\ suite\ 1/s838.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s298.bench -I TESTS/iscas89/test\ suite\ 1/s298.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s382.bench -I TESTS/iscas89/test\ suite\ 1/s382.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s400.bench -I TESTS/iscas89/test\ suite\ 1/s400.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526n.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s713.bench -I TESTS/iscas89/test\ suite\ 1/s713.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s344.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s344.1.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s420.1.bench -I TESTS/iscas89/test\ suite\ 1/s420.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s820.bench -I TESTS/iscas89/test\ suite\ 1/s820.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s953.bench -I TESTS/iscas89/test\ suite\ 1/s953.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s349.bench -I TESTS/iscas89/test\ suite\ 1/s349.vec -T s -S >> Results
./simulator -C ISCAS/iscas89/s444.bench -I TESTS/iscas89/test\ suite\ 1/s444.vec -T s -S >> Results

# ISCAS 89 (Serial Fault Drop)
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s386.bench -I TESTS/iscas89/test\ suite\ 1/s386.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s510.bench -I TESTS/iscas89/test\ suite\ 1/s510.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s641.bench -I TESTS/iscas89/test\ suite\ 1/s641.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s838.1.bench -I TESTS/iscas89/test\ suite\ 1/s838.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s298.bench -I TESTS/iscas89/test\ suite\ 1/s298.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s382.bench -I TESTS/iscas89/test\ suite\ 1/s382.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s400.bench -I TESTS/iscas89/test\ suite\ 1/s400.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526n.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s713.bench -I TESTS/iscas89/test\ suite\ 1/s713.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s344.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s344.1.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s420.1.bench -I TESTS/iscas89/test\ suite\ 1/s420.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s820.bench -I TESTS/iscas89/test\ suite\ 1/s820.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s953.bench -I TESTS/iscas89/test\ suite\ 1/s953.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s349.bench -I TESTS/iscas89/test\ suite\ 1/s349.vec -T s -S -D >> Results
./simulator -C ISCAS/iscas89/s444.bench -I TESTS/iscas89/test\ suite\ 1/s444.vec -T s -S -D >> Results

# ISCAS 89 (Serial Parallel Fault Drop)
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s386.bench -I TESTS/iscas89/test\ suite\ 1/s386.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s510.bench -I TESTS/iscas89/test\ suite\ 1/s510.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s641.bench -I TESTS/iscas89/test\ suite\ 1/s641.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s838.1.bench -I TESTS/iscas89/test\ suite\ 1/s838.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s298.bench -I TESTS/iscas89/test\ suite\ 1/s298.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s382.bench -I TESTS/iscas89/test\ suite\ 1/s382.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s400.bench -I TESTS/iscas89/test\ suite\ 1/s400.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526n.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s713.bench -I TESTS/iscas89/test\ suite\ 1/s713.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s344.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s344.1.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s420.1.bench -I TESTS/iscas89/test\ suite\ 1/s420.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s820.bench -I TESTS/iscas89/test\ suite\ 1/s820.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s953.bench -I TESTS/iscas89/test\ suite\ 1/s953.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s349.bench -I TESTS/iscas89/test\ suite\ 1/s349.vec -T s -S -P $threads >> Results
./simulator -C ISCAS/iscas89/s444.bench -I TESTS/iscas89/test\ suite\ 1/s444.vec -T s -S -P $threads >> Results

# ISCAS 89 (Parallel Fault Drop)
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s386.bench -I TESTS/iscas89/test\ suite\ 1/s386.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s510.bench -I TESTS/iscas89/test\ suite\ 1/s510.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s641.bench -I TESTS/iscas89/test\ suite\ 1/s641.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s838.1.bench -I TESTS/iscas89/test\ suite\ 1/s838.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s298.bench -I TESTS/iscas89/test\ suite\ 1/s298.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s382.bench -I TESTS/iscas89/test\ suite\ 1/s382.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s400.bench -I TESTS/iscas89/test\ suite\ 1/s400.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526n.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s526.bench -I TESTS/iscas89/test\ suite\ 1/s526.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s713.bench -I TESTS/iscas89/test\ suite\ 1/s713.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s344.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s344.1.bench -I TESTS/iscas89/test\ suite\ 1/s344.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s420.1.bench -I TESTS/iscas89/test\ suite\ 1/s420.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s820.bench -I TESTS/iscas89/test\ suite\ 1/s820.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s953.bench -I TESTS/iscas89/test\ suite\ 1/s953.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s349.bench -I TESTS/iscas89/test\ suite\ 1/s349.vec -T s -S -P $threads -D >> Results
./simulator -C ISCAS/iscas89/s444.bench -I TESTS/iscas89/test\ suite\ 1/s444.vec -T s -S -P $threads -D >> Results


