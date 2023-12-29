#include <iostream>
#include <cmath>
#include <iomanip>

int main() 
{

	double X, Y, Z;
	std::cin >> X >> Y >> Z;
	if (X + Y > Z && X + Z > Y && Z + Y > X && X > 0 && Y > 0 && Z > 0) 
    {
        std::cout << "YES";
    }else
    {
        std::cout << "NO";
    }

}