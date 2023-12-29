#include <iostream>
#include <string>

int main() 
{

	std::string n, n1;
	long long count = 0, j = 0, K = 0, i;
	char *array;
	std::cin >> n;

	for (int a : n)
	{
		count += 1;
	}

	array = new char[count];

	for (int i = 0; i < count; i++)
	{
		array[i] = n[i];
	}

	for (int i = 0; i < count; i++)
	{
		bool variable = true;

		for (int j = 0; j < count; ++j)
		{
			if (array[i] == array[j] && i != j)
			{
				array[i] = -1;
				variable = false;
				break;
			}
		}

		if (variable)
		{
			++K;
		}
	}
    
	std::cin >> i;
	std::cout << K << '\n';

	for (int j = count; j > 0; j--)
	{
		if (n[i - 1] == n[j - 1]) std::cout << count - j << ' ';
	}

	delete[] array;

}