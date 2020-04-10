## Compilation

Run `make` while in the main project directory. The source code was compiled on Ubuntu 19.10 without any extra dependecies needed.

## CLI Arguments
- `./simulator -C <path/to/bench/file>`
- `./simulator -T <unit_of_time>`
- `./simulator -I <path/to/input/file>`
- `./simulator -S `

## Example Usage

`./simulator -C ISCAS/iscas89/s27.bench` runs the simulator on s27.bench

`./simulator -C ISCAS/iscas89/s27.bench -T s` runs the simulator on s27.bench and returns in std out the execution time in seconds

`./simulator -C ISCAS/iscas89/s27.bench -T ns` runs the simulator on s27.bench and returns in std out the execution time in nanoseconds

`./simulator -C ISCAS/iscas89/s27.bench -T us` runs the simulator on s27.bench and returns in std out the execution time in microseconds

`./simulator -C ISCAS/iscas89/s27.bench -T ms` runs the simulator on s27.bench and returns in std out the execution time in miliseconds

`./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec` runs the simulator on *s27.bench* with input file *s208.vec*

## Scripts
The script *gen_table.sh* is used to run the simulator on all the inputs from *ISCAS89* and *ISCAS85* benchmark suits and save the execution time in ms as well as each netlist stats in a text file. Then a python script called *Results.py* is used to parse the file and generate a markdown table, the one shown in the PDF.

## Netlist Statistics

| Circuit Name | Time (ms) | Lines | # of Nand | # of And | #of Nor | # of Not | # of Buff | # of Inputs | # of Outputs | Graph Size (KB) 
| ------------- |-------------| ------------- |-------------| ------------- |-------------|------------- |-------------|------------- |-------------|-------------|
| c1355 | 19.352 | 1387  | 416  | 56  | 0  | 40  | 32  | 41  | 32  | 169 | 
| c5315 | 138.635 | 5544  | 454  | 718  | 27  | 581  | 419  | 178  | 123  | 678 | 
| c6288 | 123.033 | 6320  | 0  | 256  | 2128  | 32  | 0  | 32  | 32  | 774 | 
| c7552 | 235.815 | 7716  | 1028  | 776  | 54  | 876  | 593  | 207  | 108  | 943 | 
| c17 | 0.115 | 19  | 6  | 0  | 0  | 0  | 0  | 5  | 2  | 2 | 
| c2670 | 44.325 | 2916  | 254  | 332  | 12  | 321  | 305  | 233  | 140  | 355 | 
| c880 | 5.898 | 906  | 87  | 117  | 61  | 63  | 26  | 60  | 26  | 110 | 
| c3540 | 58.873 | 3579  | 298  | 495  | 68  | 490  | 246  | 50  | 22  | 438 | 
| c1908 | 20.872 | 1956  | 377  | 63  | 1  | 277  | 187  | 33  | 25  | 239 | 
| s27 | 0.167 | 30  | 1  | 1  | 4  | 2  | 0  | 7  | 4  | 3 | 
| s420.1 | 2.764 | 475  | 29  | 49  | 34  | 78  | 0  | 34  | 17  | 58 | 
| s208.1 | 1.149 | 227  | 15  | 21  | 16  | 38  | 0  | 18  | 9  | 27 | 
| s344 | 1.871 | 343  | 18  | 44  | 30  | 59  | 0  | 24  | 17  | 41 | 
| s1196 | 10.836 | 1228  | 119  | 118  | 50  | 141  | 0  | 32  | 32  | 150 | 
| s349 | 1.913 | 348  | 19  | 44  | 31  | 57  | 0  | 24  | 17  | 42 | 
| s641 | 5.013 | 679  | 4  | 90  | 0  | 272  | 0  | 54  | 42  | 82 | 
| s938 | 8.124 | 971  | 57  | 105  | 70  | 158  | 0  | 66  | 33  | 118 | 
| s38584 | 6503.81 | 40162  | 2126  | 5516  | 1185  | 7805  | 0  | 1464  | 1730  | 4910 | 
| s713 | 4.988 | 755  | 28  | 94  | 0  | 254  | 0  | 54  | 42  | 91 | 
| s1494 | 13.341 | 1519  | 0  | 354  | 0  | 89  | 0  | 14  | 25  | 186 | 
| s1238 | 9.99 | 1270  | 125  | 134  | 57  | 80  | 0  | 32  | 32  | 155 | 
| s344.1 | 1.703 | 343  | 18  | 44  | 30  | 59  | 0  | 24  | 17  | 41 | 
| s1423 | 13.423 | 1502  | 64  | 197  | 92  | 167  | 0  | 91  | 79  | 183 | 
| s1512 | 15.698 | 1518  | 92  | 98  | 47  | 367  | 0  | 86  | 60  | 185 | 
| s991 | 8.255 | 962  | 101  | 47  | 33  | 220  | 0  | 84  | 20  | 117 | 
| s820 | 5.869 | 844  | 54  | 76  | 66  | 33  | 0  | 23  | 24  | 103 | 
| s953 | 7.612 | 1005  | 114  | 49  | 112  | 84  | 0  | 45  | 52  | 122 | 
| s386 | 2.174 | 399  | 0  | 83  | 0  | 41  | 0  | 13  | 13  | 49 | 
| s510 | 3.676 | 523  | 61  | 34  | 55  | 32  | 0  | 25  | 13  | 64 | 
| s13207 | 972.441 | 13969  | 849  | 1114  | 98  | 5378  | 0  | 700  | 790  | 1701 | 
| s1269 | 10.415 | 1308  | 74  | 235  | 87  | 132  | 0  | 55  | 47  | 160 | 
| s400 | 1.876 | 427  | 36  | 11  | 34  | 56  | 0  | 24  | 27  | 52 | 
| s298 | 1.429 | 318  | 9  | 31  | 19  | 44  | 0  | 17  | 20  | 38 | 
| s635 | 3.5 | 668  | 34  | 31  | 30  | 128  | 0  | 34  | 33  | 81 | 
| s382 | 1.818 | 409  | 30  | 11  | 34  | 59  | 0  | 24  | 27  | 50 | 
| s9234 | 442.324 | 9484  | 528  | 955  | 113  | 3570  | 0  | 247  | 250  | 1156 | 
| s35932 | 5000.09 | 37660  | 7020  | 4032  | 0  | 3861  | 0  | 1763  | 2048  | 4601 | 
| s967 | 6.24 | 1016  | 102  | 49  | 107  | 99  | 0  | 45  | 52  | 124 | 
| s499 | 1.992 | 475  | 60  | 0  | 20  | 32  | 0  | 23  | 22  | 58 | 
| s444 | 2.166 | 471  | 58  | 13  | 34  | 62  | 0  | 24  | 27  | 57 | 
| s838.1 | 6.938 | 971  | 57  | 105  | 70  | 158  | 0  | 66  | 33  | 118 | 
| s1196.1 | 9.649 | 1228  | 119  | 118  | 50  | 141  | 0  | 32  | 32  | 150 | 
| s832 | 5.268 | 856  | 54  | 78  | 66  | 25  | 0  | 23  | 24  | 105 | 
| s1488 | 13.808 | 1513  | 0  | 350  | 0  | 103  | 0  | 14  | 25  | 186 | 
| s5378 | 139.323 | 5538  | 0  | 0  | 765  | 1775  | 15  | 214  | 228  | 675 | 
| s526 | 2.694 | 553  | 22  | 56  | 35  | 52  | 0  | 24  | 27  | 67 | 
| s38417 | 7496.23 | 40081  | 2050  | 4154  | 2279  | 13470  | 0  | 1664  | 1742  | 4885 | 
| s15850 | 1332.32 | 16531  | 968  | 1619  | 151  | 6324  | 0  | 611  | 684  | 2014 | 


<!---
## Part A Diagram
![flowchart.png](:/fa1554a314d04b29b0887fc7817a7406)
-->




