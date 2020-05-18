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
#from scipy.interpolate import make_interp_spline, BSpline

flush = ['Serial NFD', 'Serial FD', 'Parallel NFD', 'Parallel FD']

# Bimodals (No Shared Hysteresis)

y3 = [100,349,205,456] #c6288
y1 = [100, 587, 213, 1385] # c880
y4 = [100,600,219,1024] # c7552
y2 = [100,190,206,382] #s1488




# Colors = https://matplotlib.org/3.1.0/gallery/color/named_colors.html
# Lines = https://matplotlib.org/gallery/lines_bars_and_markers/line_styles_reference.html
# General = https://matplotlib.org/3.2.1/api/_as_gen/matplotlib.pyplot.plot.html
# Markers = https://matplotlib.org/3.2.1/api/markers_api.html

# cornflowerblue
# dodgerblue
# steelblue

# x s ^ v d

x = range(4)
pylab.xticks(x, flush)
plt.xlabel('Simulation Mode')
plt.ylabel('% Increase')
plt.title('')
plt.plot(x,y1, color='black',linestyle='-',linewidth=1, marker='x', markersize=4)
plt.plot(x,y2, color='black',linestyle='-',linewidth=1, marker='s', markersize=4)
plt.plot(x,y3, color='black',linestyle='-',linewidth=1,marker='^', markersize=4)
plt.plot(x,y4, color='black',linestyle='-',linewidth=1,marker='v', markersize=4)
plt.legend(['c880','s1488','c6288','c7552'])
plt.grid(axis='y')
#plt.show()
plt.savefig("figure.png",dpi=300)

plt.clf()

y5 = [100, 294, 196, 315] #c17
y6 = [100,232,138,435] #s27
y7 = [100,160,182,333] #s298
y8 = [100,188,207,376] #s444 


x = range(4)
pylab.xticks(x, flush)
plt.xlabel('Simulation Mode')
plt.ylabel('% Increase')
plt.title('')
plt.plot(x,y5, color='black',linestyle='-',linewidth=1, marker='x', markersize=4)
plt.plot(x,y6, color='black',linestyle='-',linewidth=1, marker='s', markersize=4)
plt.plot(x,y7, color='black',linestyle='-',linewidth=1,marker='^', markersize=4)
plt.plot(x,y8, color='black',linestyle='-',linewidth=1,marker='v', markersize=4)
plt.legend(['c17','s27','s298','s444'])
plt.grid(axis='y')
#plt.show()
plt.savefig("figure1.png",dpi=300)

plt.clf()

y9 = [100,119,199,232] #s368
y10 = [100,213,200,411] #s382
y11 = [100,187,209,342] #s400
y12 = [100,155,193,285] #s420



x = range(4)
pylab.xticks(x, flush)
plt.xlabel('Simulation Mode')
plt.ylabel('% Increase')
plt.title('')
plt.plot(x,y9, color='black',linestyle='-',linewidth=1, marker='x', markersize=4)
plt.plot(x,y10, color='black',linestyle='-',linewidth=1, marker='s', markersize=4)
plt.plot(x,y11, color='black',linestyle='-',linewidth=1,marker='^', markersize=4)
plt.plot(x,y12, color='black',linestyle='-',linewidth=1,marker='v', markersize=4)
plt.legend(['s368','s382','s400','s420'])
plt.grid(axis='y')
#plt.show()
plt.savefig("figure2.png",dpi=300)


plt.clf()

y13 = [100,100,203,1145] #c1355
y14 = [100,271,202,512] #c1908
y15 = [100,617,202,1134] #c2670
y16 = [100,288,205,576] #s5378


x = range(4)
pylab.xticks(x, flush)
plt.xlabel('Simulation Mode')
plt.ylabel('% Increase')
plt.title('')
plt.plot(x,y13, color='black',linestyle='-',linewidth=1, marker='x', markersize=4)
plt.plot(x,y14, color='black',linestyle='-',linewidth=1, marker='s', markersize=4)
plt.plot(x,y15, color='black',linestyle='-',linewidth=1,marker='^', markersize=4)
plt.plot(x,y16, color='black',linestyle='-',linewidth=1,marker='v', markersize=4)
plt.legend(['s1355','c1908','c2670','c5378'])
plt.grid(axis='y')
#plt.show()
plt.savefig("figure3.png",dpi=300)




