import numpy as np
import math
from speed import Graphic
from accuracy import check_accuracy
from tests import *
from sturms_row import *
from nonlinear import *


class Nonlinear:
    roots = []
    def __init__(self, intervals=None):
        self.intervals = intervals

    @staticmethod
    def separator():
        for i in range(2):
            print('-' * 50)

    def get_intervals(self, interval,func):
        self.intervals = get_1root_intervals(get_sturm_row(func), interval)
        print(f"\nIntervals with 1 root: {[x for x in self.intervals]}\n")
        return self.intervals

    def check_methods(self):
        for inter in self.intervals:
            print(f'\n\t\tCurrent interval is: {inter}')

            self.separator()
            secant_ans = secant(y, inter)
            print(f'**** Solving with Secant method ****\n'
                  f'ROOT: {secant_ans[0]}\n'
                  f'Iteration: {secant_ans[1]}')

            self.separator()
            bisect_ans = bisection(y, inter)
            print(f'**** Solving with Bisection method ****\n'
                  f'ROOT: {bisect_ans[0]}\n'
                  f'Iteration: {bisect_ans[1]}')

            self.separator()
            newton_ans = newton(y, inter)
            print(f'**** Solving with Newton method ****\n'
                  f'ROOT: {newton_ans[0]}\n'
                  f'Iteration: {newton_ans[1]}')

            self.separator()
            correct_root = np.roots([1, a, b, c])
            print(f'**** Solving with Numpy ****\n'
                  f'ROOTS: {correct_root}\n')

            self.roots.append(newton_ans[0])
            check_accuracy(sorted(list(filter(lambda x: interval[0] <= x <= interval[1], correct_root))),
                           sorted(self.roots))

            Graphic()


interval = (-10, 10)
x, y = symbols('x y')
a = -19.7997
b = 28.9378
c = 562.833
y = x ** 3 + a * x ** 2 + b * x + c
obj = Nonlinear()
print(f"Choose what you would like to start\n1.Variant test case\n2.User case\n3.Test cases")
inp = int(input())
match inp:
    case 1:
        obj.get_intervals(interval, y)
        obj.check_methods()
    case 2:
        y = y_7
        obj.get_intervals(interval, y)
        obj.check_methods()
    case _:
        raise Exception("Wrong input!")
