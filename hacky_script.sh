#!/bin/bash


rm Results1

./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S
./simulator -C ISCAS/iscas89/s27.bench -I TESTS/iscas89/test\ suite\ 1/s27.vec -T s -S

