#include <iostream>
#include <string>

long long  factorial(long long  n)
{
	if (n == 0 || n == 1) 
    {
        return 1;
    }else 
    { 
        return n * factorial(n - 1); 
    }
}

int main() 
{
	std::string text;
    
	char text1[14];
	char m;
	long long  sum = 1;
	long long  count = 0;

	std::cin >> text;

	long long  co = 0;
	long long length = text.length();
	long long textLength = text.length();

	for (int i = 0; i < textLength; i++)
	{
		for (int j = 0; j < textLength; j++)
		{
			if (text[i] == text[j]) 
            { 
                m = text[i]; count += 1;
            }
		}

		for (int k = 0; k < textLength; k++)
		{
			if (m != text[k])
			{
				text1[co] = text[k];
				text[co] = text1[co];
				co++;
			}
		}

		textLength -= count;
		sum *= factorial(count);
		count = 0;
		co = 0;
		i = 0;

		if (textLength == 1) 
        { 
            break;
        }
	}

	std::cout << factorial(length) / sum;
}