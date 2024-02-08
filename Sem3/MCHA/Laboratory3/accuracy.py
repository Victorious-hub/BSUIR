def check_accuracy(w, x):
    for i in range(len(x)):
        if (abs(x[i] - w[i]) / abs(x[i])) >= 0.0001:
            return False
        else:
            print(f"|{x[i]} - {w[i]}| < 0.0001")
    return True