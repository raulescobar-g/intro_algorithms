import matplotlib.pyplot as plt
import numpy as np
import random
from time import time
import heapq


def mergeSort(myList):
    if len(myList) > 1:
        mid = len(myList) // 2
        left = myList[:mid]
        right = myList[mid:]

        # Recursive call on each half
        mergeSort(left)
        mergeSort(right)

        # Two iterators for traversing the two halves
        i = 0
        j = 0
        
        # Iterator for the main list
        k = 0
        
        while i < len(left) and j < len(right):
            if left[i] < right[j]:
              # The value from the left half has been used
              myList[k] = left[i]
              # Move the iterator forward
              i += 1
            else:
                myList[k] = right[j]
                j += 1
            # Move to the next slot
            k += 1

        # For all the remaining values
        while i < len(left):
            myList[k] = left[i]
            i += 1
            k += 1

        while j < len(right):
            myList[k]=right[j]
            j += 1
            k += 1

def algo1(k,list):
    answers = []
    for i in range(len(list)):
        for j in range(len(list)):
            if list[i] + list[j] == k:
                answers.append([i,j])
    return 0


def algo2(k,sorted):
    mergeSort(sorted)


    i = 0
    j = len(sorted) - 1
    while sorted[i] + sorted[j] != k:
        if sorted[i] + sorted[j] < k:
            i += 1
        else:
            j -=1

        if j == i or j-1 == i:
            return 0
            
        
    



time1 = []
time2 = []
n = 300
k = random.randint(0,1000)
list = []
for i in range(1,n):
        list.append(random.randint(0,1000))

for i in range(50,n,10):
    t0 = time()
    algo1(k,list[0:i])
    t1 = time()
    algo2(k,list[0:i])
    t2 = time()

    time1.append(t1-t0)
    time2.append(t2-t1)



plt.plot(time1)
plt.plot(time2)
plt.legend(('O($N^2$)','O($NlogN$)'))
plt.show()






