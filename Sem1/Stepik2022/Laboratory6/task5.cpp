#include <iostream>
#include <string>

long long  binPow(long long a, long long  var1, long long  var2)
{
	long long resu;
	if (!var1) {
		return 1;
	}
	else if (var1) {
		if (var1 % 2 == 1)
		{
			resu = a % var2 * binPow(a, var1 - 1, var2);
		}
		else if (var1 % 2 == 0)
		{
			resu = ((binPow(a, var1 / 2, var2) % var2) * ((binPow(a, var1 / 2, var2) % var2)));
			resu %= var2;
		}
	}
	else return 0;
	return resu % var2;
}

int main()
{
	int t;
	std::cin >> t;

	while (t != 0)
	{
		t--;
		long long L, m;

		std::cin >> L >> m;
		std::string s1, s2;
		std::cin >> s1 >> s2;

		long long result = 0;
		int s1_size = s1.length();
		int s2_size = s2.length();
		int size = L;
		int counter = 0, counter1 = 0;

		if (L - (s1_size + s2_size) < 0)
		{
			for (int i = 0; i < s1_size; i++)
			{
				int k = s2.find(s1.substr(i));

				if (k != -1)
				{
					counter = s1_size - i;
					break;
				}
			}
			for (int i = 0; i < s2_size; i++)
			{
				int k = s1.find(s2.substr(i));

				if (k != -1)
				{
					counter1 = s2_size - i;
					break;
				}
			}

			result = (s1_size + s2_size - counter == L || s1_size + s2_size - counter1 == L) ? 1 : 0;

		}else if (L - (s1_size + s2_size) == 0)
		{
			result = (s1 == s2) ? 1 : 2;

		}else if (L - (s1_size + s2_size) > 0)
		{
			result = (s1 == s2) ? binPow(26, L - (s1_size + s2_size), m) : (binPow(26, L - (s1_size + s2_size), m) * 2 % m) % m;
		}
        
		std::cout << result << '\n';
	}
}