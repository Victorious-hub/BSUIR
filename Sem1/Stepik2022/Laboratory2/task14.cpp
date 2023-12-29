#include <iostream>
#include <cmath>
#include <algorithm>
#include <cmath>

int main() {

	long double W, H, x1, y1, x2, y2, w, h, s1, s2, s3, s4, s_p, var, gh;
	std::cin >> W >> H >> x1 >> y1 >> x2 >> y2 >> w >> h;

	if (w <= x1 && h <= H || w <= (W - x2) && h <= H || w <= (x2 - x1) && h <= (H - y2) || w <= (x2 - x1) && h <= y1) 
    {
        std::cout << 0;

    }else
	{

		int s_t1 = (H * x1 == 0) ? W + H : fabsl(fabsl(H - h) + fabsl((w - x1)));
		int s_t2 = (H * (W - x2) == 0) ? W + H : fabsl(fabsl(H - h) + fabsl((w - (W - x2))));
		int s_t3 = ((x2 - x1)*(H - y2) == 0) ? W + H : fabsl(fabsl(H - y2) - h) + fabsl((w - (x2 - x1)));
		int s_t4 = ((x2 - x1) * y1 == 0) ? W + H : fabsl(fabsl(y1 - h) + fabsl((w - (x2 - x1))));
		var = std::min(std::min(s_t1, s_t2), std::min(s_t3, s_t4));

		if (var == s_t1) 
        {
			gh = fabsl(w - x1);
			if ((W - x2) >= gh)
            {
                std::cout << gh;
            }else
            {
                std::cout << -1;
            }

		}else if (var == s_t2) 
        {
			gh = fabsl(w - (W - x2));
			if (x1 >= gh) 
            {
                std::cout << gh;
            }else
            {
                 std::cout << -1;
            }

		}else if (var == s_t3) 
        {
			gh = fabsl(h - (H - y2));
			if (y1 >= gh) 
            {
                std::cout << gh;
            }else
            {
                std::cout << -1;
            }

		}else if (var == s_t4) 
        {
			gh = fabsl(h - y1);

			if ((H - y2) >= gh) 
            { 
                std::cout << gh;
            }else 
            { 
                std::cout << -1;
            }
		}
        
	}

}