from matplotlib.pyplot import plot, show


def f(x, y):
    return a * (1 - y ** 2) / ((1 + m) * x ** 2 + y ** 2 + 1)


def runge_kutta4(num):
    step = (right - left) / num
    x = [cond[0]]
    y = [cond[1]]
    for i in range(1, num + 1):
        k1 = step * f(x[-1], y[-1])
        k2 = step * f(x[-1] + step / 2, y[-1] + k1 / 2)
        k3 = step * f(x[-1] + step / 2, y[-1] + k2 / 2)
        k4 = step * f(x[-1] + step, y[-1] + k3)
        y.append(y[-1] + (k1 + 2 * k2 + 2 * k3 + k4) / 6)
        x.append(left + step * i)
    return x, y


def adams(num):
    step = (right - left) / num
    x = [cond[0], cond[0] + step]
    y = [cond[1], runge_kutta4(num)[1][1]]
    for i in range(2, num + 1):
        y.append(y[-1] + step * (3 / 2 * f(x[-1], y[-1]) - 1 / 2 * f(x[-2], y[-2])))
        x.append(left + step * i)
    return x, y


def get_difference(sol1, sol2):
    max_ = 0.0
    for i in range(len(sol1)):
        max_ = max(max_, abs(sol1[i] - sol2[2*i]))
    return max_


def plot_(x, y):
    plot(x, y)


if __name__ == '__main__':
    left = 0.
    right = 1.
    a = 1.1
    m = 2.0
    cond = (0., 0.)
    eps = 0.001

    print("\nadams")
    n = int((right - left) / eps ** (1 / 4)) + 1
    (x_cur, y_cur) = adams(n)
    n *= 2
    while True:
        (x_prev, y_prev) = (x_cur, y_cur)
        (x_cur, y_cur) = adams(n)
        dif = get_difference(y_prev, y_cur)
        print(f"h = {(right - left) / n}     dif = {dif}")
        if dif < eps:
            break
        n *= 2
    print(f"h: {(right - left) / n}")
    plot_(x_cur, y_cur)

    show()
