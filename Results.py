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

filename = "Results"


with open(filename) as f:
        content = f.readlines()


for i in content:
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

    ##################################
    pos5 = pos5 + 6
    
    temp_line = i[pos5:pos6]
    
    lines.append(temp_line)
   
    ###################################
    pos6 = pos6 + 5
   
    temp_nand = i[pos6:pos7]
    
    nand.append(temp_nand)
    
    ##################################
    
    pos7 = pos7 + 4

    temp_and = i[pos7:pos8] 
     
    andd.append(temp_and)

    ##################################
    pos8 = pos8 + 3

    temp_or = i[pos8:pos9]

    orr.append(temp_or)

    ##################################

    pos9 = pos9 + 4

    temp_nor = i[pos9:pos10]

    nor.append(temp_nor)
    
    ##################################

    pos10 = pos10 + 4

    temp_not = i[pos10:pos11]

    nott.append(temp_not)

    #################################
    
    pos11 = pos11 + 5

    temp_buff = i[pos11:pos12]
    
    buff.append(temp_buff)

    #################################

    pos12 = pos12 + 6

    temp_input = i[pos12:pos13]

    inputt.append(temp_input)

    #################################


    pos13 = pos13 + 7

    temp_output = i[pos13:pos14]

    output.append(temp_output)

    
    ################################

    pos14 = pos14 + 3
    
    temp_kb = i[pos14:-1]

    kbb.append(temp_kb)


# Write Markdown Matrix

file= open("time.md","w") 

file.write("| Circuit Name | Time (ms) | Lines | # of Nand | # of And | #of Nor | # of Not | # of Buff | # of Inputs | # of Outputs | Graph Size (KB) \n")
file.write("| ------------- |-------------| ------------- |-------------| ------------- |-------------|------------- |-------------|------------- |-------------|-------------|\n")


for f, b,lin,na,a,nr,nt,bf,inp,out,kk in zip(circuits, y,lines,nand,andd,nor,nott,buff,inputt,output,kbb):
        #print(f, b)
        file.write("| " + f + " | " + str(b) + " | "+lin+" | "+na+" | "+a+" | "+nr+" | "+nt+" | "+bf+" | " + inp +" | " + out +" | "+kk+" | \n")


