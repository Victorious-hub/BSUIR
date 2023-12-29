#include <iostream>

int main() 
{
	int test;
	std::cin >> test;

	while (test--) 
    {
		long long number;
		std::cin >> number;
		std::cout << (number + 1) / 10 << '\n';
	}
}