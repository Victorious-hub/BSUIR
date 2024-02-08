import numpy as np


class Gauss:

    def __init__(self, k: int, A: np.ndarray):
        self.k = k
        self.A = A
        self.x = np.zeros(len(self.A))
        self.infelicity = []

    def check_diagonal_for_zeros(self, matrix: np.ndarray, vector_b: np.ndarray):
        matrix_size = len(matrix)
        for i in range(matrix_size):
            if matrix[i][i] == 0:
                swapped = False
                for j in range(matrix_size):
                    if matrix[i][j] != 0 and matrix[j][i] != 0:
                        self.swap_columns(matrix, i, j)
                        swapped = True
                        break
                if not swapped:
                    if vector_b[i] == 0:
                        return f"infinite solutions"
                    else:
                        return "no solutions"
        print("Result")
        print(matrix)
        return f"solutions exist"

    def back_substitution(self, A: np.ndarray, b: np.ndarray):
        n = len(A)
        for k in reversed(range(0, n)):
            self.x[k] = (b[k] - sum(A[k][i] * self.x[i] for i in range(k + 1, n))) / A[k][k]

    def output_solution(self):
        print(f"Корни\n")
        for i in range(len(self.x)):
            print(str(i) + ".", "%.20f" % self.x[i])

    def solution_bushes(self):
        return len(self.x)

    @staticmethod
    def gaussian_elimination(matrix: np.ndarray, vector_b: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
        print(f"Исходная матрица\nМатрица: {matrix}\n Вектор b:{vector_b}")

        matrix_size = len(matrix)
        for index, row in enumerate(matrix):
            diag_elem = row[index]
            row /= diag_elem
            vector_b[index] /= diag_elem
            current_b_factor = vector_b[index]

            for lower_row_index in range(index + 1, matrix_size):
                factor = matrix[lower_row_index][index]
                matrix[lower_row_index] -= factor * row
                vector_b[lower_row_index] -= factor * current_b_factor
        print(f"Трансформированная матрица\nМатрица: {matrix}\n Вектор b:{vector_b}")

        return matrix, vector_b

    def gauss_solver(self, A: np.ndarray, b: np.ndarray, solution_type: int):
        match solution_type:
            case 1:
                print("Метод Гаусса")
                self.gaussian_elimination(A, b)
            case 2:
                print("Метод Гаусса методом частичного выбора")
                self.gaussian_elimination_with_partial_pivoting(A, b)
            case 3:
                print("Метод Гаусса методом полного выбора")
                self.gaussian_elimination_with_pivoting(A, b)

        match self.check_diagonal_for_zeros(A, b):
            case "infinite solutions":
                raise Exception(f"Equation has infinite solutions")
            case "no solutions":
                raise Exception(f"Equation has no solutions")
            case _:
                self.back_substitution(A, b)

    @staticmethod
    def gaussian_elimination_with_partial_pivoting(matrix: np.ndarray, vector_b: np.ndarray):
        print(f"Исходная матрица\nМатрица: {matrix}\n Вектор b:{vector_b}")

        matrix_size = len(matrix)
        for row_index in range(matrix_size):
            max_row_index = row_index + np.argmax(abs(matrix[row_index:, row_index]))
            if max_row_index != row_index:
                matrix[[row_index, max_row_index]] = matrix[[max_row_index, row_index]]  # swap
                change = vector_b[max_row_index]
                vector_b[max_row_index] = vector_b[row_index]
                vector_b[row_index] = change
            row = matrix[row_index]
            diag_elem = row[row_index]
            if abs(diag_elem) < 1e-10:
                raise Exception(f"Matrix is incompatible")
            row /= diag_elem
            vector_b[row_index] /= diag_elem
            current_b_factor = vector_b[row_index]
            for lower_row in range(row_index + 1, matrix_size):
                factor = matrix[lower_row][row_index]
                matrix[lower_row] -= factor * row
                vector_b[lower_row] -= factor * current_b_factor
        print(f"Трансформированная матрица\nМатрица: {matrix}\n Вектор b:{vector_b}")
        return matrix, vector_b

    def gaussian_elimination_with_pivoting(self, matrix: np.ndarray, vector_b: np.ndarray):
        print(f"Исходная матрица\nМатрица: {matrix}\n Вектор b:{vector_b}")

        matrix_size = len(matrix)
        for row_index in range(matrix_size):
            max_row_index, max_col_num = self.max_element(matrix, row_index)
            if max_row_index != row_index:
                matrix[[row_index, max_row_index]] = matrix[[max_row_index, row_index]]  # swap
                change = vector_b[max_row_index]
                vector_b[max_row_index] = vector_b[row_index]
                vector_b[row_index] = change
            self.swap_columns(matrix, row_index, max_col_num)
            row = matrix[row_index]
            diag_elem = row[row_index]
            if abs(diag_elem) < 1e-10:
                raise Exception(f"Matrix is incompatible")
            row /= diag_elem
            vector_b[row_index] /= diag_elem
            current_b_factor = vector_b[row_index]
            for lower_row in range(row_index + 1, matrix_size):
                factor = matrix[lower_row][row_index]
                matrix[lower_row] -= factor * row
                vector_b[lower_row] -= factor * current_b_factor
        print(f"Трансформированная матрица\nМатрица: {matrix}\n Вектор b:{vector_b}")
        return matrix, vector_b

    @staticmethod
    def max_element(A: np.ndarray, k: int) -> list[int]:
        maximum = A[k - 1][k - 1]

        max_index = [k - 1, k - 1]
        for i in range(k - 1, len(A)):
            for j in range(k - 1, len(A)):
                if maximum < A[i][j]:
                    maximum = A[i][j]
                    max_index = [i, j]
        return max_index

    @staticmethod
    def swap_columns(a: np.ndarray, i: int, j: int):
        for k in range(len(a)):
            a[k][i], a[k][j] = a[k][j], a[k][i]

    def relative_infelicity(self):
        print("Относительная погрешность")
        for i in range(len(self.x)):
            print(abs(float("%.4f" % self.x[i])), self.x[i])
            self.infelicity.append("%.16f" % abs(float("%.4f" % self.x[i]) - self.x[i]))
            print("%.12f" % float(self.infelicity[i]))

    def infelicity_result(self):
        print("Результативная погрешность")
        for i in range(len(self.x)):
            res = float(self.infelicity[i]) / abs(self.x[i])
            print("%.16f" % res)


C = np.array([[0.2, 0, 0.2, 0, 0],
              [0, 0.2, 0, 0.2, 0],
              [0.2, 0, 0.2, 0, 0.2],
              [0, 0.2, 0, 0.2, 0],
              [0, 0, 0.2, 0, 0.2]])
D = np.array([[2.33, 0.81, 0.67, 0.92, -0.53],
              [-0.53, 2.33, 0.81, 0.67, 0.92],
              [0.92, -0.53, 2.33, 0.81, 0.67],
              [0.67, 0.92, -0.53, 2.33, 0.81],
              [0.81, 0.67, 0.92, -0.53, 2.33]])
b = np.array([4.1, 4.2, 4.2, 4.2, 4.2])

k = 27
A = k * C + D
b = np.transpose(b)

while True:
    print(f"Выберите метод решения:\n1. Стандартные значения(1) \n2. Собственные значения(2) \n3. Выход из программы(0)")
    choose = input()
    if choose == "1":
        test_matrix4 = np.array([[0.,1.,1.], [1.,0.,1.],[1.,1.,0.]])
        test_vector4 = np.array([6.,9.,12.])
        obj = Gauss(1,test_matrix4)
        obj.gauss_solver(test_matrix4, test_vector4, 2)
        obj.output_solution()
    elif choose == "2":
        print(f"Введите вектор b")
        vector_b = np.array(list(map(float, input().split())))
        print(f"Введите матрицу A")
        matrix = np.array([list(map(float, input().split())) for _ in range(len(vector_b))])
        obj1 = Gauss(k, matrix)
        obj1.gauss_solver(matrix, vector_b, 2)
        obj1.output_solution()
    elif choose == "0":
        break
    else:
        print(f"Неверный ввод. Попробуйте снова")
        continue


