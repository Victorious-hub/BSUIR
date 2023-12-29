#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <typeinfo>
#include <vector>

int main() {

	std::vector<int> get;
	std::vector<int> get1;
	int variable;
	std::cin >> variable;
	long long number = variable, number1 = variable, getVar = variable, counter = 0;

	while (getVar != 0)
	{
		getVar /= 3;
		counter++;
	}

	for (int i = 0; i < counter; i++)
	{
		number /= 3;
		number1 %= 3;
		if (!number1) {
			variable /= 3;
			get.push_back(number1);
		}
		else { variable -= number1; variable /= 3; get.push_back(number1); }
		number1 = variable;

	}

	int cou = 0;
	int x = 10;
	bool flagi = false;

	std::string text, text1;

	for (int i = 0; i < get.size(); i++)
	{
		text += std::to_string(get[i]);
	}

	for (int i = text.length() - 1; i > -1; i--)
		text1.push_back(text[i]);

	int co = 1;
	int find = text1.length();

	for (int j = 0; j < text1.length(); j++)
	{
		if (flagi)break;

		for (int i = 1; i < text1.length() + 1; i++)
		{
			if (text1[i] == '0' && text1[i - 1] == '1') 
            { 
                text1.replace(i, 1, "3");
                text1.replace(i - 1, 1, "0");
                break;
            }
			else if (text1[i] == '0' && text1[i - 1] == '2')
            { 
                text1.replace(i, 1, "3");
                text1.replace(i - 1, 1, "1");
                break;
            }else if (text1[i] == '0' && text1[i - 1] == '3')
            { 
                text1.replace(i, 1, "3");
                text1.replace(i - 1, 1, "2");
                break;
            }

		}

		for (int i = 1; i < text1.length() + 1; i++)
		{
			if (text1[i - 1] == '0') 
            { 
                flagi = false;
                break;
            }else
            { 
                flagi = true;
            }
		}

		if (text1[0] == '0')text1.erase(0, 1);
	}

	std::cout << text1;
}