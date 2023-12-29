#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool check(std::string s);

int main()
{
	int n = 0;
	std::cin >> n;
    std::vector<std::string> A = { "0","1" };
    std::vector<std::string> B;
    std::string to = "";

    do 
    {
        B.resize(0);
        
        for (int o = 0; o < A.size(); ++o)
            B.push_back(A[o]);
        A.resize(0);

        for (int k = 0; k < B.size(); ++k)
        {
            std::string now = "";
            now += B[k];

            if (now[now.length() - 1] != '0') 
            {
                n--;
            }
            if (!n) 
            {
                std::string final;

                for (int i = now.size(); i >= 0; i--)
                    final.push_back(now[i]);

                final.erase(0, 1);
                std::cout << final;
                return 0;
            }

            now.push_back('0');
            bool flag = check(now);

            if (flag == true) 
            {
                A.push_back(now);
            }
        }
        for (int i = 0; i < B.size(); ++i) 
        {
            std::string no = "";

            no += B[i];
            no.push_back('1');
            bool flag1 = check(no);

            if (flag1) 
            {
                A.push_back(no);
            }
        }
    } while (n != -1);
	
}

bool check(std::string s) 
{
	int var = 0, var1;
	std::vector<int> massiv1(10000);//либо 0 либо 1
	std::vector<int> massiv2(10000);// либо 0 либо 1
	massiv1[var++] = 1;

	for (var1 = 0; var1 < s.length(); ++var1) 
    {
		if (s[var1] != '0') 
        {
			for (int i = var1; i < var + 1; ++i) 
            {
				massiv2[i] += massiv1[i];

				if (massiv2[i] > 2 || massiv2[i] == 2) 
                {
					massiv2[i + 1] += (massiv2[i] / 2);
					massiv2[i] = massiv2[i] & 1;
				}
			}
		}
		if ((s[var1] - '0') != massiv2[var1]) 
        {
			return 0;
		}

		int now = 0;

		for (int i = var1; i < var; ++i) 
        {
			now += massiv1[i] * 10;
			massiv1[i] = now & 1;
			now /= 2;

			if (var < s.length()) 
            {
				var++;
			}
		}
	}

	massiv1.resize(0);
	massiv2.resize(0);
	return 1;
}