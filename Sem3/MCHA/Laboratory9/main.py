from matplotlib.pyplot import plot, show


def f(x, y):
    return a * (1 - y ** 2) / ((1 + m) * x ** 2 + y ** 2 + 1)


def euler(num):
    x = [cond[0]]
    y = [cond[1]]
    step = (right - left) / num
    for i in range(1, num + 1):
        x.append(left + step * i)
        y.append(y[-1] + step * f(x[-2], y[-1]))
    return x, y


def euler_modified(num):
    x = [cond[0]]
    y = [cond[1]]
    step = (right - left) / num
    for i in range(1, num + 1):
        x.append(left + step * i)
        y.append(y[-1] + step * f(x[-2] + step / 2, y[-1] + step / 2 * f(x[-2], y[-1])))
    return x, y


def runge_kutta2(num):
    x, y_euler = euler(num)
    step = (right - left) / num
    y = [cond[1]]
    for i in range(1, num + 1):
        y.append(y[-1] + step * (f(x[i-1], y[-1]) + f(x[i], y_euler[i])) / 2)
    return x, y


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

    # euler
    print("euler")
    n = 1
    (x_cur, y_cur) = euler(n)
    n *= 2
    while True:
        (x_prev, y_prev) = (x_cur, y_cur)
        (x_cur, y_cur) = euler(n)
        dif = get_difference(y_prev, y_cur)
        print(f"h = {(right - left) / n}     dif = {dif}")
        if dif < eps:
            break
        n *= 2
    print(f"шаг: {(right - left) / n}")
    plot_(x_cur, y_cur)

    # modified euler
    print("euler modified")
    n = 1
    (x_cur, y_cur) = euler_modified(n)
    n *= 2
    while True:
        (x_prev, y_prev) = (x_cur, y_cur)
        (x_cur, y_cur) = euler_modified(n)
        dif = get_difference(y_prev, y_cur)
        print(f"h = {(right - left) / n}     dif = {dif}")
        if dif < eps:
            break
        n *= 2
    print(f"шаг: {(right - left) / n}")
    plot_(x_cur, y_cur)

    # runge kutta
    print("runge kutta")
    n = 1
    (x_cur, y_cur) = runge_kutta2(n)
    n *= 2
    while True:
        (x_prev, y_prev) = (x_cur, y_cur)
        (x_cur, y_cur) = runge_kutta2(n)
        dif = get_difference(y_prev, y_cur)
        print(f"h = {(right - left) / n}     dif = {dif}")
        if dif < eps:
            break
        n *= 2
    print(f"шаг: {(right - left) / n}")
    plot_(x_cur, y_cur)

    # runge kutta 4 order
    print("runge kutta")
    n = int((right - left) / eps ** (1 / 4)) + 1
    (x_cur, y_cur) = runge_kutta4(n)
    n *= 2
    while True:
        (x_prev, y_prev) = (x_cur, y_cur)
        (x_cur, y_cur) = runge_kutta4(n)
        dif = get_difference(y_prev, y_cur)
        print(f"h = {(right - left) / n}     dif = {dif}")
        if dif < eps:
            break
        n *= 2
    print(f"шаг: {(right - left) / n}")
    plot_(x_cur, y_cur)

    show()
