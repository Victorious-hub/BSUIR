#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    
	long double  K, X, Y;
	std::cin >> K >> X >> Y;
	if (K > 0)
	{
		if (X <= K && X >= 0 && Y <= K && Y >= 0)
		{
			if (X <= K - X && X <= K - Y && X <= Y) { std::cout << std::setprecision(22) << X; }
			else if (Y <= X && Y <= K - X && Y <= K - Y) { std::cout << std::setprecision(22) << Y; }
			else if (K - X <= X && K - X <= Y && K - X <= K - Y) { std::cout << std::setprecision(22) << K - X; }
			else if (K - Y <= X && K - Y <= Y && K - Y <= K - X) { std::cout << std::setprecision(22) << K - Y; }
		}

		else if (X == 0 && Y == 0 || Y == K && X == 0 || Y == K && X <= K || X <= K && Y == 0 || X == K && Y == 0 || X == K && Y == K) { std::cout << std::setprecision(22) << 0; }
		else if (X > K && Y <= K)
		{
			if (X > K && Y < 0) {
				std::cout << std::setprecision(22) << sqrtl((X - K)*(X - K) + (Y - 0)*(Y - 0));
			}
			else {
				std::cout << std::setprecision(22) << X - K;
			}
		}
		else if (Y > K && X <= K)
		{
			if (X < 0 && Y > K) { std::cout << std::setprecision(22) << sqrtl((X - 0)*(X - 0) + (Y - K)*(Y - K)); }
			else {
				std::cout << std::setprecision(22) << Y - K;
			}
		}
		else if (Y < 0 && X <= K)
		{
			if (X < 0 && Y < 0) { std::cout << std::setprecision(22) << sqrtl((X - 0)*(X - 0) + (Y - 0)*(Y - 0)); }
			else {
				std::cout << std::setprecision(22) << fabsl(Y);
			}
		}
		else if (X < 0 && Y <= K) { std::cout << std::setprecision(22) << fabsl(X); }
		else if (X > K && Y > K) { std::cout << std::setprecision(22) << sqrtl((X - K)*(X - K) + (Y - K)*(Y - K)); }

	}
	else if (K < 0)
	{
		if (X >= K && Y >= K && Y <= 0 && X <= 0) {
			if (X >= K - X && X >= K - Y && X >= Y) { std::cout << std::setprecision(22) << fabs(X); }
			else if (Y >= X && Y >= K - X && Y >= K - Y) { std::cout << std::setprecision(22) << fabs(Y); }
			else if (K - X >= X && K - X >= Y && K - X >= K - Y) { std::cout << std::setprecision(22) << fabs(K - X); }
			else if (K - Y >= X && K - Y >= Y && K - Y >= K - X) { std::cout << std::setprecision(22) << fabs(K - Y); }
		}
		else if (X == 0 && Y == 0 || Y == K && X == 0 || Y == K && X >= K || X >= K && Y == 0 || X == K && Y == 0 || X == K && Y == K) { std::cout << std::setprecision(22) << 0; }
		else if (X < K && Y >= K)
		{
			if (X < K && Y > 0) {
				std::cout << std::setprecision(22) << fabsl(sqrtl((X - K)*(X - K) + (Y - 0)*(Y - 0)));
			}
			else {
				std::cout << std::setprecision(22) << fabsl(X - K);
			}
		}
		else if (Y < K && X >= K)
		{
			if (X > 0 && Y < K) { std::cout << std::setprecision(22) << fabsl((sqrtl((X - 0)*(X - 0) + (Y - K)*(Y - K)))); }
			else {
				std::cout << std::setprecision(22) << fabsl(Y - K);
			}
		}
		else if (Y > 0 && X >= K)
		{
			if (X > 0 && Y > 0) { std::cout << std::setprecision(22) << fabsl(sqrtl((X - 0)*(X - 0) + (Y - 0)*(Y - 0))); }
			else {
				std::cout << std::setprecision(22) << fabsl(Y);
			}
		}
		else if (X > 0 && Y >= K) { std::cout << std::setprecision(22) << fabsl(X); }
		else if (X < K && Y < K) { std::cout << std::setprecision(22) << fabsl(sqrtl((X - K)*(X - K) + (Y - K)*(Y - K))); }
	}
	return 0;

}