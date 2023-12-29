#include <iostream>
#include <iomanip>

int main() {

	long double Z, a, b, c, d;
	std::cin >> a >> b >> c >> d;
	if (c == 0) 
    {
        std::cout << "ERROR";
    }else if (a == 0 && b == 0)
    { 
        std::cout << 0;
    }else if (c >= d && a < d) 
    {
		Z = a + b / c; std::cout << std::setprecision(20) << Z;
	}else if (c < d && a >= d)
    {
		Z = a - b / c; std::cout << std::setprecision(20) << Z;
	}

}