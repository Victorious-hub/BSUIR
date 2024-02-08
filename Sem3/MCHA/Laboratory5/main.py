import numpy
import methods
import test
import task

numpy.set_printoptions(suppress=True, precision=4, floatmode="fixed")

A = test.A_1

print("Jacobi rotation method\n", '* ' * 15)
(w, v, iter) = methods.Jacobi(A.copy())
print(f"Eigenvalues: {w}")
print(f"Eigenvectors: {v}")
print(f"Iterations: {iter}")

print("\nPower iteration\n", '* ' * 15)
(w, v, iter) = methods.Step(A.copy())
print(f"Max eigenvalue: {w:.4f}")
print(f"Eigenvector: {v}")
print(f"Iterations: {iter}")

print("\nValidation\n", '* ' * 15)
(w, v) = numpy.linalg.eig(A.copy())
print(f"Eigenvalues: {w}")
print(f"Eigenvectors: {v}")


