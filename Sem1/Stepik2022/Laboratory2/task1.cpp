#include <iostream>

int main() {

	long int X, Y;
	std::cin >> X >> Y;
	if (Y == 0 && X == 0)
    {
        std::cout << "ERROR"; 
    }else if (X%Y == 0 || Y % X == 0)
    {
        std::cout << "YES";
    }else
    {
        std::cout << "NO";
    }

}