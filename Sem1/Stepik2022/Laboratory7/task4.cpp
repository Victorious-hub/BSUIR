#include <vector>
#include <iostream>
#include <string>

int main()
{
	std::vector<std::string> rome = { "I","II","III","IV","V","VI","VII","VIII","IX","X","XX","XXX","XL","L","LX","LXX","LXXX","XC","C","CC","CCC","CD","D","DC","DCC","DCCC","CM","M","MM","MMM" };
	int numRome[] = { 1,2,3,4,5,6,7,8,9,10,20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000 };

	int n1 = sizeof(numRome) / sizeof(numRome[0]);
	int a;

	std::cin >> a;

	int n, k, m = 10, getA = a, count = 0;
	int b = a;
    
	std::vector<int> array;

	while (getA != 0)
	{
		b /= 10;
		getA = b;
		count++;
	}

	n = a;
	k = a;
	bool flag = false;

	for (int check = 0; check < n1; check++)
	{
		if (b == numRome[check]) 
        {
            std::cout << rome[check];
            flag = true;
        }
	}

	int counter = 0;

	for (int i = 0; i < count; i++)
	{
		if (n == 10) 
        { 
            counter++; 
            array.push_back(n);
            break;
        }

		n %= m;
		array.push_back(n);
		k -= n;
		n = k;
		m *= 10;
	}

	std::vector<std::string> get;

	for (int i = array.size() - 1; i > -1; i--)
	{
		for (int j = 0; j < n1; j++)
		{
			if (array[i] == numRome[j]) 
            { 
                get.push_back(rome[j]);
            }
		}
	}

	for (int output = 0; output < get.size(); output++)
		std::cout << get[output];
}