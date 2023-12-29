#include <iostream>

int main() 
{
	int **array, n, m;
	std::cin >> n >> m;
	array = new int*[n];

	for (int i = 0; i < n; i++)
	{
		array[i] = new int[m];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cin >> array[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			if (array[i][j - 1] > array[i][j])
			{
				array[i][j] = array[i][j - 1];
			}else
			{
				array[i][j] = array[i][j];
			}
		}
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (array[i - 1][j] > array[i][j])
			{
				array[i][j] = array[i - 1][j];
			}else
			{
				array[i][j] = array[i][j];
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << array[i][j] << ' ';
		}
		std::cout << '\n';
	}
	for (int i = 0; i < n; i++)
	{
		delete[] array[i];
	}
	delete[] array;

}