#include <iostream>

long long longSqrt(long long number)
{
	long long small, large;
	if (number < 2)
	{
		return number;
	}
	else
	{
		small = longSqrt(number >> 2) << 1;
		large = small + 1;
	}
	if (large*large > number)
	{
		return small;
	}
	else
	{
		return large;
	}
}

int main() 
{

	long long row;
	long long column;
	long long number;

	std::cin >> number;

	long long m = longSqrt(number - 1);
	long long k = (m*(m + 1) + 1);

	if ((m % 2) == 1)
	{
		if (k < number)
		{
			row = m;
			column = (m)-(number - k);
		}else if (k == number)
		{
			row = m;
			column = m;
		}else
		{
			column = m;
			row = (m)+(number - k);
		}
	}else
	{
		if (k < number)
		{
			row = m;
			column = (m)-(number - k);
		}else if (k == number)
		{
			row = m;
			column = m;
		}else
		{
			column = m;
			row = (m)+(number - k);
		}
	}

	std::cout << row << ' ' << column;
}