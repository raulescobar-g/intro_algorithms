import matplotlib.pyplot as plt
import numpy as np


def psi(k0,dk,x,A=1):

    tau = ((dk) * x) / (2)

    osci = (np.cos(k0*x))

    env = np.sin(tau)

    p = (2*A *env * osci) / x

    return p,env,osci



x = np.linspace(-2*np.pi,2*np.pi,1000)
dk = np.pi/2
k0 = 6000
p,env,osci = psi(k0,dk,x)

'''
plt.plot(x,p**2)
plt.plot(x,p)
plt.title('WaveFunction')
plt.legend(('$|\Psi|^2$','$\Psi$'))
plt.grid()
plt.show()

plt.plot(x,osci)
plt.plot(x, osci**2)
plt.title('Oscillating term')
plt.legend(('$cos(k_0x)$','$cos^2(k_0x)$'))
plt.grid()
plt.show()'''

plt.plot(x,4*env**2/x**2)
plt.plot(x,env**2)
plt.plot()
plt.title('Envelope term')
plt.legend(('$4Asin^2(\Delta kx / 2)/x^2$','$sin^2(\Delta kx / 2)$'))
plt.grid()
plt.show()




