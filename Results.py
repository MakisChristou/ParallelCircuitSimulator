"""
=======================================
A simple plot with a custom dashed line
=======================================

A Line object's ``set_dashes`` method allows you to specify dashes with
a series of on/off lengths (in points).
"""

class Graph1:
    Cname: str
    FC: float
    

import numpy as np
import matplotlib.pyplot as plt
import pylab


circuits = []
y = []
lines = []
nand = []
andd = []
nor = []
orr = []
nott = []
buff = []
inputt = []
output = []
kbb = []
paths = []
coverage = []
dropping = []
parallel = []
test = []

filename = "Rand_Results" # change to Netlist_Stats and see Table1.tex 


with open(filename) as f:
        content = f.readlines()



for i in content:
	
	#  ignore empty lines
	if i.strip():
		
		#print(i)

		pos1 = i.rfind('/')
		pos1 = pos1+1

		pos2 = i.find(".bench")
		
		circuit_name = i[pos1:pos2]
		
		circuits.append(circuit_name)

		pos3 = i.rfind('=')
		pos3 = pos3 + 2
		pos4 = i.find('[')
		
		execution_time = i[pos3:pos4]
		
		
		y.append(float(execution_time))

		pos5 = i.find("LINES")
		pos6 = i.find("NAND")
		pos7 = i.rfind("AND")
		pos8 = i.find("OR")
		pos9 = i.find("NOR")
		pos10 = i.find("NOT")
		pos11 = i.find("BUFF")
		pos12 = i.find("INPUT")
		pos13 = i.find("OUTPUT")
		pos14 = i.find("KB")
		pos15 = i.find("PATHS")
		pos16 = i.find("COVERAGE")
		pos17 = i.find("Dropping")
		pos18 = i.find("Thr")
		pos19 = i.find("TEST:")

		##################################
		pos5 = pos5 + 6
		
		temp_line = i[pos5:pos6]
		
		lines.append(int(temp_line))
	   
		###################################
		pos6 = pos6 + 5
	   
		temp_nand = i[pos6:pos7]
		
		nand.append(int(temp_nand))
		
		##################################
		
		pos7 = pos7 + 4

		temp_and = i[pos7:pos8] 
		 
		andd.append(int(temp_and))

		##################################
		pos8 = pos8 + 3

		temp_or = i[pos8:pos9]

		orr.append(int(temp_or))

		##################################

		pos9 = pos9 + 4

		temp_nor = i[pos9:pos10]

		nor.append(int(temp_nor))
		
		##################################

		pos10 = pos10 + 4

		temp_not = i[pos10:pos11]

		nott.append(int(temp_not))

		#################################
		
		pos11 = pos11 + 5

		temp_buff = i[pos11:pos12]
		
		buff.append(int(temp_buff))

		#################################

		pos12 = pos12 + 6

		temp_input = i[pos12:pos13]

		inputt.append(int(temp_input))

		#################################


		pos13 = pos13 + 7

		temp_output = i[pos13:pos14]

		output.append(int(temp_output))

		
		################################

		pos14 = pos14 + 3
		
		temp_kb = i[pos14:pos15]

		kbb.append(int(temp_kb))

		################################

		pos15 = pos15 + 6

		temp_path = i[pos15:pos16]

		paths.append(int(temp_path))
		
		###############################

		pos16 = pos16 + 9

		temp_coverage = i[pos16:pos17]

		coverage.append(float(temp_coverage[:-2]))

		###############################

		pos17 = pos17 + 9

		temp_mode = i[pos17:pos18]

		dropping.append(temp_mode)

		###############################

		pos18 = pos18 + 4

		temp_parallel = i[pos18:pos19]

		parallel.append(temp_parallel)

		###############################

		pos19 = pos19 + 5

		temp_test = i[pos19:-1]

		test.append(temp_test)

		###############################




#import sys
#sys.exit(1) # Or something that calls sys.exit().


# Netlist Stats (Needs Manual Modification)
file= open("Netlist.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c c c c c c c c c||}\n")
file.write("\hline\n")
file.write("Circuit & Nand & And & Nor & Or & Not & Buff & PI & PO & Paths & KB \\\ [0.5ex] \n")
file.write("\hline\hline\n")


for name,time,liness,nand_g,and_g,nor_g,or_g,not_g,buff,inputs,outputs,paths,kilobytes,FC,FD,THR in zip(circuits,y,lines,nand,andd,nor,orr,nott,buff,inputt,output,paths,kbb,coverage,dropping,parallel):
		file.write(name + " & " + str(nand_g) + " & " + str(and_g)  + " & " + str(nor_g)  + " & " + str(or_g) + " & " + str(not_g)  + " & " + str(buff)  + " & " + str(inputs)  + " & " + str(outputs)  + " & " + str(paths)  + " & " + str(kilobytes) + " \\\ \n")
		file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")


# Fault Coverage
file = open("Fault_Coverage.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c||}\n")
file.write("\hline\n")
file.write("Circuit & Fault Coverage (\%) & Test Vector \\\ [0.5ex] \n")
file.write("\hline\hline\n")


for name,FC,test_name in zip(circuits,coverage,test):
		file.write(name + " & " + str(FC) + " \% " +" & " + str(test_name) + " \\\ \n")
		file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")


# Performance
file = open("Performance1.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c c||}\n")
file.write("\hline\n")
file.write("Circuit & Serial (s) & Parallel & Speedup \\\ [0.5ex] \n")
file.write("\hline\hline\n")



names = []
FD_Increase = []

circuit_set = set(circuits)
print(len(circuit_set))

for i in circuit_set:
	parallel_time = ""
	serial_time = ""
	test_vector = ""
	for name,threads,FD,test_name,time in zip(circuits,parallel,dropping,test,y):
		#print("(" + FD + ")")
		if name == i and FD == "NO " and ".vec" in test_name:
			#print("("+threads+")")
			if threads == "4 ":			
				parallel_time = time;
				test_vector = test_name;

			if threads == "1 ":
				serial_time = time;
				test_vector = test_name;
	
	if serial_time:
		names.append(i)
		FD_Increase.append(int(100*serial_time/parallel_time))
		file.write(i + " & " + str(serial_time) + " & " + str(parallel_time) + " & " + str(int(100*serial_time/parallel_time)) + " \% \\\ \n")
		file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")


###############################################################


# Performance
file = open("Performance2.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c c||}\n")
file.write("\hline\n")
file.write("Circuit & Not FD (s) & FD (s) & Speedup \\\ [0.5ex] \n")
file.write("\hline\hline\n")

circuit_set = set(circuits)
print(len(circuit_set))

for i in circuit_set:
	FD_time = ""
	NFD_time = ""
	test_vector = ""
	for name,threads,FD,test_name,time in zip(circuits,parallel,dropping,test,y):
		#print("(" + FD + ")")
		if name == i and threads == "1 " and ".vec" in test_name:
			#print("("+threads+") " + FD)
			if FD == "YES ":			
				FD_time = time;
				test_vector = test_name;

			if FD == "NO ":
				NFD_time = time;
				test_vector = test_name;
	
	if NFD_time:
		file.write(i + " & " + str(NFD_time) + " & " + str(FD_time) + " & " + str(int(100*NFD_time/FD_time))+" \% \\\ \n")
		file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")


###############################################################


