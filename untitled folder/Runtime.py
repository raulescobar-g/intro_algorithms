import time
import matplotlib.pyplot as plt
import numpy as np

def fragment1(n):
    sum = 0
    for i in range(1,n):
        sum = sum + 1
    return sum

def fragment2(n):
    sum = 0
    for i in range(1,n):
        for j in range(1,i):
            sum = sum + 1
    return sum

def fragment3(n):
    sum = 0
    for i in range(1,n):
        for j in range(1,i**2):
            for k in range(1,j):
                sum = sum + 1
    return sum

p=50
times1 = np.zeros(p)
times2 = np.zeros(p)
times3 = np.zeros(4)
inputs = np.linspace(1,200,p,dtype=int)


for i in range(len(inputs)):
    t1 = time.time()
    a = fragment1(inputs[i])
    t1 = time.time() - t1
    t2 = time.time()
    b = fragment2(inputs[i])
    t2 = time.time() - t2
    t3 = time.time()
    if (inputs[i]<17):
        c = fragment3(inputs[i])
        t3 = time.time() - t3
        times3[i] = t3
    
    times1[i] = t1
    times2[i] = t2

    

plt.plot(inputs,times1,color='r')
plt.plot(inputs,times2,color='b')
plt.plot(inputs[0:4],times3,color='k')
plt.legend(("O(n)","O($n^2$)","O($n^5$)"))
plt.show()




