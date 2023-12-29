#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

int main()
{
	int co = 0;
	int *random4ik, *random4ik1, *arrFinal;
	long long a, b, i = 0, t, counter3 = -1, counter4 = -1, counter5 = 0, counter6 = -2, counter55 = 0, lone = 0, lone1 = 0;
	double timed, timed1, h, iu = 0;
	int RANDOM = 0;
	random4ik = new int[1000];
	random4ik1 = new int[1000];
	arrFinal = new int[1000];

	for (i = 0; i < RANDOM; ++i)
	{
		std::cin >> random4ik[i];
	}

	i = 0;

	while (std::cin >> t)
	{
		random4ik[i] = t;
		i++;
		RANDOM++;

	}

	for (i = 0; i < RANDOM; ++i)
	{
		random4ik1[i] = random4ik[i];
	}

	for (a = 1.; a < RANDOM; ++a)
	{
		for (b = RANDOM - 1; b >= a; --b)
		{
			if (random4ik[b - 1] > random4ik[b])
			{
				iu = random4ik[b - 1];
				random4ik[b - 1] = random4ik[b];
				random4ik[b] = iu;
			}
		}
	}

	timed = random4ik[0];
	timed1 = random4ik[RANDOM - 1];

	for (i = 0; i < RANDOM; ++i)
	{
		if (random4ik1[i] == timed) { counter3 = i; }
		else if (random4ik1[i] == timed1) { counter4 = i; }
	}

	for (i = 0; i < RANDOM; i++)
	{
		if (random4ik1[i] == 0) 
        { 
            counter55 += 1; 
        }else if (i > counter3 && i < counter4 && random4ik1[i] != timed && random4ik1[i] != timed1 || i < counter3 && i > counter4 && random4ik1[i] != timed && random4ik1[i] != timed1)
		{
			random4ik1[i] = 0;
			counter5 += 1 + counter55;

		}else 
        { 
            counter6 += 1;
        }

	}

	for (i = 0; i < RANDOM; ++i)
	{
		if (counter5 <= counter6)
		{
			double arrFinal[] = { random4ik1[i] };
			for (double u : arrFinal)
			{
				std::cout << u << ' ';

			}
		}else if (counter5 > counter6)
		{
			double arrFinal[] = { random4ik1[i] };
			for (double u : arrFinal)
			{
				if (u != 0)
				{
					double array[] = { u };
					for (double uu : array)
					{
						std::cout << uu << ' ';
					}

				}else
                {
                     continue;
                }

			}
		}
		else continue;
	}

	delete[] random4ik;
	delete[] random4ik1;
	delete[] arrFinal;

}