import matplotlib.pyplot as plt
import numpy as np
from gaussKronrod import integrate

#plank radiation law
def Intensity(lam):
    T = 3000
    h = 6.62607004 * (10**-34)
    c = 299792458
    k = 1.38064852 * (10**-23)
    intensity = ((2 * h * c**2)/(lam**5)) * ((1) / (np.exp((h*c)/(lam*k*T)) - 1))
    return intensity

#function plots graphs
def plot_graphs():
    x = np.linspace(0,0.0001,10000)
    y = Intensity(x)
    x0 = np.linspace(0.0000004,0.0000007,100)
    y0 = Intensity(x0)
    x1 = np.linspace(0.0000001,0.0000003,100)
    y1 = Intensity(x1)
    x2 = np.linspace(0.0000008,0.000001,100)
    y2 = Intensity(x2)

    plt.plot(x,y)
    plt.xlabel("Wavelength")
    plt.ylabel("Intensity")
    plt.title("Planck's Radiation Law")
    plt.show()

    plt.plot(x0,y0,'blue')
    plt.plot(x1,y1,'purple')
    plt.plot(x2,y2,'r')

    plt.xlabel("Wavelength")
    plt.ylabel("Intensity")
    plt.title("Planck's Radiation Law")
    plt.legend(("Visible Region","UltraViolet","Infrared"))
    plt.show()

#prints ratios for part b
def ratios():
    max = (2.898*(10**-3))/3000
    i4 = Intensity(0.0000004)
    i7 = Intensity(0.0000007)
    print("Ratio of 400nm Intensity to maximum: ",i4/Intensity(max))
    print("Ratio of 700nm Intensity to maximum: ",i7/Intensity(max))

#numerically integrate for part a
def integrals():
    visible = integrate(0.0000004,0.0000007,Intensity)
    ultraviolet = integrate(0.0000001,0.0000004,Intensity)
    infrared = integrate(0.0000007,0.000001,Intensity)
    print("Sum of intensities: \n")
    print("For visible light sum of intensities is: ",visible)
    print("For ultraviolet light sum of intensities is: ",ultraviolet)
    print("For infrared light sum of intensities is: ",infrared)

integrals()
