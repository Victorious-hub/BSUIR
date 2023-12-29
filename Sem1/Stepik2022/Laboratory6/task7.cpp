#include <iostream>
#include <string>

int main() 
{
	std::string text;
	std::cin >> text;

	int checker = 0;
	int checker1 = 0;

	long long length = text.length();

	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < text.length(); j++) 
        {
			if (text[i] == text[j])
            { 
                checker1 += 1;
            }
		}
	}
    
	if (checker1 == length)
    {
        std::cout << -1; return 0;
    }
	if (text.length() <= 1)
    { 
        std::cout << -1; return 0;
    }

	int count = 0, i_ = 1;
	long long length1 = length + 1;

	for (int i = 0; i < 1; i++)
	{
		for (int j = 1; j < length + 1; j++)
		{
			if (text[i_ - 1] == text[length - j])
			{
				count += 2;
				continue;
			}

			i_++;
		}
	}
	if (count > length) 
    { 
        std::cout << length; return 0;
    }else
    { 
        std::cout << length - 1;
    }
}