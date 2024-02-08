import numpy as np


def input_func():
    """
        
    """
    def f(x): 
        return np.log(x)

    left_border, dots_count, right_border = 1, 6, 3

    dots = []
    for i in range(dots_count):
        x = left_border + (right_border - left_border) * i / (dots_count - 1)
        y = f(x)
        dots += [(x, y)]

    return dots, f


def three_diag_solve(A, b):
    A = A.copy()
    b = b.copy()
    n = len(A)

    A[0][1] /= A[0][0]
    for i in range(1, n - 1):
        A[i][i + 1] /= (A[i][i] - A[i][i - 1] * A[i - 1][i])

    b[0] /= A[0][0]
    for i in range(1, n):
        b[i] = (b[i] - A[i][i - 1] * b[i - 1]) / (A[i][i] - A[i][i - 1] * A[i - 1][i])
    x = np.zeros(n)
    x[-1] = b[-1]
    for i in range(n - 2, -1, -1):
        x[i] = b[i] - A[i][i + 1] * x[i + 1]
    return x


def spline_built(dots):
    """
        Значит наш общий отрезок [a, b] условно разбит на отдельные [x_i-1, x_i] задан полином 3-й степени.
        Этот полином - кубический сплайн(эта функция имеет степень не больше 3-х). Дефект сплйна - разница степени функции от порядка
        Условия задания сплайна(граничные требования):
        1. S"(a) = S"(b) = 0
        2. S"'(a) = S"'(b) = 0
        3. S'(a) = S'(b) | S"(a) = S"(b)
        4. S(x_i) = f(x_i) - сплайн интерполирует исходную функцию
        5. Первая и вторая производные - непрырывные дифференцируемые функции
        Сплайн есть на каждом отрезке. Нам только значения определить
        Записывается в виде S(x) = a_i + b_i(x - x_i) + c_i(x - x_i)^2 + .. + n_i(x - x_i)^n
        Для задания сплайна необходимо выполнить еще 4 условия:
        - Каждый полином определяется на 1 и второй точках, потом 2 и 3-ей, потом 3-я и 4-я и т.д
    """
    n = len(dots) - 1
    (x, y) = map(list, zip(*dots))

    # ищем h_i = x_i - x_i-1. Для поиска коэффицентов естественного сплайна(для поиска a_i, b_i, c_i....)
    h = [None]
    for i in range(1, n + 1):
        h += [x[i] - x[i - 1]]

    A = [[None] * n for i in range(n)]

    for i in range(1, n):
        for j in range(1, n):
            A[i][j] = 0.0

    for i in range(1, n - 1):
        A[i + 1][i] = h[i + 1]

    for i in range(1, n):
        A[i][i] = 2 * (h[i] + h[i + 1])

    for i in range(1, n - 1):
        A[i][i + 1] = h[i + 1]

    F = []
    for i in range(1, n):
        F += [3 * ((y[i + 1] - y[i]) / h[i + 1] - (y[i] - y[i - 1]) / h[i])]

    A = [A[i][1:] for i in range(len(A)) if i]

    # коэффицент с считается либо через метод прогонки(последовательное исключение неизвестных), 
    # либо через трехдиагональную матрицу(матрица Якоби)

    c = three_diag_solve(A, F)
    c = [0.0] + list(c) + [0.0]

    def evaluate(xdot):# здесь мы выстраиваем сплайн(как в image.png фотка)
        for i in range(1, len(x)):
            if x[i - 1] <= xdot <= x[i]:
                val = 0
                val += y[i]
                b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
                val += b * (xdot - x[i])
                val += c[i] * ((xdot - x[i]) ** 2)
                d = (c[i] - c[i - 1]) / (3 * h[i])
                val += d * ((xdot - x[i]) ** 3)
                return val
        return None


    def output():
        print("Cubic spline:", '\n')
        for i in range(1, len(x)):
            val = 0
            b = (y[i] - y[i - 1]) / h[i] + (2 * c[i] + c[i - 1]) * h[i] / 3
            d = (c[i] - c[i - 1]) / (3 * h[i])
            print(x[i - 1], x[i], "->")
            print(np.poly1d([d, c[i], b, y[i]]), '\n')

    return evaluate, output
