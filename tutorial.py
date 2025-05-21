# Joseph Whittier - 5/20/2025
# Python tutorial

# print to console
print("Hello World")

# creating data and plotting, saving image
import numpy as np
import matplotlib.pyplot as plt

def Gauss(x,mu,sigma): # normalized Gaussian distribution in x
    A=1/(np.sqrt(2*np.pi*sigma**2))
    return A*np.exp(-(x-mu)**2/(2*sigma**2))

x=np.arange(0,10,0.01) # x from 0 to 10, step size 0.01
y=Gauss(x,5,2) # distribution with mean of 5, std of 2

plt.plot(x,y) # plotting data with title, and saving to file
plt.title("Normalized Gaussian")
plt.savefig('gaussian.png')
plt.close()

# variables, loops, if/else, file i/o
# reading three different data files from another project
pi2=[[float(x) for x in line.split()] # pi/2 offset
     for line in open("pass5pi2Poincare.txt", "r").readlines()]

pi4=[[float(x) for x in line.split()] # pi/4 offset
     for line in open("pass5pi4Poincare.txt", "r").readlines()]

pi0=[[float(x) for x in line.split()] # no offset
     for line in open("pass50Poincare.txt", "r").readlines()]

# Transposing data for plotting
pi2T=np.zeros((2,len(pi2)))
for i in range(len(pi2)):
    pi2T[0][i]=pi2[i][0]
    pi2T[1][i]=pi2[i][1]

pi4T=np.zeros((2,len(pi4)))
for i in range(len(pi4)):
    pi4T[0][i]=pi4[i][0]
    pi4T[1][i]=pi4[i][1]

pi0T=np.zeros((2,len(pi0)))
for i in range(len(pi0)):
    pi0T[0][i]=pi0[i][0]
    pi0T[1][i]=pi0[i][1]

# Plotting datasets together with legend (saving file)
plt.title("Great Wave off Poincare")
plt.plot(pi2T[0],pi2T[1],'b.',label="2*Pi Offset")
plt.plot(pi4T[0],pi4T[1],'r.',label="4*Pi Offset")
plt.plot(pi0T[0],pi0T[1],'k.',label="No Offset")
plt.legend()
plt.savefig('PoincareWave.png')
plt.close()

# saving concatenated data
f=open("new.txt", "w")
f.write("Pi/2 Pi/4 0\n")
for i in range(len(pi0T[0])):
    f.write((str(pi2T[0][i])+" "+str(pi2T[1][i])+" "))
    f.write((str(pi4T[0][i])+" "+str(pi4T[1][i])+" "))
    f.write((str(pi0T[0][i])+" "+str(pi0T[1][i])+"\n"))
f.close()