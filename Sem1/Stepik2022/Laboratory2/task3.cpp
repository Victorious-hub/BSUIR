#include <iostream>

int main() 
{

	long long X, Y;
	double A, B, C, K;
	std::cin >> X >> Y;
	std::cin >> A >> B >> C >> K;
	if (X > Y) 
    {
        Y = 0;
    }else if (X < Y)
    {
         X = 0;
    }else
    { 
        X = Y = 0;
    }

	if (A > B&&A > C)
    { 
        A -= K;
    }else if (B > A&&B > C)
    {
        B -= K;
    }else if (C > B&&C > A)
    { 
        C -= K;
    }else
    {
        A = B = C = 0;
    }
    
	std::cout << X << ' ' << Y << '\n';
	std::cout << A << ' ' << B << ' ' << C;

}