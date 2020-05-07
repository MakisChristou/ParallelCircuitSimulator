"""
=======================================
A simple plot with a custom dashed line
=======================================

A Line object's ``set_dashes`` method allows you to specify dashes with
a series of on/off lengths (in points).
"""
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

filename = "Results" # change to Netlist_Stats and see Table1.tex 


with open(filename) as f:
        content = f.readlines()



for i in content:
	
	#  ignore empty lines
	if i.strip():

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

		coverage.append(temp_coverage)

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






# Write Markdown Matrix

file= open("Table.md","w") 

file.write("| Circuit | Time | Lines | NAND | AND | NOR | NOT | BUFF | PI | PO |Paths | (KB) | FC | FD | Threads | \n")
file.write("| ------------- |-------------| ------------- |-------------| ------------- |-------------|------------- |-------------|------------- |-------------- |------------|-------------|-------------- |------------|-------------|\n")


for f, b,lin,na,a,nr,nt,bf,inp,out,pth,kk,cov,mode,par in zip(circuits, y,lines,nand,andd,nor,nott,buff,inputt,output,paths,kbb,coverage,dropping,parallel):
        #print(f, b)
        file.write("| " + f + " | " + str(b) + " | "+str(lin)+" | "+str(na)+" | "+str(a)+" | "+str(nr)+" | "+str(nt)+" | "+str(bf)+" | " + str(inp) +" | " + str(out) +" | "+str(pth) + " | " + str(kk) + " | "+ cov + " | " + mode + " | " + par + " | \n")


# Write Latex Matrix

file= open("Table.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c c c c c c c c c c c c||}\n")
file.write("\hline\n")
file.write("Circuit & Time (s) & NAND & AND & NOR & NOT & BUFF & PI & PO & Paths & KB & FC(\%) & FD & Thr \\\ [0.5ex] \n")
file.write("\hline\hline\n")


for f, b,lin,na,a,nr,nt,bf,inp,out,pth,kk,cov,mode,par in zip(circuits, y,lines,nand,andd,nor,nott,buff,inputt,output,paths,kbb,coverage,dropping,parallel):
        #print(f, b)
        file.write(" " + f + " & " + str(b) + " & "+ ""+str(na)+" & "+str(a)+" & "+str(nr)+" & "+str(nt)+" & "+str(bf)+" & " + str(inp) +" & " + str(out) +" & "+str(pth) + " & " + str(kk) + " & "+ cov[:-2] + "\%" + " & " + mode + " & " + par + " \\\ \n")
        file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")



#########################################################

# Write Latex Matrix

file= open("Table1.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c c c c c c c c||}\n")
file.write("\hline\n")
file.write("Circuit & NAND & AND & NOR & NOT & BUFF & PI & PO & Paths & KB  \\\ [0.5ex] \n")
file.write("\hline\hline\n")


for f, b,lin,na,a,nr,nt,bf,inp,out,pth,kk,cov,mode,par in zip(circuits, y,lines,nand,andd,nor,nott,buff,inputt,output,paths,kbb,coverage,dropping,parallel):
        #print(f, b)
        file.write(" " + f + "" + " & "+ ""+str(na)+" & "+str(a)+" & "+str(nr)+" & "+str(nt)+" & "+str(bf)+" & " + str(inp) +" & " + str(out) +" & "+str(pth) + " & " + str(kk) + "" +"" " \\\ \n")
        file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")



#########################################################
# Write Latex Matrix

file= open("Table2.tex","w") 
file.write("begin{center}\n")
file.write("begin{tabular}{||c c c c c||}\n")
file.write("\hline\n")
file.write("Circuit & Time (s) & FC(\%) & FD & Thr & Test \\\ [0.5ex] \n")
file.write("\hline\hline\n")


for f, b,lin,na,a,nr,nt,bf,inp,out,pth,kk,cov,mode,par,tst in zip(circuits, y,lines,nand,andd,nor,nott,buff,inputt,output,paths,kbb,coverage,dropping,parallel,test):
        #print(f, b)
        file.write(" " + f + " & " + str(b) +  " & "+ cov[:-2] + "\%" + " & " + mode + " & " + par +" & " + tst +" \\\ \n")
        file.write("\hline\n")


file.write("\end{tabular}\n")
file.write("\end{center}\n")



#########################################################


import sys
sys.exit(1) # Or something that calls sys.exit().


import numpy as np
import matplotlib.pyplot as plt


coverage_int = []


for i in coverage:
	coverage_int.append(float(i[:-2]))


x = range(len(circuits))
pylab.xticks(x, circuits)
plt.xlabel('Circuit Name')
plt.ylabel('Fault Coverage (%)')
plt.title('ECE 307 Project')
plt.plot(circuits,coverage_int)

plt.legend(['FC'])
#plt.grid(axis='y')
plt.grid(axis='x')
plt.show()






x = range(len(circuits))
pylab.xticks(x, circuits)
plt.xlabel('ISCAS89')
plt.ylabel('# of Gates')
plt.title('ECE 307 Project')
plt.plot(circuits,nand)
plt.plot(circuits,andd)
plt.plot(circuits,orr)
plt.plot(circuits,nor)
plt.plot(circuits,nott)
plt.plot(circuits,buff)
plt.plot(circuits,inputt)
plt.plot(circuits,output)

plt.legend(['NAND','AND','OR','NOT','BUFF','PI','PO'])
#plt.grid(axis='y')
plt.grid(axis='x')
plt.show()

