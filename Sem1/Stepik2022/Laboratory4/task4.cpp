#include <iostream> 

int main()
{
	int n, m, result = 0;
	std::cin >> n >> m;
	int array[n][m];
    
	for (int i = 0; i < n; i++) 
    {
		for (int j = 0; j < m; j++) 
        {
			std::cin >> array[i][j];
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			bool checker = false;
			if (i > 0 && array[i - 1][j] <= array[i][j] || j > 0 && array[i][j - 1] <= array[i][j])
				checker = true;
			if (i < n - 1 && array[i + 1][j] <= array[i][j] || j < m - 1 && array[i][j + 1] <= array[i][j])
				checker = true;
			if (!checker)
				result += 1;
		}
	}
	std::cout << result;
}