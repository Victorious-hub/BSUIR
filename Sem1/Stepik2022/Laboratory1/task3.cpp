#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    
	long double a, v_0, t;
	std::cin >> a >> t >> v_0;
	std::cout << std::setprecision(20) << v_0 * t + a * t*t / 2;

}