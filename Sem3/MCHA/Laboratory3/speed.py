import numpy as np
from scipy.optimize import bisect, newton
import matplotlib.pyplot as plt


def Graphic():
    
    def f(x):
        
        return x ** 4 - 10.5 * x ** 3 + 5.51 * x ** 2 - 89.98 * x + 12.87

    def fprime(x):
        return 4 * x ** 3 - 10.5 * 3 * x ** 2 + 5.51 * 2 * x - 89.98

    def f_ext(x):
        x_all.append(x)
        return x ** 4 - 10.5 * x ** 3 + 5.51 * x ** 2 - 89.98 * x + 12.87

    x_all = []
    x0 = bisect(f_ext, -1, 1)
    x_all.append(x0)
    x_bisect = x_all
    x, r = bisect(f, -1, 1, full_output=True)
    print(r)
    print(x_bisect)
    x_all = []
    x0 = newton(f_ext, -1)
    x_all.append(x0)
    x_secant = x_all
    x, r = newton(f, -1, full_output=True)
    print(r)
    print(x_secant)
    x_all = []
    x0 = newton(f_ext, -1, fprime=fprime)
    x_all.append(x0)
    x_newton = x_all
    x, r = newton(f, 1, fprime=fprime, full_output=True)
    print(r)

    print(x_newton)
    plt.semilogy(np.abs(np.array(x_bisect) - 0.14406391569536936), label='Bisect')
    plt.semilogy(np.abs(np.array(x_secant) - 0.14406391569536936), label='Secant')
    plt.semilogy(np.abs(np.array(x_newton) - 0.14406391569536936), label='Newton')
    plt.legend()
    plt.show()
