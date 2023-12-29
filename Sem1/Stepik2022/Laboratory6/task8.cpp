#include <iostream>
#include <string>

int main()
{
	int q;
	std::cin >> q;
	while (q != 0)
	{
		q--;

		std::string text1, text2;
		std::cin >> text1;
		std::cin >> text2;

		bool flag = false, flag2 = false;
		bool checkerFlag = false;
		bool checker = false;
		bool checker1 = false;
        
		int co = 0;
		int *arr = new int[1000];

		if (text2 == text1 && text2.length() <= 2 * text1.length() - 1)
		{
			checker1 = true;
		}
		for (int i = 1; i < text2.length() + 1; i++)
		{
			for (int j = 0; j < text1.length(); j++)
			{
				if (text2[i - 1] == text1[j])
				{
					flag2 == true;
				}else
				{
					flag2 = false;
					break;
				}
			}
		}

		for (int i = 1; i < text2.length() + 1; i++)
		{
			int one_more = text1.find(text2[i - 1]);
			arr[co] = one_more;
			co++;
		}

		for (int i = 1; i < text2.length() + 1; i++)
		{
			int one_more = text1.find(text2[i - 1]);
			arr[co] = one_more;
			co++;
		}

		for (int no = 1; no < text2.length() + 1; no++)
		{
			int support = arr[no] - arr[no - 1];
			if (support != -1 || support != 1 && support != 0)
			{
				checkerFlag = true;
			}else
			{
				checkerFlag = false;
				break;
			}
		}

		for (int i = 0; i < text1.length(); i++)
		{
			for (int j = 0; j < text1.length() - i; j++)
			{
				std::string str1 = text1.substr(i, j + 1);
				std::string str2;
				std::string str3;

				if (flag || flag2 || checker || checker1)break;

				if (i + j < text2.length() - 1 - j)
				{
					continue;
				}

				if (text2.length() - 1 - j > 0)
				{
					str2 = text1.substr(i + j - (text2.length() - 1 - j), text2.length() - 1 - j);
					for (int check = str2.length() - 1; check > -1; check--)
					{
						str3.push_back(str2[check]);
					}
				}

				std::string concatenate = str1 + str3;
				if (concatenate == text2) flag = true;
			}
		}

		if (flag  && text2.length() <= 2 * text1.length() - 1 || flag2 && text2.length() <= 2 * text1.length() - 1 || checker && text2.length() <= 2 * text1.length() - 1 || checker1)
		{
			std::cout << "YES" << '\n';
		}else
		{
			std::cout << "NO" << '\n';
		}

		flag2 = false;
		checker = false;
		checkerFlag = false;
		checker1 = false;
		co = 0;

		delete[] arr;
        
	}
}