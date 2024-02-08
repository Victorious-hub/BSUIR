from typing import Any
from sympy import symbols, lambdify


def bisection(function: Any, interval: tuple, tol=0.0001) -> tuple[float | Any, int]:
    x, y = symbols('x y')
    a, b = interval
    f = lambdify(x, function)

    if f(a) * f(b) > 0:# если на интервале более одного корня или их нет
        raise Exception("Bisection method couldn't solve f(x) = 0, because f(a) * f(b) >= 0\n"
                        "--> more than 1 root or no roots in the interval")

    iteration = 0
    while (b - a) / 2 > tol: # пока разница между значениями интервалов !> погрешности
        c = (a + b) / 2 # половина отрезка
        if f(c) == 0: # наш корень
            return c, iteration

        if f(a) * f(c) < 0: # корень лежит на отрезке [a; c].
            b = c
        else:
            a = c # корень лежит на отрезке [c; b].

        iteration += 1

    return (a + b) / 2, iteration


def secant(function: Any, interval: tuple, tol=0.0001) -> tuple[float | Any, int]:#  его сходимость равна золотому сечению:
    x, y = symbols('x y')
    a, b = interval
    f = lambdify(x, function)

    if f(a) * f(b) > 0: # если на интервале более одного корня или их нет
        raise Exception(f"Secant method couldn't solve f(x) = 0, because f(a) * f(b) = {f(a) * f(b)} >= 0\n"
                        f"--> more than 1 root on ({(a, b)}) or no roots)")

    iteration = 0
    while True:
        c = b - (f(b) * (b - a)) / (f(b) - f(a))# вычисляем значение точки по формуле
        if abs(f(c)) < tol or abs(b - a) < tol:
            return c, iteration

        a, b = b, c
        iteration += 1


def newton(function: Any, interval: tuple, tol=0.0001) -> tuple[float | Any, int]:
    x, y = symbols('x y')
    x_start = (interval[0] + interval[1]) / 2
    f = lambdify(x, function)

    if f(interval[0]) * f(interval[1]) > 0: # пока разница между значениями интервалов !> погрешности
        raise Exception(
            f"Newton method couldn't solve f(x) = 0, because f(a) * f(b) = {f(interval[0]) * f(interval[1])} >= 0\n"
            f"--> more than 1 root on ({(interval[0], interval[1])}) or no roots)")
    
    f_diff = lambdify(x, function.diff())

    x_newton = x_start - f(x_start) / f_diff(x_start)

    iteration = 0
    while abs(f(x_newton)) > tol:
        x_newton = x_newton - f(x_newton) / f_diff(x_newton)
        iteration += 1

    return x_newton, iteration


def relaxation(function: Any, interval: tuple, tol=0.0001, max_iter=100000) -> tuple[float | Any, int]:
    x, y = symbols('x y')
    a, b = interval[0], interval[1]
    f = lambdify(x, function, modules=['numpy', 'mpmath'])

    x_iter = (a + b) / 2
    x_delta = tol * 2
    iteration = 1
    while (abs(f(x_iter)) > tol or x_delta > tol) and iteration < max_iter:
        if f(x_iter) == 0:
            return x_iter, iteration

        x_delta = x_iter
        x_iter = f(x_iter)
        x_delta = abs(x_delta - x_iter)
        iteration += 1

    if iteration == max_iter:
        raise Exception("Maximum iterations reached. The method did not converge.")
    return x_iter, iteration


def simple_iteration(function: Any, interval: tuple, tol=0.00001) -> tuple[float | Any, int]:
    x = symbols('x')
    a, b = interval[0], interval[1]
    phi = (function + x).subs(x, function)
    phi_diff = phi.diff(x)
    phi_lambdified = lambdify(x, phi, "numpy")
    phi_diff_lambdified = lambdify(x, phi_diff, "numpy")

    if abs(phi_diff_lambdified(a)) >= 1 or abs(phi_diff_lambdified(b)) >= 1:
        raise Exception(f"Simple iteration method couldn't solve f(x) = 0, because |phi'(a)| >= 1 or |phi'(b)| >= 1\n"
                        f"--> not convergent on ({(a, b)})")

    x_simple = (a + b) / 2

    x_delta = tol * 2
    iteration = 1
    while abs(function.subs(x, x_simple)) > tol or x_delta > tol:
        if function.subs(x, x_simple) == 0:
            return x_simple, iteration

        x_delta = x_simple
        x_simple = phi_lambdified(x_simple)
        x_delta = abs(x_delta - x_simple)
        iteration += 1

    return x_simple, iteration
