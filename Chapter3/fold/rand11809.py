from random import *
data=[]
for i in range(0,20):
    m=randint(0,9)
    e=randint(1,10)
    a=(2**(m+1)-1)/2**(m+1)
    k=a*2**(2**e-1)
    print(format(k,'15.15e'))
    data.append((m,e))
for i in range(0,len(data)):
    print(data[i][0],data[i][1])
