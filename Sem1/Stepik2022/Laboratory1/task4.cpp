#include <iostream>
#include <cmath>
#include <iomanip>

int main() {

	double b1;
	double q = 1;
	std::cin >> b1;
	q /= 1001;
	std::cout << std::setprecision(8) << b1 / (1 - q);
    
}