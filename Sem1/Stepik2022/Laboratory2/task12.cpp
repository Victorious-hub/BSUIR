#include <iostream>

int main() {
    
	long double a, b, c, x, y;
	std::cin >> a >> b >> c >> x >> y;
	if (a <= 0 || b <= 0 || c <= 0 || x <= 0 || y <= 0) 
    {
        std::cout << "Incorrect input";
    }else if (a <= x && b <= y || c <= x && b <= y || b <= x && c <= y || b <= x && a <= y || c <= y && a <= x) 
    {
        std::cout << "YES";
    }else if (a > x && b > y || a > x && b <= y || b > y && a <= x || c <= x && b > y || c > x && b <= x || c > y && a <= x || c <= y && a > x)
    { 
        std::cout << "NO";
    }

}