#include <iostream>
#include <cmath>
#include <iomanip>

int main() {

	long double a1, a100;
	long long d;
	std::cout << std::setprecision(10);
	std::cin >> a1;
	std::cin >> a100;
	d = (a100 - a1) / 99;
	std::cout << d << "\n";
	std::cout << ((a1 + (a1 + 69 * d)) / 2 * 70);
	
}