from unittest import TestCase
from Laboratory1.GausElimination import Gauss
import numpy as np


class TryTesting(TestCase):
    test_matrix = np.array([[1, 2, 4], [-2, 1, -3], [3, -2, -5]], dtype=np.float32)
    tes_vector = np.array([-5, 10, 3], dtype=np.float32)

    test_matrix2 = np.array([[1., 1., 1., 1., 1.],
                             [2., 2., 2., 2., 2.],
                             [3., 3, 3., 3., 3.],
                             [4., 4., 4., 4., 4.],
                             [5., 5., 5., 5., 5.]])
    tes_vector2 = np.array([1, 2, 3, 4, 6], dtype=np.float32)

    test_vector3 = np.array([1, 2, 3, 4, 5], dtype=np.float32)

    test_matrix4 = np.array([[3., -7.0001], [3., -7.]])
    test_vector4 = np.array([0.9998, 1.])

    def test_first_solve(self):
        test_object = Gauss(1, self.test_matrix)
        test_object.gauss_solver(self.test_matrix, self.tes_vector, 1)
        self.assertEqual(test_object.solution_bushes(), 3, msg="Equal")

    def test_second_solve(self):
        test_object = Gauss(1, self.test_matrix)
        test_object.gauss_solver(self.test_matrix, self.tes_vector, 2)
        self.assertEqual(test_object.solution_bushes(), 3, msg="Equal")

    def test_first_solve_not_equals(self):
        test_object = Gauss(1, self.test_matrix)
        test_object.gauss_solver(self.test_matrix, self.tes_vector, 1)
        self.assertNotEqual(test_object.solution_bushes(), None, msg="Not Equal")

    def test_third_solve_pivoting(self):
        test_object1 = Gauss(1, self.test_matrix2)
        test_object1.gaussian_elimination_with_pivoting(self.test_matrix2, self.tes_vector2)

        self.assertEqual(test_object1.check_diagonal_for_zeros(self.test_matrix2, self.tes_vector2),
                         "no solutions", msg="Equation has infinite solutions")

    # Матрица где нет решений системы. Ранг матрицы A меньше ранга расширенной матрицы [A|b]
    def test_third_solve_partial_pivoting(self):
        test_object1 = Gauss(1, self.test_matrix2)
        test_object1.gaussian_elimination_with_partial_pivoting(self.test_matrix2, self.tes_vector2)

        self.assertEqual(test_object1.check_diagonal_for_zeros(self.test_matrix2, self.tes_vector2),
                         "no solutions", msg="Matrix is incompatible")

    def test_fifth_solve_pivoting(self):
        test_object1 = Gauss(2, self.test_matrix4)
        test_object1.gauss_solver(self.test_matrix4, self.test_vector4, 2)
        res = np.array([5., 2.])
        self.assertTrue(np.allclose(test_object1.x, res), msg="infinite solutions")
