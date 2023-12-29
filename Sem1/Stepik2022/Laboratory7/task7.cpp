#include <iostream>
#include <cmath>
#include <cmath>

int checkDel(int a, int n)
{
	if (!n) return 1;
	return checkDel(a, n - 1)*a;
}

long long  funcDel(long long a, long long  var1, long long  var2)
{
	long long resu;
	if (!var1) {
		return 1;
	}
	else if (var1) {
		if (var1 % 2 == 1)
		{
			resu = a % var2 * funcDel(a, var1 - 1, var2);
		}
		else if (var1 % 2 == 0)
		{
			resu = ((funcDel(a, var1 / 2, var2) % var2) * ((funcDel(a, var1 / 2, var2) % var2)));
			resu %= var2;
		}
	}
	else return 0;
	return resu % var2;
}

int main()
{
	long long k, n, t, res, count = 0;
	do
	{
		std::cin >> k >> n >> t;
		if (k <= 0 || n <= 0 || t <= 0)
		{
			return 0;
		}

		int result = checkDel(10, t);
		res = funcDel(k, n, result);
		count++;
		std::cout << "Case #" << count << ": " << res << '\n';
	} while (true);
}