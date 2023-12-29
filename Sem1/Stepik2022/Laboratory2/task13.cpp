#include <iostream>

int main() {

	long int a, K;
	setlocale(LC_ALL, "Rus");
	std::cin >> K;
	a = K;
	a %= 100;
	if (a >= 5 && a <= 20)
    { 
        std::cout << "Мы нашли" << ' ' << K << ' ' << "грибов в лесу"; 
        return 0; 
    }
	a %= 10;
	if (a == 0)
    { 
        std::cout << "Мы нашли" << ' ' << K << ' ' << "грибов в лесу";
    }else if (a == 1) 
    { 
        std::cout << "Мы нашли" << ' ' << K << ' ' << "гриб в лесу";
    }else if (a >= 2 && a <= 4)
    { 
        std::cout << "Мы нашли" << ' ' << K << ' ' << "гриба в лесу";
    }else if (a >= 5 && a <= 9)
    { 
        std::cout << "Мы нашли" << ' ' << K << ' ' << "грибов в лесу";
    }

}