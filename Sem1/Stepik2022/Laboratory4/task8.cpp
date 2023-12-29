#include <iostream>

int main() 
{
	int n, m, k = 0;
	std::cin >> n;
	int **firstArr = new int*[n];

	for (int i = 0; i < n; ++i)
	{
		firstArr[i] = new int[n];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			std::cin >> firstArr[i][j];
		}
	}

	std::cin >> m;
	int **secondArr = new int*[m];

	for (int i = 0; i < m; ++i)
	{
		secondArr[i] = new int[m];
	}

	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			std::cin >> secondArr[i][j];
		}
	}

	int** finalArr = new int*[n];

	for (int i = 0; i < n; ++i)
	{
		finalArr[i] = new int[m];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			finalArr[i][j] = 0;
			for (int k = 0; k < n; ++k)
			{
				finalArr[i][j] += firstArr[i][k] * secondArr[k][j];
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			std::cout << finalArr[i][j];
			if (j != n - 1)
			{
				std::cout << ' ';
			}

		}
		std::cout << '\n';
	}

	for (int i = 0; i < n; ++i)
	{
		delete[] firstArr[i];
	}

	delete[] firstArr;

	for (int i = 0; i < n; ++i)
	{
		delete[] secondArr[i];
	}

	delete[] secondArr;

	for (int i = 0; i < n; ++i)
	{
		delete[] finalArr[i];
	}

	delete[] finalArr;

}