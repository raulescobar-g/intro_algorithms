import matplotlib.pyplot as plt
import numpy as np

def vels(bk):
    c = 3 * (10**8)
    root = np.sqrt(1-((np.pi**2)/((bk**2))))
    p = (c)/(root)
    g = p*(1 - ((np.pi**2)/(bk**2)))
    return p,g


x = np.linspace(0,4,10000)
y1,y2 = vels(x)

plt.plot(x,y1)
plt.plot(x,y2)
plt.xlabel("bk")
plt.ylabel('velocities')
plt.legend(('Phase velocity','Group velocity'))
plt.grid()
plt.show()


#transfereed everything to unreal and took all the videos
#in total about 200-300 per sign but with data augmentation it could be more
#need to get the segmentation
#theres a way to output it but i have to mess with unreal engine settings still not super sure how its done
#i trie 
#seperate the video into frames for machine learning part