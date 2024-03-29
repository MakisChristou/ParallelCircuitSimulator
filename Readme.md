## Compilation

The simulator can be easily compiled by running `make` in the main project directory (asuming that the necesarry dependecies are met). The source code was compiled on Ubuntu 19.10 without any extra dependencies needed. Alternatively the program can be compiled by running `g++ simulator.cpp`.

## CLI Arguments
The following list contain the command line arguments that the simulator supports at the moment.
- `./simulator -C <path/to/bench/file>`
- `./simulator -T <unit_of_time>`
- `./simulator -I <path/to/input/file>`
- `./simulator -S`
- `./simulator -G`
- `./simulator -B`

Their use case is explained in the following section

## Example Usage
These are some examples using the command line arguments that the simulator supports.

`./simulator -C ISCAS/iscas89/s27.bench` runs the simulator on s27.bench

`./simulator -C ISCAS/iscas89/s27.bench -T s` runs the simulator on s27.bench and returns in std out the execution time in seconds

`./simulator -C ISCAS/iscas89/s27.bench -T ms` runs the simulator on s27.bench and returns in std out the execution time in miliseconds

`./simulator -C ISCAS/iscas89/s208.1.bench -I TESTS/iscas89/test\ suite\ 1/s208.vec` runs the simulator on *s27.bench* with input file *s208.vec*

`./simulator -C ISCAS/iscas89/s27.bench -G` runs the simulator on s27.bench and saves the netlist as a Graphviz file (only for small netlists)

`./simulator -C ISCAS/iscas89/s27.bench -S` runs the simulator on s27.bench and returns the netlist stats in standard out

`./simulator -C ISCAS/iscas89/s27.bench -B` runs the simulator on s27.bench with a progress bar for more verbose output (useful in larger circuits)


## Scripts
The script *gen_table.sh* is used to run the simulator on all the inputs from *ISCAS89* and *ISCAS85* benchmark suits and save the execution time in ms as well as each netlist stats in a text file. Then a python script called *Results.py* is used to parse the file and generate a markdown table, the one shown in the PDF.

## Netlist Statistics

| Circuit | Time (ms) | Lines | # of Nand | # of And | #of Nor | # of Not | # of Buff | # of Inputs | # of Outputs |# Paths | Graph Size (KB) 
| ------------- |-------------| ------------- |-------------| ------------- |-------------|------------- |-------------|------------- |-------------- |------------|-------------|
| c1355 | 22.574 | 619  | 416  | 56  | 0  | 40  | 32  | 41  | 32  | 4173216 | 81  | 
| c5315 | 126.514 | 2714  | 454  | 718  | 27  | 581  | 419  | 178  | 123  | 1341305 | 357  | 
| c6288 | 112.751 | 2480  | 0  | 256  | 2128  | 32  | 0  | 32  | 32  | 1101055638 | 328  | 
| c7552 | 223.137 | 3886  | 1028  | 776  | 54  | 876  | 593  | 207  | 108  | 726494 | 510  | 
| c17 | 0.094 | 13  | 6  | 0  | 0  | 0  | 0  | 5  | 2  | 11 | 1  | 
| c2670 | 40.036 | 1674  | 254  | 332  | 12  | 321  | 305  | 233  | 140  | 679954 | 218  | 
| c880 | 4.852 | 469  | 87  | 117  | 61  | 63  | 26  | 60  | 26  | 8642 | 61  | 
| c3540 | 51.495 | 1761  | 298  | 495  | 68  | 490  | 246  | 50  | 22  | 28265874 | 231  | 
| c1908 | 16.206 | 963  | 377  | 63  | 1  | 277  | 187  | 33  | 25  | 729056 | 126  | 
| s27 | 0.129 | 21  | 1  | 1  | 4  | 2  | 0  | 7  | 4  | 28 | 2  | 
| s420.1 | 1.972 | 269  | 29  | 49  | 34  | 78  | 0  | 34  | 17  | 474 | 35  | 
| s208.1 | 0.768 | 131  | 15  | 21  | 16  | 38  | 0  | 18  | 9  | 142 | 17  | 
| s344 | 1.282 | 201  | 18  | 44  | 30  | 59  | 0  | 24  | 17  | 344 | 26  | 
| s1196 | 7.873 | 593  | 119  | 118  | 50  | 141  | 0  | 32  | 32  | 3098 | 78  | 
| s349 | 1.313 | 202  | 19  | 44  | 31  | 57  | 0  | 24  | 17  | 354 | 26  | 
| s641 | 3.88 | 475  | 4  | 90  | 0  | 272  | 0  | 54  | 42  | 1722 | 61  | 
| s938 | 6.411 | 545  | 57  | 105  | 70  | 158  | 0  | 66  | 33  | 1714 | 71  | 
| s38584 | 6409.59 | 22447  | 2126  | 5516  | 1185  | 7805  | 0  | 1464  | 1730  | 1080723 | 2940  | 
| s713 | 4.403 | 489  | 28  | 94  | 0  | 254  | 0  | 54  | 42  | 21812 | 63  | 
| s1494 | 13.418 | 686  | 0  | 354  | 0  | 89  | 0  | 14  | 25  | 976 | 91  | 
| s1238 | 8.498 | 572  | 125  | 134  | 57  | 80  | 0  | 32  | 32  | 3559 | 75  | 
| s344.1 | 1.494 | 201  | 18  | 44  | 30  | 59  | 0  | 24  | 17  | 344 | 26  | 
| s1423 | 13.309 | 827  | 64  | 197  | 92  | 167  | 0  | 91  | 79  | 44726 | 108  | 
| s1512 | 16.462 | 926  | 92  | 98  | 47  | 367  | 0  | 86  | 60  | 3468 | 120  | 
| s991 | 7.582 | 623  | 101  | 47  | 33  | 220  | 0  | 84  | 20  | 7444 | 81  | 
| s820 | 4.636 | 336  | 54  | 76  | 66  | 33  | 0  | 23  | 24  | 492 | 45  | 
| s953 | 5.943 | 492  | 114  | 49  | 112  | 84  | 0  | 45  | 52  | 1156 | 64  | 
| s386 | 1.624 | 185  | 0  | 83  | 0  | 41  | 0  | 13  | 13  | 207 | 24  | 
| s510 | 2.276 | 249  | 61  | 34  | 55  | 32  | 0  | 25  | 13  | 369 | 32  | 
| s13207 | 1066.04 | 9441  | 849  | 1114  | 98  | 5378  | 0  | 700  | 790  | 1345369 | 1226  | 
| s1269 | 8.713 | 671  | 74  | 235  | 87  | 132  | 0  | 55  | 47  | 39570 | 88  | 
| s400 | 1.606 | 213  | 36  | 11  | 34  | 56  | 0  | 24  | 27  | 448 | 27  | 
| s298 | 1.095 | 156  | 9  | 31  | 19  | 44  | 0  | 17  | 20  | 231 | 20  | 
| s635 | 3.102 | 353  | 34  | 31  | 30  | 128  | 0  | 34  | 33  | 1245 | 46  | 
| s382 | 1.529 | 209  | 30  | 11  | 34  | 59  | 0  | 24  | 27  | 400 | 27  | 
| s9234 | 489.134 | 6094  | 528  | 955  | 113  | 3570  | 0  | 247  | 250  | 244854 | 793  | 
| s35932 | 5614.21 | 19876  | 7020  | 4032  | 0  | 3861  | 0  | 1763  | 2048  | 197141 | 2602  | 
| s967 | 5.816 | 491  | 102  | 49  | 107  | 99  | 0  | 45  | 52  | 1071 | 64  | 
| s499 | 1.656 | 197  | 60  | 0  | 20  | 32  | 0  | 23  | 22  | 1452 | 26  | 
| s444 | 1.963 | 232  | 58  | 13  | 34  | 62  | 0  | 24  | 27  | 535 | 30  | 
| s838.1 | 6.725 | 545  | 57  | 105  | 70  | 158  | 0  | 66  | 33  | 1714 | 71  | 
| s1196.1 | 9.032 | 593  | 119  | 118  | 50  | 141  | 0  | 32  | 32  | 3098 | 78  | 
| s832 | 4.45 | 334  | 54  | 78  | 66  | 25  | 0  | 23  | 24  | 506 | 44  | 
| s1488 | 13.412 | 692  | 0  | 350  | 0  | 103  | 0  | 14  | 25  | 962 | 92  | 
| s5378 | 148.818 | 3236  | 0  | 0  | 765  | 1775  | 15  | 214  | 228  | 13542 | 421  | 
| s526 | 2.147 | 244  | 22  | 56  | 35  | 52  | 0  | 24  | 27  | 410 | 32  | 
| s38417 | 8413.21 | 25585  | 2050  | 4154  | 2279  | 13470  | 0  | 1664  | 1742  | 1391579 | 3330  | 
| s15850 | 1526.33 | 11067  | 968  | 1619  | 151  | 6324  | 0  | 611  | 684  | 164738046 | 1439  | 


<!---
## Part A Diagram
![flowchart.png](:/fa1554a314d04b29b0887fc7817a7406)
-->




