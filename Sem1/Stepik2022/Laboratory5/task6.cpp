#include <iostream>

long long S(long long i)
{
	long long a = 0, b = 0;
	if (i == 0)return 0;
	if (i % 10 > 0) return i % 10;
	else 
    {
		return S(i / 10);
	}
}

int main()
{
	long long p, q;
	while (true) 
    {
		std::cin >> p >> q;

		if (p < 0 && q < 0 || p < 0 || q < 0 || p > q)return 0;

		long long get = 0;

		for (int i = p; i <= q; i++)
		{
			get += S(i);
		}
        
		std::cout << get << '\n';
	}

}